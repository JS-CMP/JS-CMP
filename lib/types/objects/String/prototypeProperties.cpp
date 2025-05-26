#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsString.hpp"

std::shared_ptr<JS::InternalObject>& JS::String::getPrototypeProperties() {
    static std::unordered_map<std::u16string, JS::Attribute> properties_prototype = {
        {u"toString",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toString)), true, true, true}},
        {u"valueOf", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::valueOf)), true, true, true}},
        {u"charAt", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::charAt)), true, true, true}},
        {u"charCodeAt",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::charCodeAt)), true, true, true}},
        {u"concat", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::concat)), true, true, true}},
        {u"indexOf", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::indexOf)), true, true, true}},
        {u"lastIndexOf",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::lastIndexOf)), true, true, true}},
        {u"localeCompare",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::localeCompare)), true, true, true}},
        {u"match", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::match)), true, true, true}},
        {u"replace", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::replace)), true, true, true}},
        {u"search", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::search)), true, true, true}},
        {u"slice", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::slice)), true, true, true}},
        {u"split", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::split)), true, true, true}},
        {u"substring",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::substring)), true, true, true}},
        {u"toLowerCase",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toLowerCase)), true, true, true}},
        {u"toLocaleLowerCase",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toLocaleLowerCase)), true, true, true}},
        {u"toUpperCase",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toUpperCase)), true, true, true}},
        {u"toLocaleUpperCase",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toLocaleUpperCase)), true, true, true}},
        {u"trim", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::trim)), true, true, true}},
    };
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(
        properties_prototype, JS::Object::getPrototypeProperties(), u"String", true);

    return instance;
}