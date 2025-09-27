#include "types/objects/Function/JsFunction.hpp"

std::shared_ptr<JS::InternalObject>& JS::Object::getPrototypeProperties(const std::shared_ptr<JS::InternalObject>& prototype) {
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(
        JS::Properties{
            {u"constructor",
             JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::internal_constructor, prototype)),
                                true, false, true}},
            {u"toString", JS::DataDescriptor{
                 JS::Any(std::make_shared<JS::Function>(JS::Object::toString, prototype, 0, u"toString")),
                 true, false, true}},
            {u"toLocaleString",
             JS::DataDescriptor{
                 JS::Any(std::make_shared<JS::Function>(JS::Object::toLocaleString, prototype, 0, u"toLocaleString")),
                 true, false, true}},
            {u"valueOf", JS::DataDescriptor{
                 JS::Any(std::make_shared<JS::Function>(JS::Object::valueOf, prototype, 0, u"valueOf")),
                 true, false, true}},
            {u"hasOwnProperty",
             JS::DataDescriptor{
                 JS::Any(std::make_shared<JS::Function>(JS::Object::hasOwnProperty, prototype, 1, u"hasOwnProperty")),
                 true, false, true}},
            {u"isPrototypeOf",
             JS::DataDescriptor{
                 JS::Any(std::make_shared<JS::Function>(JS::Object::isPrototypeOf, prototype, 1, u"isPrototypeOf")),
                 true, false, true}},
            {u"propertyIsEnumerable",
             JS::DataDescriptor{
                 JS::Any(std::make_shared<JS::Function>(JS::Object::propertyIsEnumerable, prototype, 1,
                                                        u"propertyIsEnumerable")),
                 true, false, true}},
        },
        nullptr, OBJECT_CLASS_NAME, true);

        return instance;
}