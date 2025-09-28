#include "types/objects/Error/JsReferenceError.hpp"
#include "utils/Convert.hpp"

namespace JS {
ReferenceError::ReferenceError(const JS::Any& value) : JS::Error(value, JS::ReferenceError::getPrototypeProperties()) {}

ReferenceError::ReferenceError(const std::unordered_map<std::u16string, JS::Attribute>& properties)
    : JS::Error(properties, JS::ReferenceError::getPrototypeProperties()) {
    this->call_function = &JS::ReferenceError::internal_call;
    this->construct = &JS::ReferenceError::internal_constructor;
}
} // namespace JS