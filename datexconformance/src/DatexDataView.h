#pragma once
#include "DatexNarrative.h"
#include "DatexWire.h"
#include <algorithm>
#include <sstream>

namespace datex {
struct LinkedData {
    std::string message, oid, decodedJson, regionalJson, note;
    unsigned subscription = 0, publication = 0;
    Bytes raw;
};
inline std::string dataHex(const Bytes &bytes) {
    static const char *digits = "0123456789abcdef";
    std::string text;
    text.reserve(bytes.size() * 2);
    for (auto b : bytes) { text += digits[b >> 4]; text += digits[b & 15]; }
    return text;
}
// Inspect the bytes observed on the connection, including TX after send succeeds.
// This view does not submit platform validation or change the protocol verdict.
inline std::vector<LinkedData> inspectLinkedData(const Case &c, const Bytes &wire,
                                               const std::string &test) {
    std::vector<LinkedData> records;
    Bytes bytes = wire;
    auto packet = decode(bytes);
    if (packet->pdu->present != Iso14827PDUsPresent_publication) return records;
    auto messages = c.messages;
    if (test.compare(0, 7, "normal_") == 0) {
        auto preferred = std::find_if(messages.begin(), messages.end(), [&](const Message &m) {
            return test == std::string("normal_") + m.name;
        });
        if (preferred != messages.end()) std::rotate(messages.begin(), preferred, preferred + 1);
    }
    for (auto d : publicationData(packet->pdu->x.publication)) {
        LinkedData base;
        base.subscription = d->subscriptionSerial; base.publication = d->serial;
        if (d->type && d->type->present == Iso14827PublicationTypePresent_msg && d->type->x.msg) {
            auto msg = d->type->x.msg;
            base.oid = oidText(msg->oid);
            if (msg->data) base.raw.assign(msg->data->data, msg->data->data + msg->data->size);
        }
        const auto before = records.size();
        std::set<std::string> attempted;
        for (auto m : messages) {
            const std::string oid = m.oid ? m.oid : c.oid;
            if (oid != base.oid || !attempted.insert(oid + ":" + std::to_string(m.psid) + ":" + std::to_string(m.type)).second) continue;
            m.businessProfile = 0; // Display the actual content, independently of the selected criterion.
            Sink capture;
            std::string regional;
            capture.info = [&](const std::string &, const std::string &text) {
                const std::string prefix = "TIM_REGIONAL_DECODE ";
                if (text.compare(0, prefix.size(), prefix) == 0) regional = text.substr(prefix.size());
            };
            capture.validation = [&](const std::string &, const std::string &name, const Bytes &raw, const Bytes &json) {
                auto value = base;
                value.message = name; value.raw = raw;
                value.decodedJson.assign(json.begin(), json.end()); value.regionalJson = regional;
                records.push_back(std::move(value));
            };
            try { validatePayload(messageCase(c, m), m, d, &capture, test); }
            catch (const Failure &) { /* Invalid stimuli and absent bundled message kinds are also observable. */ }
        }
        if (records.size() == before) {
            base.note = "이 전문에서는 연계정보 요약을 생성하지 못했습니다. 원문과 식별정보를 보관했습니다. 적합 여부는 해당 시험의 판정을 확인하세요.";
            records.push_back(std::move(base));
        }
    }
    return records;
}
inline const Json *dataAt(const Json *j, std::initializer_list<const char *> path) {
    for (auto key : path) { if (!j) return nullptr; j = j->get(key); }
    return j;
}
inline std::string dataValue(const Json *j) {
    if (!j || j->kind == Json::Null) return "미제공";
    if (j->kind == Json::Bool) return j->boolean ? "예" : "아니요";
    if (j->kind != Json::Number && j->kind != Json::String) return "상세 구조";
    if (j->text.empty()) return "빈 값";
    std::string text = j->text;
    for (auto &c : text) if (static_cast<unsigned char>(c) < 32) c = ' ';
    if (text.size() > 180) {
        size_t end = 180;
        while (end && (static_cast<unsigned char>(text[end]) & 0xc0) == 0x80) --end;
        text.resize(end); text += "…(일부 표시)";
    }
    return text;
}
inline size_t dataCount(const Json *j) { return j && j->kind == Json::Array ? j->array.size() : 0; }
inline std::string dataList(const Json *j) {
    if (!j || j->kind == Json::Null) return "미제공";
    if (j->kind != Json::Array) return dataValue(j);
    if (j->array.empty()) return "0개";
    std::string text;
    for (size_t i = 0; i < std::min<size_t>(3, j->array.size()); ++i) {
        if (i) text += ", "; text += dataValue(&j->array[i]);
    }
    if (j->array.size() > 3) text += " 외 " + std::to_string(j->array.size() - 3) + "개";
    return text;
}
inline std::vector<std::string> linkedDataSummary(const LinkedData &record) {
    if (record.decodedJson.empty()) {
        std::vector<std::string> result{record.note};
        if (!record.raw.empty()) result.push_back("분석 전 연계정보 원문(앞 32바이트): " + dataHex(Bytes(record.raw.begin(), record.raw.begin() + std::min<size_t>(32, record.raw.size()))));
        return result;
    }
    std::vector<std::string> lines;
    try {
        auto body = Json::parseData(record.decodedJson);
        auto value = [&](const Json *j, std::initializer_list<const char *> path) { return dataValue(dataAt(j, path)); };
        auto position = [&](const Json *j) { return "위도 " + value(j, {"lat"}) + ", 경도 " + value(j, {"lon"}); };
        auto array = [&](const Json *list, const std::string &label, auto render) {
            if (!list || list->kind == Json::Null) { lines.push_back(label + ": 미제공"); return; }
            lines.push_back(label + ": " + std::to_string(dataCount(list)) + "개");
            for (size_t i = 0; i < std::min<size_t>(3, dataCount(list)); ++i) render(&list->array[i], i);
            if (dataCount(list) > 3) lines.push_back(label + " 중 앞 3개 표시. 나머지는 전체 데이터 증적에 보관했습니다.");
        };
        const auto *j = &body;
        if (record.message == "bsm") {
            auto core = j->get("coreData");
            lines.push_back("차량 식별자 " + value(core, {"id"}) + "; 메시지 순번 " + value(core, {"msgCnt"}) + "; 초 내 시각 " + value(core, {"secMark"}));
            lines.push_back(position(core) + "; 고도 " + value(core, {"elev"}) + "; 속도 " + value(core, {"speed"}) + "; 진행 방향 " + value(core, {"heading"}) + "; 변속 상태 " + value(core, {"transmission"}));
            lines.push_back("차량 폭 " + value(core, {"size","width"}) + "; 길이 " + value(core, {"size","length"}) + "; 제동 상태 " + value(core, {"brakes","wheelBrakes"}));
        } else if (record.message == "map") {
            lines.push_back("지도 개정번호 " + value(j,{"msgIssueRevision"}) + "; 기준 시각 " + value(j,{"timeStamp"}));
            for (auto key : {"intersections", "roadSegments"}) array(j->get(key), std::string(key)=="intersections" ? "교차로" : "도로 구간", [&](const Json *v, size_t) {
                auto lanes = v->get(std::string(key)=="intersections" ? "laneSet" : "roadLaneSet");
                lines.push_back("지역 " + value(v,{"id","region"}) + ", 식별자 " + value(v,{"id","id"}) + ", 이름 " + value(v,{"name"}) + "; 기준 위치 " + position(v->get("refPoint")) + "; 차로 " + (lanes && lanes->kind == Json::Array ? std::to_string(dataCount(lanes)) + "개" : "미제공"));
                if (lanes && lanes->kind == Json::Array) for (size_t i=0; i<std::min<size_t>(3,lanes->array.size()); ++i) {
                    auto lane=&lanes->array[i]; lines.push_back("차로 ID " + value(lane,{"laneID"}) + ", 이름 " + value(lane,{"name"}) + ", 허용 진행 코드 " + value(lane,{"maneuvers"}));
                }
                auto speeds=v->get("speedLimits");
                if (speeds && dataCount(speeds)) lines.push_back("첫 속도 제한 종류 " + value(&speeds->array[0],{"type"}) + ", 속도 " + value(&speeds->array[0],{"speed"}));
            });
        } else if (record.message == "spat") {
            lines.push_back("메시지 이름 " + value(j,{"name"}) + "; 기준 시각 " + value(j,{"timeStamp"}));
            array(j->get("intersections"), "교차로", [&](const Json *v, size_t) {
                lines.push_back("지역 " + value(v,{"id","region"}) + ", 교차로 ID " + value(v,{"id","id"}) + ", 이름 " + value(v,{"name"}));
                array(v->get("states"), "신호군", [&](const Json *state, size_t) {
                    auto events=state->get("state_time_speed");
                    lines.push_back("신호군 ID " + value(state,{"signalGroup"}) + ", 이름 " + value(state,{"movementName"}));
                    if (dataCount(events)) { auto e=&events->array[0]; lines.push_back("첫 신호 상태 " + value(e,{"eventState"}) + "; 시작 시각 " + value(e,{"timing","startTime"}) + "; 최소 종료 시각 " + value(e,{"timing","minEndTime"}) + "; 최대 종료 시각 " + value(e,{"timing","maxEndTime"})); }
                    if (dataCount(events)>1) lines.push_back("신호 상태 " + std::to_string(dataCount(events)) + "개 중 첫 상태 표시");
                });
            });
        } else if (record.message == "tls") {
            lines.push_back("신호등 ID " + value(j,{"trafficLightID"}) + "; 주기 순번 " + value(j,{"cycleCounter"}) + "; 주기 시간 " + value(j,{"cycleTime"}) + "; " + position(j));
            auto time=j->get("currentTime");
            lines.push_back("제공 시각 " + value(time,{"year"}) + "/" + value(time,{"month"}) + "/" + value(time,{"day"}) + " " + value(time,{"hour"}) + ":" + value(time,{"minute"}) + ", 초 필드 " + value(time,{"second"}));
            array(j->get("trafficLightStatus"), "신호등 상태", [&](const Json *v,size_t i) {
                lines.push_back(std::to_string(i+1) + "번: 신호등 종류 " + value(v,{"trafficLightType"}) + ", 등화 상태 " + value(v,{"lightingStatus"}) + ", 잔여 시간 " + value(v,{"remainingTime"}) + ", 방향 코드 " + value(v,{"directionCode"}) + ", 보행 호출 " + value(v,{"pedestrianCall"}));
            });
        } else if (record.message == "rsa") {
            lines.push_back("경고 종류 코드 " + value(j,{"typeEvent"}) + "; 설명 코드 " + dataList(j->get("description")) + "; 우선순위 " + value(j,{"priority"}));
            lines.push_back("발생 위치 " + position(j->get("position")) + "; 적용 범위 " + value(j,{"extent"}) + "; 방향 " + value(j,{"heading"}) + "; 추가정보 ID " + value(j,{"furtherInfoID"}));
        } else if (record.message.compare(0,3,"tim")==0) {
            lines.push_back("안내 식별자 " + value(j,{"packetID"}) + "; 메시지 순번 " + value(j,{"msgCnt"}) + "; 기준 시각 " + value(j,{"timeStamp"}));
            array(j->get("dataFrames"), "안내 프레임", [&](const Json *v,size_t i) {
                lines.push_back(std::to_string(i+1) + "번: 종류 " + value(v,{"frameType"}) + ", 추가정보 ID " + value(v,{"msgId","furtherInfoID"}) + ", 우선순위 " + value(v,{"priority"}) + "; 시작 연도 " + value(v,{"startYear"}) + ", 시작 시각 " + value(v,{"startTime"}) + ", 지속 시간 " + value(v,{"durationTime"}));
                array(v->get("regions"), "적용 구간", [&](const Json *region,size_t) {
                    lines.push_back("구간명 " + value(region,{"name"}) + ", 지역 " + value(region,{"id","region"}) + ", 구간 ID " + value(region,{"id","id"}) + "; 기준 위치 " + position(region->get("anchor")) + "; 방향 " + value(region,{"directionality"}));
                });
                auto content=v->get("content");
                if (content && content->kind == Json::Object) for (const auto &part : content->object) {
                    array(&part.second, "안내 내용 ("+part.first+")", [&](const Json *item,size_t) {
                        auto text=dataAt(item,{"item","text"});
                        lines.push_back("ITIS 코드 " + value(item,{"item","itis"}) + "; 안내문 " + dataValue(text));
                    });
                }
            });
            if (!record.regionalJson.empty()) {
                auto r=Json::parseData(record.regionalJson);
                lines.push_back("국내 확장: 안내정보 " + value(&r,{"travelerInformationKor"}) + "개, 구간정보 " + value(&r,{"geographicalPathKor"}) + "개; 기타 지역 확장 " + value(&r,{"opaqueOtherRegions"}) + "개");
                array(r.get("values"), "국내 확장 주요값", [&](const Json *v,size_t) {
                    if (value(v,{"kind"}) == "text") lines.push_back("안내 프레임 " + value(v,{"frameIndex"}) + "; 실제 안내문 " + value(v,{"value"}));
                    else {
                        static const std::map<std::string,std::string> names={{"0","차로 ID"},{"1","도로 구간 ID"},{"2","링크 ID"},{"3","검지 차로 코드"},{"4","영역 ID"},{"5","교차로 ID"}};
                        auto type=names.find(value(v,{"type"}));
                        lines.push_back((type==names.end()?"구간 식별값":type->second) + " " + value(v,{"value"}));
                    }
                });
                if (value(&r,{"summaryOmitted"}) != "0" && r.get("summaryOmitted")) lines.push_back("국내 확장 주요값 일부는 표시 한도를 넘어 생략했습니다. 원문 증적을 확인하세요.");
            }
        }
        if (lines.empty()) lines.push_back("이 메시지의 상세 데이터는 전체 데이터 증적에 보관했습니다.");
    } catch (const Failure &) { lines = {"요약 표시 범위를 넘었거나 표시 변환을 완료하지 못했습니다. 디코딩 데이터와 원문은 전체 데이터 증적에 보관했습니다."}; }
    return lines;
}
} // namespace datex
