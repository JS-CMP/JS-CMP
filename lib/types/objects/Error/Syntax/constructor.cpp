#include "types/objects/Error/JsSyntaxError.hpp"
#include "utils/Convert.hpp"

namespace JS {
SyntaxError::SyntaxError() : JS::InternalObject({}, getPrototypeProperties(), u"Error", true) {
    this->defineOwnProperty(u"message", JS::DataDescriptor{JS::Any(u""), false, false, false});
}

SyntaxError::SyntaxError(const JS::Any& value) : JS::InternalObject({}, getPrototypeProperties(), u"Error", true) {
    this->defineOwnProperty(u"message", JS::DataDescriptor{JS::Any(JS::CONVERT::ToString(value)), false, false, false});
}

SyntaxError::SyntaxError(const std::unordered_map<std::u16string, JS::Attribute>& properties)
    : InternalObject({}, getPrototypeProperties(), u"Error", true) {
    for (const auto& [key, value] : properties) {
        this->InternalObject::defineOwnProperty(key, value);
    }

    if (properties.find(u"message") == properties.end()) {
        this->defineOwnProperty(u"message", JS::DataDescriptor{JS::Any(""), false, false, false});
    }
}
} // namespace JS