#include "types/objects/JsBoolean.hpp"

#include <utils/Convert.hpp>

namespace JS {
Boolean::Boolean() : InternalObject({}, getPrototypeProperties(), u"Boolean", true) {
    this->primitiveValue = true;
    this->defineOwnProperty(u"length", JS::DataDescriptor{Any(1), false, false, false});
    this->defineOwnProperty(u"prototype", JS::DataDescriptor{Any(getPrototypeProperties()), false, false, false});
}

Boolean::Boolean(const JS::Any& value) : InternalObject({}, getPrototypeProperties(), u"Boolean", true) {
    bool v = CONVERT::ToBoolean(value);
    this->primitiveValue = v;
    this->defineOwnProperty(u"length", JS::DataDescriptor{Any(1), false, false, false});
    this->defineOwnProperty(u"prototype", JS::DataDescriptor{Any(getPrototypeProperties()), false, false, false});
}

} // namespace JS