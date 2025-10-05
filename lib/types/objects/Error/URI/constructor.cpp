#include "types/objects/Error/JsURIError.hpp"
#include "utils/Convert.hpp"

namespace JS {
URIError::URIError(const JS::Any& value) : JS::Error(value, JS::URIError::getPrototypeProperties()) {}

} // namespace JS