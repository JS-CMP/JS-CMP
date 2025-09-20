#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsNumber.hpp"
#include "utils/Convert.hpp"

namespace JS {
Number::Number() : JS::InternalObject({}, getPrototypeProperties(), ERROR_CLASS_NAME, true) {
    this->primitiveValue = 0.0;
}

Number::Number(const JS::Any& value) : JS::InternalObject({}, getPrototypeProperties(), ERROR_CLASS_NAME, true) {
    double v = JS::CONVERT::ToNumber(value);
    this->primitiveValue = v;
}

// Static constructor for properties
Number::Number(const JS::Properties& properties)
    : JS::InternalObject(properties, JS::Function::getPrototypeProperties(), ERROR_CLASS_NAME, true) {
    this->defineOwnProperty(u"prototype", JS::DataDescriptor{JS::Any(getPrototypeProperties()), false, false, false});
    this->call_function = &JS::Number::internal_call;
    this->construct = &JS::Number::internal_constructor;
}
} // namespace JS