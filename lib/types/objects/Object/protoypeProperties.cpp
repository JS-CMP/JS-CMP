#include "types/objects/Function/JsFunction.hpp"

std::shared_ptr<JS::InternalObject>& JS::Object::getPrototypeProperties() {
    static std::unordered_map<std::u16string, JS::Any> properties_prototype = {
        {u"toString", JS::Any(std::make_shared<JS::Function>(JS::Object::toString))},
        {u"toLocaleString", JS::Any(std::make_shared<JS::Function>(JS::Object::toLocaleString))},
        {u"valueOf", JS::Any(std::make_shared<JS::Function>(JS::Object::valueOf))},
        {u"hasOwnProperty", JS::Any(std::make_shared<JS::Function>(JS::Object::hasOwnProperty))},
        {u"isPrototypeOf", JS::Any(std::make_shared<JS::Function>(JS::Object::isPrototypeOf))},
        {u"propertyIsEnumerable", JS::Any(std::make_shared<JS::Function>(JS::Object::propertyIsEnumerable))},
    };
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(properties_prototype);
    return instance;
}