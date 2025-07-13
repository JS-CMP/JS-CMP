#include "types/objects/Error/JsURIError.hpp"
#include "utils/Convert.hpp"

namespace JS {
UriError::UriError() : JS::InternalObject({}, getPrototypeProperties(), u"Error", true) {
    this->defineOwnProperty(u"message", JS::DataDescriptor{JS::Any(u""), false, false, false});
}

UriError::UriError(const JS::Any& value) : JS::InternalObject({}, getPrototypeProperties(), u"Error", true) {
    this->defineOwnProperty(u"message", JS::DataDescriptor{JS::Any(JS::CONVERT::ToString(value)), false, false, false});
}

UriError::UriError(const std::unordered_map<std::u16string, JS::Attribute>& properties)
    : InternalObject({}, getPrototypeProperties(), u"Error", true) {
    for (const auto& [key, value] : properties) {
        this->InternalObject::defineOwnProperty(key, value);
    }

    if (properties.find(u"message") == properties.end()) {
        this->defineOwnProperty(u"message", JS::DataDescriptor{JS::Any(u""), false, false, false});
    }
}
} // namespace JS