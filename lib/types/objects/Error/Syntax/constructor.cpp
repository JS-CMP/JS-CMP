#include "types/objects/Error/JsSyntaxError.hpp"
#include "utils/Convert.hpp"

namespace JS {
SyntaxError::SyntaxError(const JS::Any& value) : JS::Error(value, JS::SyntaxError::getPrototypeProperties()) {}

} // namespace JS