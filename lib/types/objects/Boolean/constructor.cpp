#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsBoolean.hpp"

#include <utils/Convert.hpp>

namespace JS {
Boolean::Boolean() : InternalObject({}, getPrototypeProperties(), u"Boolean", true) {
    this->primitiveValue = false;
}

Boolean::Boolean(const JS::Any& value) : InternalObject({}, getPrototypeProperties(), u"Boolean", true) {
    bool v = CONVERT::ToBoolean(value);
    this->primitiveValue = v;
}

// Static constructor for properties
Boolean::Boolean(const JS::Properties& properties) : InternalObject(properties, JS::Function::getPrototypeProperties(), u"Boolean", true) {
    this->defineOwnProperty(u"prototype", JS::DataDescriptor{JS::Any(getPrototypeProperties()), false, false, false});
    this->call_function = &JS::Boolean::internal_call;
    this->construct = &JS::Boolean::internal_constructor;
}

} // namespace JS