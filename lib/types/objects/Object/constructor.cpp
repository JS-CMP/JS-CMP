#include "types/objects/JsObject.hpp"

namespace JS {
Object::Object(const Attribute& attribute)
    : properties(std::make_shared<std::unordered_map<std::string, JS::Attribute>>()) {
    properties->operator[]("value") = attribute.value;
    properties->operator[]("writable") = JS::Any(attribute.writable);
    properties->operator[]("enumerable") = JS::Any(attribute.enumerable);
    properties->operator[]("configurable") = JS::Any(attribute.configurable);
}

Object::Object(const Object& other) { properties = other.properties; }

Object::Object(Object&& other) noexcept { properties = other.properties; }

Object& Object::operator=(const Object& other) {
    properties = other.properties;
    return *this;
}

Object& Object::operator=(Object&& other) noexcept {
    properties = other.properties;
    return *this;
}
bool Object::isCallable() const { return true; }
} // namespace JS