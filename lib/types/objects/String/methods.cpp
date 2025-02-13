#include "types/objects/JsString.hpp"
#include "utils/Convert.hpp"

// override
std::optional<JS::Attribute> JS::String::getOwnProperty(const std::string &key) const {
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
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::valueOf(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::charAt(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::charCodeAt(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::concat(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::indexOf(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::lastIndexOf(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::localeCompare(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::match(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::replace(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::search(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::slice(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::split(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::substring(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::toLowerCase(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::toLocaleLowerCase(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::toUpperCase(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::toLocaleUpperCase(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::String::trim(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

