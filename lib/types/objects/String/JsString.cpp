#include "types/objects/String/JsString.hpp"

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