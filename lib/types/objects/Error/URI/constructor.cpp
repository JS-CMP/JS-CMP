#include "types/objects/Error/JsURIError.hpp"
#include "utils/Convert.hpp"

namespace JS {
URIError::URIError() : JS::Error(JS::URIError::getPrototypeProperties()) {
}

URIError::URIError(const JS::Any& value) : JS::Error(value, JS::URIError::getPrototypeProperties()) {
}

URIError::URIError(const std::unordered_map<std::u16string, JS::Attribute>& properties)
    : JS::Error(properties, JS::URIError::getPrototypeProperties()) {
    this->call_function = &JS::URIError::internal_call;
    this->construct = &JS::URIError::internal_constructor;
}
} // namespace JS