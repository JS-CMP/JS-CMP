#include "types/objects/JsFunction.hpp"
#include "types/objects/Object/JsObject.hpp"
#include "types/objects/Object/PrototypeProperties.hpp"
#include <utility>

namespace JS {

Object::Object() : JS::InternalObject({}, JS::PrototypeProperties::get(), "Object", true) {
    this->defineOwnProperty("prototype", DataDescriptor({
            JS::Any(JS::PrototypeProperties::get()),
            false,
            false,
            false,
    }));
}

Object::Object(const std::unordered_map<std::string, JS::Any>& properties)
    : JS::InternalObject({}, JS::PrototypeProperties::get(), "Object", true) {
    for (const auto& [key, value] : properties) {
        this->InternalObject::put(key, value);
    }
    this->defineOwnProperty("prototype", DataDescriptor({
        JS::Any(JS::PrototypeProperties::get()),
        false,
        false,
        false,
    }));
}

Object::Object(const Attribute& attribute) : JS::InternalObject(attribute) {
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
            (*properties)["get"] = desc.get == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(desc.get);
            (*properties)["set"] = desc.set == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(desc.set);
            (*properties)["enumerable"] = JS::Any(desc.enumerable);
            (*properties)["configurable"] = JS::Any(desc.configurable);
        }
    }
    this->defineOwnProperty("prototype", DataDescriptor({
            JS::Any(JS::PrototypeProperties::get()),
            false,
            false,
            false,
    }));
}

Object::Object(const InternalObject&& internalObject) : JS::InternalObject(internalObject) {}
} // namespace JS