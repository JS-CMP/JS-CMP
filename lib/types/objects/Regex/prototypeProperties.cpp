#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsRegex.hpp"

std::shared_ptr<JS::InternalObject>& JS::Regex::getPrototypeProperties() {
    static std::unordered_map<std::u16string, JS::Attribute> properties_prototype = {
        {u"exec", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Regex::exec)), true, true, true}},
        {u"test", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Regex::test)), true, true, true}},
        {u"toString",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Regex::toString)), true, true, true}},
    };
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(
        properties_prototype, JS::Object::getPrototypeProperties(), u"Regex", true);

    return instance;
}