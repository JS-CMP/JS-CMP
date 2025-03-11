#include "types/objects/JsFunction.hpp"
#include "types/objects/Error/JsSyntaxError.hpp"

std::shared_ptr<JS::InternalObject>& JS::SyntaxError::getPrototypeProperties() {
    static std::unordered_map<std::string, JS::Attribute> properties_prototype = {
        {"toString", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::SyntaxError::toString)), true, true, true}},
        {"name", JS::DataDescriptor{JS::Any("SyntaxError"), true, true, true}},
        {"message", JS::DataDescriptor{JS::Any(""), true, true, true}},
    };
    
    static std::shared_ptr<JS::InternalObject> protoInstance = std::make_shared<JS::InternalObject>(
        properties_prototype, JS::Object::getPrototypeProperties(), "Error", true);

    return protoInstance;
}
