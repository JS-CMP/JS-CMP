#include "types/objects/Error/JsRangeError.hpp"
#include "utils/Convert.hpp"

namespace JS {
RangeError::RangeError(const JS::Any& value) : JS::Error(value, JS::RangeError::getPrototypeProperties()) {}

} // namespace JS