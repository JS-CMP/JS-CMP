#include "types/objects/Error/JsTypeError.hpp"
#include "utils/Convert.hpp"

namespace JS {
TypeError::TypeError(const JS::Any& value) : JS::Error(value, JS::TypeError::getPrototypeProperties()) {}
} // namespace JS