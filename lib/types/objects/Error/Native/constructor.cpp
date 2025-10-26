#include "types/objects/Error/JsNativeError.hpp"
#include "utils/Convert.hpp"

namespace JS {
NativeError::NativeError(const JS::Any& value) : JS::Error(value, JS::NativeError::getPrototypeProperties()) {}

} // namespace JS