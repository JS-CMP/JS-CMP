#include "types/objects/Error/JsRangeError.hpp"
#include "utils/Convert.hpp"

namespace JS {
RangeError::RangeError() : JS::Error(JS::RangeError::getPrototypeProperties()) {
}

RangeError::RangeError(const JS::Any& value) : JS::Error(value, JS::RangeError::getPrototypeProperties()) {
}

RangeError::RangeError(const std::unordered_map<std::u16string, JS::Attribute>& properties)
    : JS::Error(properties, JS::RangeError::getPrototypeProperties()) {
    this->call_function = &JS::RangeError::internal_call;
    this->construct = &JS::RangeError::internal_constructor;
}
} // namespace JS