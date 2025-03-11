#include "types/objects/Error/JsURIError.hpp"
#include "utils/Convert.hpp"

namespace JS {
UriError::UriError() : JS::InternalObject({}, getPrototypeProperties(), "Error", true) {
    this->defineOwnProperty("message", JS::DataDescriptor{JS::Any(""), false, false, false});
}

UriError::UriError(const JS::Any& value) : JS::InternalObject({}, getPrototypeProperties(), "Error", true) {
    this->defineOwnProperty("message", JS::DataDescriptor{JS::Any(JS::CONVERT::ToString(value)), false, false, false});
}

UriError::UriError(const std::unordered_map<std::string, JS::Attribute>& properties)
    : InternalObject({}, getPrototypeProperties(), "Error", true) {
    for (const auto& [key, value] : properties) {
        this->InternalObject::defineOwnProperty(key, value);
    }

    if (properties.find("message") == properties.end()) {
        this->defineOwnProperty("message", JS::DataDescriptor{JS::Any(""), false, false, false});
    }
}
} // namespace JS