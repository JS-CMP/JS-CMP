#include "types/objects/JsArray.hpp"
#include "types/objects/JsRegExp.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

#include <cmath>
#include <types/objects/Error/JsTypeError.hpp>
#include <types/objects/JsObject.hpp>
#include <unicode/uchar.h>

using Iter = std::u16string::const_iterator;

std::optional<JS::Match> JS::RegExp::match(const std::u16string& str, uint32_t pos) const {
    boost::match_results<Iter> match;

    Iter begin = str.begin() + pos;
    Iter end = str.end();

    if (boost::regex_search(begin, end, match, expression)) {
        std::vector<std::optional<std::u16string>> captures;
        for (std::size_t i = 1; i < match.size(); ++i) {
            if (match[i].matched) {
                captures.emplace_back(std::u16string(match[i].first, match[i].second));
            } else {
                captures.emplace_back(); // empty if unmatched
            }
        }

        return Match{
            .index = static_cast<uint32_t>(match[0].first - str.begin()),
            .string = std::u16string(match[0].first, match[0].second),
            .groups = std::move(captures),
        };
    }
    return std::nullopt;
}

// prototype methods
JS::Any JS::RegExp::exec(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(thisArg, JS::OBJECT) ||
        std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())->class_name != u"RegExp") {
        throw JS::Any(TypeError(JS::Any("this is not a RegExp object")));
    }
    std::shared_ptr<JS::InternalObject> R = std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue());
    std::u16string S = JS::CONVERT::ToString(args[0]);
    size_t length = S.length();
    int i = JS::CONVERT::ToInteger(R->get(u"lastIndex"));
    bool global = JS::CONVERT::ToBoolean(R->get(u"global"));
    if (!global) {
        i = 0;
    }
    bool matchSucceeded = false;
    std::optional<JS::Match> r;
    while (!matchSucceeded) {
        if (i < 0 || static_cast<size_t>(i) > length) {
            R->put(u"lastIndex", JS::Any(0), true);
            return JS::Any(JS::Null());
        }
        r = R->match(S, static_cast<uint32_t>(i));
        if (!r.has_value()) {
            ++i;
        } else {
            i = static_cast<int>(r->index); // Update i to the start index of the match to make it faster
            matchSucceeded = true;
        }
    }
    if (global) {
        R->put(u"lastIndex", JS::Any(static_cast<uint32_t>(i + r->string.length())), true);
    }
    size_t n = r->groups.size();
    JS::Array A = JS::Array();
    int matchIndex = i;
    A.defineOwnProperty(u"index", JS::DataDescriptor{JS::Any(matchIndex), true, true, true}, true);
    A.defineOwnProperty(u"input", JS::DataDescriptor{JS::Any(S), true, true, true}, true);
    A.defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(static_cast<uint32_t>(n + 1))}, true);
    std::u16string matchedSubstr = r->string;
    A.defineOwnProperty(u"0", JS::DataDescriptor{JS::Any(matchedSubstr), true, true, true}, true);
    for (uint32_t j = 1; j <= n; ++j) {
        JS::Any captureI = r->groups[j - 1].has_value() ? JS::Any(r->groups[j - 1].value()) : JS::Any();
        A.defineOwnProperty(JS::CONVERT::ToString(j), JS::DataDescriptor{JS::Any(captureI), true, true, true}, true);
    }
    return JS::Any(A);
}

JS::Any JS::RegExp::test(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(!JS::COMPARE::Type(JS::RegExp::exec(thisArg, args), JS::NULL_TYPE));
}

JS::Any JS::RegExp::toString(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(thisArg, JS::OBJECT) ||
        std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())->class_name != u"RegExp") {
        throw JS::Any(TypeError(JS::Any("This is not a RegExp object")));
    }
    std::shared_ptr<JS::InternalObject> R = std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue());
    std::u16string source = JS::CONVERT::ToString(R->get(u"source"));
    std::u16string flags;
    if (JS::CONVERT::ToBoolean(R->get(u"global"))) {
        flags += u'g';
    }
    if (JS::CONVERT::ToBoolean(R->get(u"ignoreCase"))) {
        flags += u'i';
    }
    if (JS::CONVERT::ToBoolean(R->get(u"multiline"))) {
        flags += u'm';
    }
    return JS::Any(u"/" + source + u"/" + flags);
}