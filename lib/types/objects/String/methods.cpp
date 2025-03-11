#include "types/objects/JsString.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

#include <types/objects/JsObject.hpp>

// TODO ToString should return a rope not a std::string
// TODO should change string to utf-16 code unit
// TODO in rope then recode operator [], find, rfind, substr, toLowerCase, toUpperCase, trim for rope, all of this function

// override
std::optional<JS::Attribute> JS::String::getOwnProperty(const std::string& key) const {
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
    int len = str.length();
    if (len <= index) {
        return std::nullopt;
    }
    auto resultStr = str.toString()[index]; // TODO:: make [] operator in ropes
    return JS::DataDescriptor(JS::Any(resultStr), false, false, false);
}

// prototype methods
JS::Any JS::String::toString(const JS::Any& thisArg, const JS::Any& args) {
    if ((!JS::COMPARE::Type(thisArg, JS::OBJECT) ||
        std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())->class_name != "String") &&
        !JS::COMPARE::Type(thisArg, JS::STRING)) {
        throw std::runtime_error("TypeError: String.prototype.valueOf called on non-object");
    }
    return thisArg;
}

JS::Any JS::String::valueOf(const JS::Any& thisArg, const JS::Any& args) {
    if ((!JS::COMPARE::Type(thisArg, JS::OBJECT) ||
        std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())->class_name != "String") &&
        !JS::COMPARE::Type(thisArg, JS::STRING)) {
        throw std::runtime_error("TypeError: String.prototype.valueOf called on non-object");
    }
    return thisArg;
}

JS::Any JS::String::charAt(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    JS::Any S = thisArg["toString"]();
    int position = JS::CONVERT::ToInteger(args["0"]);
    uint32_t size = JS::CONVERT::ToUint32(S["length"]);
    if (position < 0 || position >= size) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    std::string str =
        std::get<Rope>(std::get<std::shared_ptr<JS::InternalObject>>(S.getValue())->primitiveValue).toString();
    return JS::Any(std::string(1, str[position])); // TODO:: make [] operator in ropes
}

JS::Any JS::String::charCodeAt(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    std::string S = JS::CONVERT::ToString(thisArg);
    int position = JS::CONVERT::ToInteger(args["0"]);
    uint32_t size = S.length();
    if (position < 0 || position >= size) {
        return JS::Any(std::nan(""));
    }
    return JS::Any(static_cast<int>(S[position])); // TODO:: make [] operator in ropes
}

JS::Any JS::String::concat(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    std::string S = JS::CONVERT::ToString(thisArg);
    Rope R = Rope(S);
    uint32_t size = JS::CONVERT::ToUint32(args["length"]);
    for (uint32_t k = 0; k < size; k++) {
        R = R + Rope(JS::CONVERT::ToString(args[k]));
    }
    return JS::Any(Rope(std::move(R)));
}

JS::Any JS::String::indexOf(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    std::string S = JS::CONVERT::ToString(thisArg);
    std::string searchStr = JS::CONVERT::ToString(args["0"]);
    int position;
    if (JS::COMPARE::Type(args["1"], JS::UNDEFINED)) {
        position = 0;
    } else {
        position = JS::CONVERT::ToInteger(args["1"]);
    }
    return JS::Any(static_cast<int>(S.find(searchStr, position)));
}

JS::Any JS::String::lastIndexOf(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    std::string S = JS::CONVERT::ToString(thisArg);
    std::string searchStr = JS::CONVERT::ToString(args["0"]);
    int position;
    if (JS::COMPARE::Type(args["1"], JS::UNDEFINED)) {
        position = S.length();
    } else {
        position = JS::CONVERT::ToInteger(args[1]);
    }
    return JS::Any(static_cast<int>(S.rfind(searchStr, position)));
}

JS::Any JS::String::localeCompare(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    std::string S = JS::CONVERT::ToString(thisArg);
    std::string that = JS::CONVERT::ToString(args["0"]);
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
    std::string S = JS::CONVERT::ToString(thisArg);
    uint32_t len = S.length();
    int intStart = JS::CONVERT::ToInteger(args["0"]);
    int intEnd;
    if (JS::COMPARE::Type(args["1"], JS::UNDEFINED)) {
        intEnd = static_cast<int>(len);
    } else {
        intEnd = JS::CONVERT::ToInteger(args["1"]);
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
    std::string S = JS::CONVERT::ToString(thisArg);
    uint32_t len = S.length();
    uint32_t intStart = JS::CONVERT::ToInteger(args["0"]);
    uint32_t intEnd;
    if (JS::COMPARE::Type(args["1"], JS::UNDEFINED)) {
        intEnd = len;
    } else {
        intEnd = JS::CONVERT::ToInteger(args["1"]);
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
    std::string S = JS::CONVERT::ToString(thisArg);
    return JS::Any(S /*.toLowerCase()*/); // TODO:: make toLowerCase in ropes
}

JS::Any JS::String::toLocaleLowerCase(const JS::Any& thisArg, const JS::Any& args) {
    return toLowerCase(thisArg, args);
}

JS::Any JS::String::toUpperCase(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    std::string S = JS::CONVERT::ToString(thisArg);
    return JS::Any(S /*.toUpperCase()*/); // TODO:: make toUpperCase in ropes
}

JS::Any JS::String::toLocaleUpperCase(const JS::Any& thisArg, const JS::Any& args) {
    return toUpperCase(thisArg, args);
}

JS::Any JS::String::trim(const JS::Any& thisArg, const JS::Any& args) {
    JS::COMPARE::CheckObjectCoercible(thisArg);
    std::string S = JS::CONVERT::ToString(thisArg);
    return JS::Any(S /*.trim()*/); // TODO:: make trim in ropes
}
