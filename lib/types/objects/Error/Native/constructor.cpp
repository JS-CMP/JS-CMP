#include "types/objects/Error/JsNativeError.hpp"
#include "utils/Convert.hpp"

namespace JS {
NativeError::NativeError() : JS::InternalObject({}, getPrototypeProperties(), "Error", true) {
    this->defineOwnProperty("message", JS::DataDescriptor{JS::Any(""), false, false, false});
}

NativeError::NativeError(const JS::Any& value) : JS::InternalObject({}, getPrototypeProperties(), "Error", true) {
    this->defineOwnProperty("message", JS::DataDescriptor{JS::Any(JS::CONVERT::ToString(value)), false, false, false});
}

NativeError::NativeError(const std::unordered_map<std::string, JS::Attribute>& properties)
    : InternalObject({}, getPrototypeProperties(), "Error", true) {
    for (const auto& [key, value] : properties) {
        this->InternalObject::defineOwnProperty(key, value);
    }

    if (properties.find("message") == properties.end()) {
        this->defineOwnProperty("message", JS::DataDescriptor{JS::Any(""), false, false, false});
    }
}
} // namespace JS