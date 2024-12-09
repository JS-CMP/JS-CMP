#include "types/objects/JsObject.hpp"

namespace JS {
Object::Object(const Attribute& attribute)
    : properties(std::make_shared<std::unordered_map<std::string, JS::Attribute>>()) {
    switch (attribute.index()) {
        case DATA_DESCRIPTOR: {
            JS::DataDescriptor desc = std::get<JS::DataDescriptor>(attribute);
            properties->operator[]("value") = desc.value;
            properties->operator[]("writable") = JS::Any(desc.writable);
            properties->operator[]("enumerable") = JS::Any(desc.enumerable);
            properties->operator[]("configurable") = JS::Any(desc.configurable);
        }
        case ACCESSOR_DESCRIPTOR: {
            JS::AccessorDescriptor desc = std::get<JS::AccessorDescriptor>(attribute);
            properties->operator[]("get") = desc.get == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(*desc.get);
            properties->operator[]("set") = desc.set == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(*desc.set);
            properties->operator[]("enumerable") = JS::Any(desc.enumerable);
            properties->operator[]("configurable") = JS::Any(desc.configurable);
        }
    }
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