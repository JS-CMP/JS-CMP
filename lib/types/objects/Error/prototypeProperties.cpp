#include "types/objects/Error/JsError.hpp"
#include "types/objects/Function/JsFunction.hpp"

std::shared_ptr<JS::InternalObject>& JS::Error::getPrototypeProperties() {
    static std::unordered_map<std::u16string, JS::Attribute> properties_prototype = {
        {u"toString",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Error::toString)), true, false, true}},
        {u"name", JS::DataDescriptor{JS::Any("Error"), true, false, true}},
        {u"message", JS::DataDescriptor{JS::Any(""), true, false, true}},
        {u"constructor", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Error::internal_constructor)),
                                            true, false, true}},
    };

    static std::shared_ptr<JS::InternalObject> protoInstance = std::make_shared<JS::InternalObject>(
        properties_prototype, JS::Object::getPrototypeProperties(), u"Object", true);

    return protoInstance;
}
