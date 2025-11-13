#include "types/objects/Error/JsError.hpp"
#include "types/objects/Function/JsFunction.hpp"

std::shared_ptr<JS::InternalObject>& JS::Error::getPrototypeProperties(const std::shared_ptr<JS::InternalObject>& constructor) {
    static std::unordered_map<std::u16string, JS::Attribute> properties_prototype = {
        {u"toString", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Error::toString)), true, false, true}},
        {u"name", JS::DataDescriptor{JS::Any("Error"), true, false, true}},
        {u"message", JS::DataDescriptor{JS::Any(""), true, false, true}},
        {u"constructor", JS::DataDescriptor{JS::Any(constructor ? constructor : JS::Error::getConstructor()), true, false, true}},
    };

    static std::shared_ptr<JS::InternalObject> protoInstance = std::make_shared<JS::InternalObject>(properties_prototype, JS::Object::getPrototypeProperties(), OBJECT_CLASS_NAME, true);

    return protoInstance;
}
