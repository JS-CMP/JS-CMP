#include "types/objects/String/PrototypeProperties.hpp"

#include "types/objects/JsFunction.hpp"
#include "types/objects/String/PrototypeMethods.hpp"
#include "types/objects/Object/PrototypeProperties.hpp"

std::shared_ptr<JS::InternalObject> &JS::STR::PrototypeProperties::get() {
    static std::unordered_map<std::string, JS::Attribute> properties_prototype = {
            {"toString", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toString)), true, true, true}},
            {"valueOf", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::valueOf)), true, true, true}},
            {"charAt", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::charAt)), true, true, true}},
            {"charCodeAt", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::charCodeAt)), true, true, true}},
            {"concat", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::concat)), true, true, true}},
            {"indexOf", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::indexOf)), true, true, true}},
            {"lastIndexOf", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::lastIndexOf)), true, true, true}},
            {"localeCompare", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::localeCompare)), true, true, true}},
            {"match", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::match)), true, true, true}},
            {"replace", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::replace)), true, true, true}},
            {"search", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::search)), true, true, true}},
            {"slice", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::slice)), true, true, true}},
            {"split", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::split)), true, true, true}},
            {"substring", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::substring)), true, true, true}},
            {"toLowerCase", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toLowerCase)), true, true, true}},
            {"toLocaleLowerCase", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toLocaleLowerCase)), true, true, true}},
            {"toUpperCase", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toUpperCase)), true, true, true}},
            {"toLocaleUpperCase", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toLocaleUpperCase)), true, true, true}},
            {"trim", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::trim)), true, true, true}},
    };
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(properties_prototype, JS::OBJ::PrototypeProperties::get(), "String", true);

    return instance;
}