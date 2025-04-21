#include "internals/Attribute.hpp"
#include "internals/Object.hpp"

namespace JS {
InternalObject::InternalObject(Properties properties, std::shared_ptr<InternalObject> prototype, std::string class_name,
                               bool extensible)
    : properties(std::make_shared<Properties>(std::move(properties))), prototype(std::move(prototype)), call_function(nullptr),
      construct(nullptr), class_name(std::move(class_name)), extensible(extensible) {

}

InternalObject::InternalObject(const std::unordered_map<std::string, JS::Any>& properties)
    : properties(std::make_shared<Properties>()), prototype(nullptr), call_function(nullptr), construct(nullptr),
      class_name("Object"), extensible(true) {

    for (const auto& [key, value] : properties) {
        this->put(key, value);
    }
}

InternalObject::InternalObject(const Attribute& attribute)
    : properties(std::make_shared<std::unordered_map<std::string, JS::Attribute>>()), extensible(true) {
    switch (attribute.index()) {
        case DATA_DESCRIPTOR: {
            JS::DataDescriptor desc = std::get<JS::DataDescriptor>(attribute);
            (*properties)["value"] = desc.value;
            (*properties)["writable"] = JS::Any(desc.writable);
            (*properties)["enumerable"] = JS::Any(desc.enumerable);
            (*properties)["configurable"] = JS::Any(desc.configurable);
        }
        case ACCESSOR_DESCRIPTOR: {
            JS::AccessorDescriptor desc = std::get<JS::AccessorDescriptor>(attribute);
            (*properties)["get"] = desc.get == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(*desc.get);
            (*properties)["set"] = desc.set == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(*desc.set);
            (*properties)["enumerable"] = JS::Any(desc.enumerable);
            (*properties)["configurable"] = JS::Any(desc.configurable);
        }
        default:
            throw std::runtime_error("Cannot convert to property descriptor");
    }
}

InternalObject::InternalObject(const InternalObject& other)  : enable_shared_from_this(other) {
    properties = other.properties;
    prototype = other.prototype;
    class_name = other.class_name;
    extensible = other.extensible;
    call_function = other.call_function;
    construct = other.construct;

}

InternalObject::InternalObject(InternalObject&& other) noexcept {
    properties = other.properties;
    prototype = other.prototype;
    class_name = other.class_name;
    extensible = other.extensible;
    call_function = other.call_function;
    construct = other.construct;
}

InternalObject& InternalObject::operator=(InternalObject&& other) noexcept {
    properties = other.properties;
    prototype = other.prototype;
    class_name = other.class_name;
    extensible = other.extensible;
    call_function = other.call_function;
    construct = other.construct;
    return *this;
}
} // namespace JS