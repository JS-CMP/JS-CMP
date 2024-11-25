#include <types/objects/JsObject.hpp>

namespace JS {
JS::Any& Object::operator[](const std::string& key) { return properties->operator[](key); }

JS::Any& Object::operator[](size_t index) { return properties->operator[](std::to_string(index)); }

bool Object::hasProperty(const std::string& key) const { return properties->find(key) != properties->end(); }

bool Object::isCallable() const { return false; }

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
} // namespace JS
