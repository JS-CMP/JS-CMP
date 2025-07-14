#include "types/objects/Error/JsTypeError.hpp"
#include "utils/Convert.hpp"

namespace JS {
TypeError::TypeError() : JS::Error(JS::TypeError::getPrototypeProperties()) {
}

TypeError::TypeError(const JS::Any& value) : JS::Error(value, JS::TypeError::getPrototypeProperties()) {
}

TypeError::TypeError(const std::unordered_map<std::u16string, JS::Attribute>& properties)
    : JS::Error(properties, JS::TypeError::getPrototypeProperties()) {
    this->call_function = &JS::TypeError::internal_call;
    this->construct = &JS::TypeError::internal_constructor;
}
} // namespace JS