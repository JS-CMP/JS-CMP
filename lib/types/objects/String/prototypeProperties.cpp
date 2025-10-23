#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsString.hpp"

std::shared_ptr<JS::InternalObject>& JS::String::getPrototypeProperties() {
    static std::unordered_map<std::u16string, JS::Attribute> properties_prototype = {
        {u"toString", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::toString)), true, false, true}},
        {u"valueOf", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::valueOf)), true, false, true}},
        {u"charAt", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::charAt)), true, false, true}},
        {u"charCodeAt", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::charCodeAt)), true, false, true}},
        {u"concat", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::concat)), true, false, true}},
        {u"indexOf", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::indexOf)), true, false, true}},
        {u"lastIndexOf", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::lastIndexOf)), true, false, true}},
        {u"localeCompare", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::localeCompare)), true, false, true}},
        {u"match", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::match)), true, false, true}},
        {u"replace", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::replace)), true, false, true}},
        {u"search", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::search)), true, false, true}},
        {u"slice", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::slice)), true, false, true}},
        {u"split", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::split)), true, false, true}},
        {u"substring", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::substring)), true, false, true}},
        {u"toLowerCase", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::toLowerCase)), true, false, true}},
        {u"toLocaleLowerCase", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::toLocaleLowerCase)), true, false, true}},
        {u"toUpperCase", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::toUpperCase)), true, false, true}},
        {u"toLocaleUpperCase", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::toLocaleUpperCase)), true, false, true}},
        {u"trim", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::trim)), true, false, true}},
        {u"constructor", JS::DataDescriptor{JS::Any(getConstructor()), true, false, true}},
    };
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(
        properties_prototype, JS::Object::getPrototypeProperties(), STRING_CLASS_NAME, true);
    instance->primitiveValue = Rope("");
    return instance;
}