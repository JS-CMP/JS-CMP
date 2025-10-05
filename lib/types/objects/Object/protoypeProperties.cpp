#include "types/objects/Function/JsFunction.hpp"

std::shared_ptr<JS::InternalObject>& JS::Object::getPrototypeProperties(const std::shared_ptr<JS::InternalObject>& prototype, const std::shared_ptr<Function>& constructor) {
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(
        JS::Properties{
            {u"constructor", JS::DataDescriptor{JS::Any(constructor ? constructor : getConstructor()), true, false, true}},
            {u"toString", JS::DataDescriptor{ JS::Any(std::make_shared<JS::Function>(JS::Object::toString, 0, u"toString", prototype)), true, false, true}},
            {u"toLocaleString", JS::DataDescriptor{ JS::Any(std::make_shared<JS::Function>(JS::Object::toLocaleString, 0, u"toLocaleString", prototype)), true, false, true}},
            {u"valueOf", JS::DataDescriptor{ JS::Any(std::make_shared<JS::Function>(JS::Object::valueOf, 0, u"valueOf", prototype)), true, false, true}},
            {u"hasOwnProperty", JS::DataDescriptor{ JS::Any(std::make_shared<JS::Function>(JS::Object::hasOwnProperty, 1, u"hasOwnProperty", prototype)), true, false, true}},
            {u"isPrototypeOf", JS::DataDescriptor{ JS::Any(std::make_shared<JS::Function>(JS::Object::isPrototypeOf, 1, u"isPrototypeOf", prototype)), true, false, true}},
            {u"propertyIsEnumerable", JS::DataDescriptor{ JS::Any(std::make_shared<JS::Function>(JS::Object::propertyIsEnumerable, 1,u"propertyIsEnumerable", prototype)), true, false, true}},
        },
        nullptr, OBJECT_CLASS_NAME, true);

        return instance;
}