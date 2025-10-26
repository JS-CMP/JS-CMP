#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsRegExp.hpp"

std::shared_ptr<JS::InternalObject>& JS::RegExp::getPrototypeProperties() {
    static std::unordered_map<std::u16string, JS::Attribute> properties_prototype = {
        {u"exec", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::RegExp::exec)), true, true, true}},
        {u"test", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::RegExp::test)), true, true, true}},
        {u"toString", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::RegExp::toString)), true, true, true}},
    };
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(properties_prototype, JS::Object::getPrototypeProperties(), REGEXP_CLASS_NAME, true);

    return instance;
}