#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/Error/JsReferenceError.hpp"

std::shared_ptr<JS::InternalObject>& JS::ReferenceError::getPrototypeProperties() {
    static std::unordered_map<std::u16string, JS::Attribute> properties_prototype = {
        {u"toString", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::ReferenceError::toString)), true, true, true}},
        {u"name", JS::DataDescriptor{JS::Any("ReferenceError"), true, true, true}},
        {u"message", JS::DataDescriptor{JS::Any(""), true, true, true}},
    };
    
    static std::shared_ptr<JS::InternalObject> protoInstance = std::make_shared<JS::InternalObject>(
        properties_prototype, JS::Object::getPrototypeProperties(), u"Error", true);

    return protoInstance;
}
