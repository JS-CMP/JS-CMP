#include "types/objects/JsFunction.hpp"

#include <utility>

#include "types/objects/JsObject.hpp"

namespace JS {

std::unordered_map<std::string, JS::Any> properties_prototype = {
    {"toString", JS::Any(std::make_shared<JS::Function>(Object::toString))},
    {"toLocaleString", JS::Any(std::make_shared<JS::Function>(Object::toLocaleString))},
    {"valueOf", JS::Any(std::make_shared<JS::Function>(Object::valueOf))},
    {"hasOwnProperty", JS::Any(std::make_shared<JS::Function>(Object::hasOwnProperty))},
    {"isPrototypeOf", JS::Any(std::make_shared<JS::Function>(Object::isPrototypeOf))},
    {"propertyIsEnumerable", JS::Any(std::make_shared<JS::Function>(Object::propertyIsEnumerable))},
};
std::shared_ptr<JS::InternalObject> prototype = std::make_shared<JS::Object>(properties_prototype);

Object::Object()
    : JS::InternalObject({}, JS::prototype, "Object", true) {
}

Object::Object(const std::unordered_map<std::string, JS::Any>& properties) : JS::InternalObject({}, JS::prototype, "Object", true) {
    for (const auto& [key, value] : properties) {
        this->InternalObject::put(key, value);
    }
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
            (*properties)["get"] = desc.get == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(*desc.get);
            (*properties)["set"] = desc.set == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(*desc.set);
            (*properties)["enumerable"] = JS::Any(desc.enumerable);
            (*properties)["configurable"] = JS::Any(desc.configurable);
        }
    }
}

Object::Object(const InternalObject& internalObject)
    : JS::InternalObject(internalObject) {}
} // namespace JS