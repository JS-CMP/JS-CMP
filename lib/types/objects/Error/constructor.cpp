#include "types/objects/Error/JsError.hpp"
#include "types/objects/Function/JsFunction.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

namespace JS {
Error::Error(const std::shared_ptr<JS::InternalObject>& prototype)
    : JS::InternalObject({}, prototype == nullptr ? JS::Error::getPrototypeProperties() : prototype, u"Error", true) {}

Error::Error(const JS::Any& value, const std::shared_ptr<JS::InternalObject>& prototype)
    : JS::InternalObject({}, prototype == nullptr ? JS::Error::getPrototypeProperties() : prototype, u"Error", true) {
    if (JS::COMPARE::Type(value, JS::UNDEFINED)) {
        return;
    }
    this->InternalObject::defineOwnProperty(
        u"message", JS::DataDescriptor{JS::Any(JS::CONVERT::ToString(value)), false, false, false});
}

Error::Error(const std::unordered_map<std::u16string, JS::Attribute>& properties,
             const std::shared_ptr<JS::InternalObject>& prototype)
    : InternalObject(properties, JS::Function::getPrototypeProperties(), u"Error", true) {
    this->InternalObject::defineOwnProperty(
        u"prototype",
        JS::DataDescriptor{JS::Any(prototype == nullptr ? JS::Error::getPrototypeProperties() : prototype), false,
                           false, true});
    this->call_function = &Error::internal_call;
    this->construct = &Error::internal_constructor;
}
} // namespace JS