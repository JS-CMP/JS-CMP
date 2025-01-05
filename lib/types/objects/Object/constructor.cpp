#include "types/objects/JsObject.hpp"

namespace JS {
Object::Object() : JS::InternalObject() {}

Object::Object(const Attribute& attribute) : JS::InternalObject() {
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
    }
}

Object::Object(const InternalObject& internalObject) : JS::InternalObject(internalObject) {}
} // namespace JS