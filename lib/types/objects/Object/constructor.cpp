#include "types/objects/JsFunction.hpp"

#include <utility>

#include "types/objects/JsObject.hpp"

namespace JS {

std::unordered_map<std::string, JS::Any> properties_prototype = {
    {"toString", JS::Any(std::make_shared<JS::Function>([](const std::vector<JS::Any>& args) { return std::bind(&Object::toString, std::placeholders::_1)(args); }))},
    {"toLocaleString", JS::Any(std::make_shared<JS::Function>([](const std::vector<JS::Any>& args) { return std::bind(&Object::toLocaleString, std::placeholders::_1)(args); }))},
    {"valueOf", JS::Any(std::make_shared<JS::Function>([](const std::vector<JS::Any>& args) { return std::bind(&Object::valueOf, std::placeholders::_1)(args); }))},
    {"hasOwnProperty", JS::Any(std::make_shared<JS::Function>([](const std::vector<JS::Any>& args) { return std::bind(&Object::hasOwnProperty, std::placeholders::_1)(args); }))},
    {"isPrototypeOf", JS::Any(std::make_shared<JS::Function>([](const std::vector<JS::Any>& args) { return std::bind(&Object::isPrototypeOf, std::placeholders::_1)(args); }))},
    {"propertyIsEnumerable", JS::Any(std::make_shared<JS::Function>([](const std::vector<JS::Any>& args) { return std::bind(&Object::propertyIsEnumerable, std::placeholders::_1)(args); }))},
};
std::shared_ptr<JS::InternalObject> prototype = std::make_shared<JS::InternalObject>({}, properties_prototype);

Object::Object()
    : JS::InternalObject({}, JS::prototype, "Object", true) {
}

Object::Object(std::unordered_map<std::string, JS::Any> properties) : JS::InternalObject({}, JS::prototype, "Object", true) {
    std::cerr << "Object constructor" << std::endl;
    for (const auto& [key, value] : properties) {
        std::cerr << "key: " << key << " value: " << value << std::endl;
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