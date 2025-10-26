#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsNumber.hpp"

std::shared_ptr<JS::InternalObject>& JS::Number::getPrototypeProperties(const std::shared_ptr<JS::InternalObject>& constructor) {
    static std::unordered_map<std::u16string, JS::Attribute> properties_prototype = {
        {u"toString", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Number::toString, 1, u"toString")), true, false, true}},
        {u"toLocaleString", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Number::toLocaleString, 0, u"toLocaleString")), true, false, true}},
        {u"valueOf", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Number::valueOf, 0, u"valueOf")), true, false, true}},
        {u"toFixed", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Number::toFixed, 1, u"toFixed")), true, false, true}},
        {u"toExponential", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Number::toExponential, 1, u"toExponential")), true, false, true}},
        {u"toPrecision", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Number::toPrecision, 1, u"toPrecision")), true, false, true}},
        {u"constructor", JS::DataDescriptor{JS::Any(constructor ? constructor : JS::Number::getConstructor()), true, false, true}},
    };
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(properties_prototype, JS::Object::getPrototypeProperties(), OBJECT_CLASS_NAME, true);
    instance->primitiveValue = 0.0;
    return instance;
}
