#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsNumber.hpp"

std::shared_ptr<JS::InternalObject>& JS::Number::getPrototypeProperties() {
     static std::unordered_map<std::u16string, JS::Attribute> properties_prototype = {
         {u"toString",
          JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toString)), true, true, true}},
        {u"toLocaleString",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toLocaleString)), true, true, true}},
        {u"valueOf",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::valueOf)), true, true, true}},
        {u"toFixed",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toFixed)), true, true, true}},
        {u"toExponential",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toExponential)), true, true, true}},
        {u"toPrecision",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toPrecision)), true, true, true}},
    };
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(
        properties_prototype, JS::Object::getPrototypeProperties(), u"Number", true);

    return instance;
}
