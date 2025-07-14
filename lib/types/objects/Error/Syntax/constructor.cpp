#include "types/objects/Error/JsSyntaxError.hpp"
#include "utils/Convert.hpp"

namespace JS {
SyntaxError::SyntaxError() : JS::Error(JS::SyntaxError::getPrototypeProperties()) {
}

SyntaxError::SyntaxError(const JS::Any& value) : JS::Error(value, JS::SyntaxError::getPrototypeProperties()) {
}

SyntaxError::SyntaxError(const std::unordered_map<std::u16string, JS::Attribute>& properties)
    : JS::Error(properties, JS::SyntaxError::getPrototypeProperties()) {
    this->call_function = &JS::SyntaxError::internal_call;
    this->construct = &JS::SyntaxError::internal_constructor;
}
} // namespace JS