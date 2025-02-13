#include "types/objects/Object/PrototypeProperties.hpp"
#include "types/objects/Function/JsFunction.hpp"

std::shared_ptr<JS::InternalObject> &JS::OBJ::PrototypeProperties::get() {
    static std::unordered_map<std::string, JS::Any> properties_prototype = {
            {"toString", JS::Any(std::make_shared<JS::Function>(JS::Object::toString))},
            {"toLocaleString", JS::Any(std::make_shared<JS::Function>(JS::Object::toLocaleString))},
            {"valueOf", JS::Any(std::make_shared<JS::Function>(JS::Object::valueOf))},
            {"hasOwnProperty", JS::Any(std::make_shared<JS::Function>(JS::Object::hasOwnProperty))},
            {"isPrototypeOf", JS::Any(std::make_shared<JS::Function>(JS::Object::isPrototypeOf))},
            {"propertyIsEnumerable", JS::Any(std::make_shared<JS::Function>(JS::Object::propertyIsEnumerable))},
    };
    static std::shared_ptr<JS::InternalObject> instance =
            std::make_shared<JS::InternalObject>(properties_prototype);
    return instance;
}