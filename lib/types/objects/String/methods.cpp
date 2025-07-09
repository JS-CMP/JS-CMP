#include "types/objects/JsString.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

#include <cmath>
#include <types/objects/JsObject.hpp>
#include <unicode/uchar.h>
#include <unicode/unistr.h>
#include <unicode/ustream.h>

std::optional<JS::Attribute> JS::String::getOwnProperty(const std::u16string& key) const {
    auto desc = JS::InternalObject::getOwnProperty(key);
    if (desc.has_value()) {
        return desc;
    }
    if (JS::CONVERT::ToString(abs(JS::CONVERT::ToInteger(key))) == key) {
        return std::nullopt;
    }
    if (this->primitiveValue.index() != JS::STRING) {
        throw std::runtime_error("Unexpected primitive value"); // should not happen
    }
    Rope str = std::get<Rope>(this->primitiveValue);
    int index = JS::CONVERT::ToInteger(key);
    size_t len = str.length();
    if (len <= index) {
        return std::nullopt;
    }
    return JS::DataDescriptor(JS::Any(std::u16string(1, str[index])), false, false, false);
}

// prototype methods
JS::Any JS::String::toString(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Object(thisArg, u"String") && !JS::COMPARE::Type(thisArg, JS::STRING)) {
        throw std::runtime_error("TypeError: String.prototype.toString called on non-object");
    }
    return JS::Any(std::get<Rope>(std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())->primitiveValue).toString());
}

JS::Any JS::String::valueOf(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Object(thisArg, u"String") && !JS::COMPARE::Type(thisArg, JS::STRING)) {
        throw std::runtime_error("TypeError: String.prototype.valueOf called on non-object");
    }
    return thisArg;
}

JS::Any JS::String::charAt(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    Rope S = JS::CONVERT::ToRope(thisArg); // aka convert to string but faster
    int position = JS::CONVERT::ToInteger(args[u"0"]);
    uint32_t size = JS::CONVERT::ToUint32(static_cast<unsigned int>(S.length()));
    if (position < 0 || position >= size) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(std::u16string(1, S[position]));
}

JS::Any JS::String::charCodeAt(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    Rope S = JS::CONVERT::ToRope(thisArg); // aka convert to string but faster
    int position = JS::CONVERT::ToInteger(args[u"0"]);
    uint32_t size = S.length();
    if (position < 0 || position >= size) {
        return JS::Any(std::nan(""));
    }
    return JS::Any(static_cast<unsigned int>(S[position]));
}

JS::Any JS::String::concat(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    Rope S = JS::CONVERT::ToRope(thisArg); // aka convert to string but faster
    uint32_t size = JS::CONVERT::ToUint32(args[u"length"]);
    for (uint32_t k = 0; k < size; k++) {
        S = S + Rope(JS::CONVERT::ToString(args[k]));
    }
    return JS::Any(Rope(std::move(S)));
}

JS::Any JS::String::indexOf(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    Rope S = JS::CONVERT::ToRope(thisArg); // aka convert to string but faster
    std::u16string searchStr = JS::CONVERT::ToString(args[u"0"]);
    int position;
    if (JS::COMPARE::Type(args[u"1"], JS::UNDEFINED)) {
        position = 0;
    } else {
        position = JS::CONVERT::ToInteger(args[u"1"]);
    }
    size_t foundPos = S.find(searchStr, static_cast<size_t>(position));
    return JS::Any(foundPos == std::u16string::npos ? -1 : static_cast<unsigned int>(foundPos));
}

JS::Any JS::String::lastIndexOf(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    Rope S = JS::CONVERT::ToRope(thisArg);
    std::u16string searchStr = JS::CONVERT::ToString(args[u"0"]);
    int position;
    if (JS::COMPARE::Type(args[u"1"], JS::UNDEFINED)) {
        position = S.length();
    } else {
        position = JS::CONVERT::ToInteger(args[1]);
    }
    return JS::Any(static_cast<int>(S.rfind(searchStr, position)));
}

JS::Any JS::String::localeCompare(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    Rope S = JS::CONVERT::ToRope(thisArg);
    Rope that = JS::CONVERT::ToRope(args[u"0"]);
    return JS::Any(S.compare(that));
}

JS::Any JS::String::match(const JS::Any& thisArg, const JS::Any& args) {
    // TODO NEED REGEXP
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::replace(const JS::Any& thisArg, const JS::Any& args) {
    // TODO NEED REGEXP
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::search(const JS::Any& thisArg, const JS::Any& args) {
    // TODO NEED REGEXP
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::slice(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    std::u16string S = JS::CONVERT::ToString(thisArg);
    uint32_t len = S.length();
    int intStart = JS::CONVERT::ToInteger(args[u"0"]);
    int intEnd;
    if (JS::COMPARE::Type(args[u"1"], JS::UNDEFINED)) {
        intEnd = static_cast<int>(len);
    } else {
        intEnd = JS::CONVERT::ToInteger(args[u"1"]);
    }
    uint32_t from = intStart < 0 ? std::max(len + intStart, 0U) : std::min(intStart, static_cast<int>(len));
    uint32_t to = intEnd < 0 ? std::max(len + intEnd, 0U) : std::min(intEnd, static_cast<int>(len));
    uint32_t span = std::max(to - from, 0U);
    return JS::Any(S.substr(from, span));
}

JS::Any JS::String::split(const JS::Any& thisArg, const JS::Any& args) {
    // TODO NEED REGEXP AND ARRAY
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::substring(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    Rope S = JS::CONVERT::ToRope(thisArg);
    uint32_t len = S.length();
    uint32_t intStart = JS::CONVERT::ToInteger(args[u"0"]);
    uint32_t intEnd;
    if (JS::COMPARE::Type(args[u"1"], JS::UNDEFINED)) {
        intEnd = len;
    } else {
        intEnd = JS::CONVERT::ToInteger(args[u"1"]);
    }
    uint32_t from = std::min(std::max(intStart, 0U), len);
    uint32_t to = std::min(std::max(intEnd, 0U), len);
    if (from > to) {
        std::swap(from, to);
    }
    return JS::Any(S.substr(from, to - from));
}

JS::Any JS::String::toLowerCase(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    std::u16string S = JS::CONVERT::ToString(thisArg);
    icu::UnicodeString ustr(reinterpret_cast<const UChar*>(S.data()), S.length());
    ustr.toLower();
    std::u16string result(reinterpret_cast<const char16_t*>(ustr.getBuffer()), ustr.length());
    return JS::Any(result);
}

JS::Any JS::String::toLocaleLowerCase(const JS::Any& thisArg, const JS::Any& args) {
    return toLowerCase(thisArg, args);
}

JS::Any JS::String::toUpperCase(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    std::u16string S = JS::CONVERT::ToString(thisArg);
    icu::UnicodeString ustr(reinterpret_cast<const UChar*>(S.data()), S.length());
    ustr.toUpper();
    std::u16string result(reinterpret_cast<const char16_t*>(ustr.getBuffer()), ustr.length());
    return JS::Any(result);
}

JS::Any JS::String::toLocaleUpperCase(const JS::Any& thisArg, const JS::Any& args) {
    return toUpperCase(thisArg, args);
}

JS::Any JS::String::trim(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    Rope S = JS::CONVERT::ToRope(thisArg); // aka convert to string
    // maybe faster in string
    int32_t start = 0;
    int32_t end = S.length();
    while (start < end && u_isUWhiteSpace(S[start])) {
        ++start;
    }
    while (end > start && u_isUWhiteSpace(S[end - 1])) {
        --end;
    }
    return JS::Any(S.substr(start, end - start));
}
