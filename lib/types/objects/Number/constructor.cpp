#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsNumber.hpp"
#include "utils/Convert.hpp"

namespace JS {

Number::Number(const JS::Any& value) : JS::InternalObject({}, getPrototypeProperties(), ERROR_CLASS_NAME, true) {
    double v = JS::CONVERT::ToNumber(value);
    this->primitiveValue = v;
}

} // namespace JS