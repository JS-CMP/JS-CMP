#include "types/objects/Function/JsFunction.hpp"

#include <types/objects/JsBoolean.hpp>

std::shared_ptr<JS::InternalObject>& JS::Boolean::getPrototypeProperties(const std::shared_ptr<JS::InternalObject>& constructor) {
    static std::unordered_map<std::u16string, Attribute> properties_prototype = {
        {u"toString", DataDescriptor{Any(JS::InternalObject::create<JS::Function>(JS::Boolean::toString, 0, u"toString")), true, false, true}},
        {u"valueOf", DataDescriptor{Any(JS::InternalObject::create<JS::Function>(JS::Boolean::valueOf, 0, u"valueOf")), true, false, true}},
        {u"constructor", DataDescriptor{Any(constructor ? constructor : JS::Boolean::getConstructor()), true, false, true}},
    };
    static std::shared_ptr<InternalObject> instance = std::make_shared<InternalObject>(properties_prototype, JS::Object::getPrototypeProperties(), BOOL_CLASS_NAME, true);
    instance->primitiveValue = false;
    return instance;
}
