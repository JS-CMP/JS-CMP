#include "types/objects/Error/JsTypeError.hpp"
#include "utils/Convert.hpp"

namespace JS {
TypeError::TypeError() : JS::InternalObject({}, getPrototypeProperties(), "Error", true) {
    this->defineOwnProperty("message", JS::DataDescriptor{JS::Any(""), false, false, false});
}

TypeError::TypeError(const JS::Any& value) : JS::InternalObject({}, getPrototypeProperties(), "Error", true) {
    this->defineOwnProperty("message", JS::DataDescriptor{JS::Any(JS::CONVERT::ToString(value)), false, false, false});
}

TypeError::TypeError(const std::unordered_map<std::string, JS::Attribute>& properties)
    : InternalObject({}, getPrototypeProperties(), "Error", true) {
    for (const auto& [key, value] : properties) {
        this->InternalObject::defineOwnProperty(key, value);
    }

    if (properties.find("message") == properties.end()) {
        this->defineOwnProperty("message", JS::DataDescriptor{JS::Any(""), false, false, false});
    }
}
} // namespace JS