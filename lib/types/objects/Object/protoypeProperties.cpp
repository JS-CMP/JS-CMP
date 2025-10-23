#include "types/objects/Function/JsFunction.hpp"

std::shared_ptr<JS::InternalObject>& JS::Object::getPrototypeProperties(const std::shared_ptr<JS::InternalObject>& prototype, const std::shared_ptr<Function>& constructor) {
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(JS::Properties{}, nullptr, OBJECT_CLASS_NAME, true);

    instance->defineOwnProperty(u"constructor", JS::DataDescriptor{JS::Any(constructor ? constructor : getConstructor()), true, false, true}, true);
    instance->defineOwnProperty(u"toString", JS::DataDescriptor{ JS::Any(JS::InternalObject::create<JS::Function>(instance, JS::Object::toString, 0, u"toString", prototype)), true, false, true}, true);
    instance->defineOwnProperty(u"toLocaleString", JS::DataDescriptor{ JS::Any(JS::InternalObject::create<JS::Function>(instance, JS::Object::toLocaleString, 0, u"toLocaleString", prototype)), true, false, true});
    instance->defineOwnProperty(u"valueOf",JS::DataDescriptor{ JS::Any(JS::InternalObject::create<JS::Function>(instance, JS::Object::valueOf, 0, u"valueOf", prototype)), true, false, true});
    instance->defineOwnProperty(u"hasOwnProperty", JS::DataDescriptor{ JS::Any(JS::InternalObject::create<JS::Function>(instance, JS::Object::hasOwnProperty, 1, u"hasOwnProperty", prototype)), true, false, true});
    instance->defineOwnProperty(u"isPrototypeOf",  JS::DataDescriptor{ JS::Any(JS::InternalObject::create<JS::Function>(instance, JS::Object::isPrototypeOf, 1, u"isPrototypeOf", prototype)), true, false, true});
    instance->defineOwnProperty(u"propertyIsEnumerable", JS::DataDescriptor{ JS::Any(JS::InternalObject::create<JS::Function>(instance, JS::Object::propertyIsEnumerable, 1,u"propertyIsEnumerable", prototype)), true, false, true});

    return instance;
}