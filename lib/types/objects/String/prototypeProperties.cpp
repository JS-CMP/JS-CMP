#include "types/objects/String/PrototypeProperties.hpp"

#include "types/objects/JsFunction.hpp"
#include "types/objects/String/PrototypeMethods.hpp"
#include "types/objects/Object/PrototypeProperties.hpp"

std::shared_ptr<JS::InternalObject> &JS::STR::PrototypeProperties::get() {
    static std::unordered_map<std::string, JS::Any> properties_prototype = {
            {"toString", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toString))},
            {"valueOf", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::valueOf))},
            {"charAt", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::charAt))},
            {"charCodeAt", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::charCodeAt))},
            {"concat", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::concat))},
            {"indexOf", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::indexOf))},
            {"lastIndexOf", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::lastIndexOf))},
            {"localeCompare", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::localeCompare))},
            {"match", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::match))},
            {"replace", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::replace))},
            {"search", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::search))},
            {"slice", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::slice))},
            {"split", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::split))},
            {"substring", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::substring))},
            {"toLowerCase", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toLowerCase))},
            {"toLocaleLowerCase", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toLocaleLowerCase))},
            {"toUpperCase", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toUpperCase))},
            {"toLocaleUpperCase", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toLocaleUpperCase))},
            {"trim", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::trim))},
    };
//    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(
//            JS::InternalObject(properties_prototype, JS::OBJ::PrototypeProperties::get(), "Object", true));
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(properties_prototype));

    return instance;
}