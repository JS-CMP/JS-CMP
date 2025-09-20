#include "types/objects/Function/JsFunction.hpp"

std::shared_ptr<JS::InternalObject>& JS::Object::getPrototypeProperties(std::shared_ptr<InternalObject> prototype) {
    if (prototype == nullptr) {
        prototype = JS::Function::getPrototypeProperties();
    }
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(
        JS::Properties{
            {u"constructor",
             JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::internal_constructor, prototype)),
                                true, false, true}},
            {u"toString", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::toString, prototype)),
                                             true, false, true}},
            {u"toLocaleString",
             JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::toLocaleString, prototype)), true,
                                false, true}},
            {u"valueOf", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::valueOf, prototype)),
                                            true, false, true}},
            {u"hasOwnProperty",
             JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::hasOwnProperty, prototype)), true,
                                false, true}},
            {u"isPrototypeOf",
             JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::isPrototypeOf, prototype)), true,
                                false, true}},
            {u"propertyIsEnumerable",
             JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::propertyIsEnumerable, prototype)),
                                true, false, true}},
        },
        nullptr, OBJECT_CLASS_NAME, true);
    return instance;
}