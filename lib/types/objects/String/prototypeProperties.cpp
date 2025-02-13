#include "types/objects/JsString.hpp"
#include "types/objects/JsFunction.hpp"

std::shared_ptr<JS::InternalObject> &JS::String::getPrototypeProperties() {
    static std::unordered_map<std::string, JS::Attribute> properties_prototype = {
            {"toString", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toString)), true, true, true}},
            {"valueOf", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::valueOf)), true, true, true}},
            {"charAt", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::charAt)), true, true, true}},
            {"charCodeAt", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::charCodeAt)), true, true, true}},
            {"concat", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::concat)), true, true, true}},
            {"indexOf", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::indexOf)), true, true, true}},
            {"lastIndexOf", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::lastIndexOf)), true, true, true}},
            {"localeCompare", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::localeCompare)), true, true, true}},
            {"match", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::match)), true, true, true}},
            {"replace", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::replace)), true, true, true}},
            {"search", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::search)), true, true, true}},
            {"slice", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::slice)), true, true, true}},
            {"split", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::split)), true, true, true}},
            {"substring", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::substring)), true, true, true}},
            {"toLowerCase", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toLowerCase)), true, true, true}},
            {"toLocaleLowerCase", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toLocaleLowerCase)), true, true, true}},
            {"toUpperCase", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toUpperCase)), true, true, true}},
            {"toLocaleUpperCase", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toLocaleUpperCase)), true, true, true}},
            {"trim", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::trim)), true, true, true}},
    };
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(properties_prototype, JS::Object::getPrototypeProperties(), "String", true);

    return instance;
}