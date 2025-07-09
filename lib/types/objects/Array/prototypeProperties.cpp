#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsArray.hpp"

std::shared_ptr<JS::InternalObject>& JS::Array::getPrototypeProperties() {
    static std::unordered_map<std::u16string, JS::Attribute> properties_prototype = {
        {u"toString",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::toString)), true, true, true}},
        {u"toLocaleString",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::toLocaleString)), true, true, true}},
        {u"concat", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::concat)), true, true, true}},
        {u"join", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::join)), true, true, true}},
        {u"pop", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::pop)), true, true, true}},
        {u"push", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::push)), true, true, true}},
        {u"reverse", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::reverse)), true, true, true}},
        {u"shift", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::shift)), true, true, true}},
        {u"slice", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::slice)), true, true, true}},
        {u"sort", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::sort)), true, true, true}},
        {u"splice", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::splice)), true, true, true}},
        {u"unshift", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::unshift)), true, true, true}},
        {u"indexOf", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::indexOf)), true, true, true}},
        {u"lastIndexOf",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::lastIndexOf)), true, true, true}},
        {u"every", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::every)), true, true, true}},
        {u"some", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::some)), true, true, true}},
        {u"forEach", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::forEach)), true, true, true}},
        {u"map", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::map)), true, true, true}},
        {u"filter", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::filter)), true, true, true}},
        {u"reduce", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::reduce)), true, true, true}},
        {u"reduceRight",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::reduceRight)), true, true, true}},
        {u"constructor", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::internal_constructor)), true, false, true}},

    };
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(
        properties_prototype, JS::Object::getPrototypeProperties(), u"Object", true);

    return instance;
}