#include "internals/Attribute.hpp"
#include "internals/Object.hpp"

namespace JS {
InternalObject::InternalObject(Properties properties, std::shared_ptr<InternalObject> prototype, std::u16string class_name, bool extensible) : properties(std::make_shared<Properties>(std::move(properties))), prototype(std::move(prototype)), call_function(nullptr), construct(nullptr), class_name(std::move(class_name)), extensible(extensible) {}

InternalObject::InternalObject(const std::unordered_map<std::u16string, JS::Any>& properties) : properties(std::make_shared<Properties>()), prototype(nullptr), call_function(nullptr), construct(nullptr), class_name(OBJECT_CLASS_NAME), extensible(true) {

    for (const auto& [key, value] : properties) {
        this->InternalObject::put(key, value);
    }
}

InternalObject::InternalObject(const Attribute& attribute) : properties(std::make_shared<std::unordered_map<std::u16string, JS::Attribute>>()), extensible(true) {
    switch (attribute.index()) {
        case DATA_DESCRIPTOR: {
            JS::DataDescriptor desc = std::get<JS::DataDescriptor>(attribute);
            this->InternalObject::put(u"value", desc.value);
            this->InternalObject::put(u"writable", JS::Any(desc.writable));
            this->InternalObject::put(u"enumerable", JS::Any(desc.enumerable));
            this->InternalObject::put(u"configurable", JS::Any(desc.configurable));
        }
        case ACCESSOR_DESCRIPTOR: {
            JS::AccessorDescriptor desc = std::get<JS::AccessorDescriptor>(attribute);
            this->InternalObject::put(u"get", desc.get == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(desc.get));
            this->InternalObject::put(u"set", desc.set == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(desc.set));
            this->InternalObject::put(u"enumerable", JS::Any(desc.enumerable));
            this->InternalObject::put(u"configurable", JS::Any(desc.configurable));
        }
        default:
            throw std::runtime_error("Cannot convert to property descriptor");
    }
}

InternalObject::InternalObject(const InternalObject& other) : enable_shared_from_this(other) {
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