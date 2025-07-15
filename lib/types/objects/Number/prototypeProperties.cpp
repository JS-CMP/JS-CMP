#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsNumber.hpp"

std::shared_ptr<JS::InternalObject>& JS::Number::getPrototypeProperties() {
    static std::unordered_map<std::u16string, JS::Attribute> properties_prototype = {
        {u"toString",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toString)), true, false, true}},
        {u"toLocaleString",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toLocaleString)), true, false, true}},
        {u"valueOf",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::valueOf)), true, false, true}},
        {u"toFixed",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toFixed)), true, false, true}},
        {u"toExponential",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toExponential)), true, false, true}},
        {u"toPrecision",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toPrecision)), true, false, true}},
        {u"constructor", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::internal_constructor)),
                                            true, false, true}},
    };
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(
        properties_prototype, JS::Object::getPrototypeProperties(), u"Object", true);
    instance->primitiveValue = 0.0;
    return instance;
}
