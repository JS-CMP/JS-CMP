#include "types/objects/Error/JsNativeError.hpp"
#include "utils/Convert.hpp"

namespace JS {
NativeError::NativeError() : JS::Error(JS::NativeError::getPrototypeProperties()) {}

NativeError::NativeError(const JS::Any& value) : JS::Error(value, JS::NativeError::getPrototypeProperties()) {}

NativeError::NativeError(const std::unordered_map<std::u16string, JS::Attribute>& properties)
    : JS::Error(properties, JS::NativeError::getPrototypeProperties()) {
    this->call_function = &JS::NativeError::internal_call;
    this->construct = &JS::NativeError::internal_constructor;
}
} // namespace JS