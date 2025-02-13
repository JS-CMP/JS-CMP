#include "types/objects/JsFunction.hpp"

#include <types/objects/JsBoolean.hpp>

std::shared_ptr<JS::InternalObject>& JS::Boolean::getPrototypeProperties() {
    static std::unordered_map<std::string, Attribute> properties_prototype = {
        {"toString", DataDescriptor{Any(std::make_shared<JS::Function>(JS::Boolean::toString)), true, true, true}},
        {"valueOf", DataDescriptor{Any(std::make_shared<JS::Function>(JS::Boolean::valueOf)), true, true, true}},
    };
    static std::shared_ptr<InternalObject> instance =
        std::make_shared<InternalObject>(properties_prototype, JS::Object::getPrototypeProperties(), "Boolean", true);

    return instance;
}
