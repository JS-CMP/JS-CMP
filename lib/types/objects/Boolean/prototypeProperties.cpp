#include "types/objects/Function/JsFunction.hpp"

#include <types/objects/JsBoolean.hpp>

std::shared_ptr<JS::InternalObject>& JS::Boolean::getPrototypeProperties() {
    static std::unordered_map<std::u16string, Attribute> properties_prototype = {
        {u"toString", DataDescriptor{Any(std::make_shared<JS::Function>(JS::Boolean::toString)), true, true, true}},
        {u"valueOf", DataDescriptor{Any(std::make_shared<JS::Function>(JS::Boolean::valueOf)), true, true, true}},
    };
    static std::shared_ptr<InternalObject> instance =
        std::make_shared<InternalObject>(properties_prototype, JS::Object::getPrototypeProperties(), u"Boolean", true);

    return instance;
}
