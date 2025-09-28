#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsBoolean.hpp"

#include <utils/Convert.hpp>

namespace JS {

Boolean::Boolean(const JS::Any& value) : InternalObject({}, getPrototypeProperties(), BOOL_CLASS_NAME, true) {
    bool v = CONVERT::ToBoolean(value);
    this->primitiveValue = v;
}

} // namespace JS