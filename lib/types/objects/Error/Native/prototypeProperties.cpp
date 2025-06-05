#include "types/objects/JsFunction.hpp"
#include "types/objects/Error/JsNativeError.hpp"

std::shared_ptr<JS::InternalObject>& JS::NativeError::getPrototypeProperties() {
    static std::unordered_map<std::string, JS::Attribute> properties_prototype = {
        {"toString", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::NativeError::toString)), true, true, true}},
        {"name", JS::DataDescriptor{JS::Any("NativeError"), true, true, true}},
        {"message", JS::DataDescriptor{JS::Any(""), true, true, true}},
    };
    
    static std::shared_ptr<JS::InternalObject> protoInstance = std::make_shared<JS::InternalObject>(
        properties_prototype, JS::Object::getPrototypeProperties(), "Error", true);

    return protoInstance;
}
