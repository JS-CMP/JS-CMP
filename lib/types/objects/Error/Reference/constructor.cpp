#include "types/objects/Error/JsReferenceError.hpp"
#include "utils/Convert.hpp"

namespace JS {
ReferenceError::ReferenceError(const JS::Any& value) : JS::Error(value, JS::ReferenceError::getPrototypeProperties()) {}

} // namespace JS