#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsString.hpp"

std::shared_ptr<JS::InternalObject>& JS::String::getPrototypeProperties() {
    static std::unordered_map<std::u16string, JS::Attribute> properties_prototype = {
        {u"toString",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toString, 0, u"toString")), true, false, true}},
        {u"valueOf",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::valueOf, 0, u"valueOf")), true, false, true}},
        {u"charAt", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::charAt, 1, u"charAt")), true, false, true}},
        {u"charCodeAt",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::charCodeAt, 1, u"charCodeAt")), true, false, true}},
        {u"concat", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::concat, 1, u"concat")), true, false, true}},
        {u"indexOf",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::indexOf, 1, u"indexOf")), true, false, true}},
        {u"lastIndexOf",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::lastIndexOf, 1, u"lastIndexOf")), true, false, true}},
        {u"localeCompare",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::localeCompare, 1, u"localeCompare")), true, false, true}},
        {u"match", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::match, 1, u"match")), true, false, true}},
        {u"replace",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::replace, 2, u"replace")), true, false, true}},
        {u"search", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::search, 1, u"search")), true, false, true}},
        {u"slice", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::slice, 2, u"slice")), true, false, true}},
        {u"split", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::split, 2, u"split")), true, false, true}},
        {u"substring",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::substring, 2, u"substring")), true, false, true}},
        {u"toLowerCase",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toLowerCase, 0, u"toLowerCase")), true, false, true}},
        {u"toLocaleLowerCase",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toLocaleLowerCase, 0, u"toLocaleLowerCase")), true, false, true}},
        {u"toUpperCase",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toUpperCase, 0, u"toUpperCase")), true, false, true}},
        {u"toLocaleUpperCase",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::toLocaleUpperCase, 0, u"toLocaleUpperCase")), true, false, true}},
        {u"trim", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::trim, 0, u"trim")), true, false, true}},
        {u"constructor", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::internal_constructor, 1, u"String")),
                                            true, false, true}},
    };
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(
        properties_prototype, JS::Object::getPrototypeProperties(), u"String", true);
    instance->primitiveValue = Rope("");
    return instance;
}