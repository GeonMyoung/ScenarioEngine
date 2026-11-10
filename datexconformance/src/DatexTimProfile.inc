/* P3 Annex II mandatory core fields; optional regional business semantics are
   explicitly outside this check. The original generic TIM fixture is retained. */
#include <time.h>
Dz1Binary *DatexPayload_timProfile(unsigned char *bytes, size_t size, unsigned kind) {
    if (kind == 3) return DatexPayload_timRegionalFixture(bytes, size, 0);
    if ((kind != 1 && kind != 2) || !bytes || size > UINT32_MAX) return NULL;
    Dz1Error e = DZ1_ERROR_INITIALIZER;
    Dz1Binary input = {bytes, (u32_t)size}, *raw = NULL, *body = NULL, *result = NULL;
    ASN1WorkSpace ws, encoded;
    ASN1_INIT_WS_INFO(&ws);
    ASN1_INIT_WS_INFO(&encoded);
    TravelerInformation value;
    int id = 0;
    raw = GitsnAsnUtil_getValueFromMessageFrame(&input, &id, &e);
    if (!raw || id != 31 || !TravelerInformation_uper_decode(&ws, raw, &value, &e) || value.dataFrames.count != 1) goto profile_done;
    TravelerDataFrame *frame = ASN1_Get_Node_Index(&value.dataFrames, 1);
    if (!frame || !frame->msgId || !frame->content || frame->content->M != DEF_TravelerDataFrame_content_advisory || frame->content->elements.advisory.count != 1) goto profile_done;
    ITIScodesAndText_element *item = ASN1_Get_Node_Index(&frame->content->elements.advisory, 1);
    if (!item || !item->item) goto profile_done;
    unsigned char packet[9] = {0x56, 0x45, 0x48, 0, 0, 0, 0, 0x0c, (unsigned char)kind};
    unsigned char info[2] = {0x0c, (unsigned char)kind};
    value.DEF_TravelerInformation_packetID = 1;
    value.packetID.data = packet;
    value.packetID.numbits = sizeof(packet);
    frame->frameType = TravelerInfoType_advisory;
    frame->msgId->M = DEF_TravelerDataFrame_msgId_furtherInfoID;
    frame->msgId->elements.furtherInfoID.data = info;
    frame->msgId->elements.furtherInfoID.numbits = sizeof(info);
    time_t now = time(NULL);
    struct tm utc;
    if (gmtime_s(&utc, &now)) goto profile_done;
    frame->DEF_TravelerDataFrame_startYear = 1;
    frame->startYear = utc.tm_year + 1900;
    frame->startTime = (utc.tm_yday * 24 + utc.tm_hour) * 60 + utc.tm_min;
    value.DEF_TravelerInformation_timeStamp = 1;
    value.timeStamp = frame->startTime;
    frame->notUsed = frame->notUsed1 = frame->notUsed2 = frame->notUsed3 = 0;
    item->item->M = DEF_ITIScodesAndText_element_item_itis;
    item->item->elements.itis = kind == 1 ? 7444 : 7428;
    body = TravelerInformation_get_uper_encoded(&value, &e);
    if (!body) goto profile_done;
    MessageFrame message;
    memset(&message, 0, sizeof(message));
    message.messageId = 31;
    message.value.data = body->data;
    message.value.numocts = body->size;
    if (ASN1_PER_UNAlign_Enc_MessageFrame(&encoded, &message) < 0) goto profile_done;
    result = Dz1Binary_new(ASN1WorkSpace_getEncodePtr(&encoded),
                          ASN1WorkSpace_getEncodedSize(&encoded, Dz1Asn1Codec_uper), &e);
profile_done:
    Dz1Binary_del(body); Dz1Binary_del(raw);
    ASN1_INIT_WS_INFO_cancel(&encoded); ASN1_INIT_WS_INFO_cancel(&ws);
    return result;
}
int DatexPayload_checkTimProfile(unsigned char *bytes, size_t size, unsigned kind) {
    if (kind == 3) {
        TimRegionalCounts counts;
        return tim_regional_from_payload(bytes, size, &counts) && (counts.traveler || counts.path);
    }
    if ((kind != 1 && kind != 2) || !bytes || size > UINT32_MAX) return 0;
    Dz1Error e = DZ1_ERROR_INITIALIZER;
    Dz1Binary input = {bytes, (u32_t)size}, *raw = NULL;
    ASN1WorkSpace ws;
    ASN1_INIT_WS_INFO(&ws);
    TravelerInformation value;
    int id = 0, valid = 0;
    raw = GitsnAsnUtil_getValueFromMessageFrame(&input, &id, &e);
    if (!raw || id != 31 || !TravelerInformation_uper_decode(&ws, raw, &value, &e)) goto check_done;
    if (!value.DEF_TravelerInformation_packetID || value.packetID.numbits != 9 || value.dataFrames.count != 1) goto check_done;
    TravelerDataFrame *frame = ASN1_Get_Node_Index(&value.dataFrames, 1);
    if (!frame || !frame->msgId || !frame->content || !frame->DEF_TravelerDataFrame_startYear ||
        frame->regions.count != 1 || frame->notUsed || frame->notUsed1 || frame->notUsed2 || frame->notUsed3 ||
        frame->msgId->M != DEF_TravelerDataFrame_msgId_furtherInfoID ||
        frame->msgId->elements.furtherInfoID.numbits != 2 ||
        frame->msgId->elements.furtherInfoID.data[0] != 0x0c || frame->msgId->elements.furtherInfoID.data[1] != kind ||
        frame->content->M != DEF_TravelerDataFrame_content_advisory || frame->content->elements.advisory.count != 1) goto check_done;
    ITIScodesAndText_element *item = ASN1_Get_Node_Index(&frame->content->elements.advisory, 1);
    if (!item || !item->item || item->item->M != DEF_ITIScodesAndText_element_item_itis) goto check_done;
    long long code = item->item->elements.itis;
    valid = kind == 1 ? (code == 7443 || code == 7444) : (code == 7427 || code == 7428 || code == 7436);
check_done:
    Dz1Binary_del(raw); ASN1_INIT_WS_INFO_cancel(&ws);
    return valid;
}
