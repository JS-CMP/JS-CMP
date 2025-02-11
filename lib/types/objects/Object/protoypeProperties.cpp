#include "types/objects/Object/PrototypeProperties.hpp"
#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/Object/PrototypeMethods.hpp"

std::shared_ptr<JS::InternalObject> &JS::OBJ::PrototypeProperties::get() {
    static std::unordered_map<std::string, JS::Any> properties_prototype = {
            {"toString", JS::Any(std::make_shared<JS::Function>(JS::OBJ::PrototypeMethods::toString))},
            {"toLocaleString", JS::Any(std::make_shared<JS::Function>(JS::OBJ::PrototypeMethods::toLocaleString))},
            {"valueOf", JS::Any(std::make_shared<JS::Function>(JS::OBJ::PrototypeMethods::valueOf))},
            {"hasOwnProperty", JS::Any(std::make_shared<JS::Function>(JS::OBJ::PrototypeMethods::hasOwnProperty))},
            {"isPrototypeOf", JS::Any(std::make_shared<JS::Function>(JS::OBJ::PrototypeMethods::isPrototypeOf))},
            {"propertyIsEnumerable", JS::Any(std::make_shared<JS::Function>(JS::OBJ::PrototypeMethods::propertyIsEnumerable))},
    };
    static std::shared_ptr<JS::InternalObject> instance =
            std::make_shared<JS::InternalObject>(properties_prototype);
    return instance;
}