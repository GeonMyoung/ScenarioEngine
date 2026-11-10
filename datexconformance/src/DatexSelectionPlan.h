#pragma once
#include "DatexCore.h"
#include <algorithm>

namespace datex {
struct SelectionStep {
    std::string test;
    Case counterpart;
    bool requestData;
};
// Fixture/operation preparation only. Replies and rejection reasons continue to
// be derived from actual wire messages by the independent counterpart.
inline std::vector<SelectionStep> selectionPlan(const Case &tester, const std::string &source) {
    auto json = Json::parse(source);
    auto id = json.get("case"), tests = json.get("tests");
    if (!id || id->kind != Json::String || id->text != tester.id ||
        !tests || tests->kind != Json::Array || tests->array.empty())
        throw Failure("Selection plan must name this case and at least one test");
    auto allowed = availableTests(tester);
    std::set<std::string> selected;
    for (const auto &value : tests->array) {
        if (value.kind != Json::String) throw Failure("Selection entries must be testName strings");
        auto key = value.text;
        if (key.compare(0,5,"test_")==0) key.erase(0,5);
        if (std::find(allowed.begin(), allowed.end(), key)==allowed.end()) throw Failure("Unknown selected test: " + key);
        if (!selected.insert(key).second) throw Failure("Duplicate selected test: " + key);
    }
    std::vector<SelectionStep> plan;
    for (const auto &test : allowed) if (selected.count(test)) {
        auto message = tester.messages.front();
        if (test.compare(0,7,"normal_")==0) {
            auto found = std::find_if(tester.messages.begin(), tester.messages.end(), [&](const Message &m){return test==std::string("normal_")+m.name;});
            if (found==tester.messages.end()) throw Failure("Selected message is not supported");
            message = *found;
        }
        auto peer = messageCase(tester, message);
        peer.role = tester.role == Role::Client ? Role::Server : Role::Client;
        plan.push_back({test, std::move(peer), test!="session" && test!="login_retry"});
    }
    return plan;
}
} // namespace datex
