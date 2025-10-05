#include "types/objects/Function/JsFunction.hpp"

std::shared_ptr<JS::InternalObject>& JS::Function::getPrototypeProperties(const std::shared_ptr<JS::InternalObject>& constructor) {
    static bool initialized = false;
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(JS::Properties{}, nullptr, FUNCTION_CLASS_NAME, true);

    if (initialized) {
        return instance;
    }

    instance->prototype = constructor ? constructor : JS::Object::getPrototypeProperties(instance);
    instance->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(0), false, false, false});
    instance->defineOwnProperty(u"name", JS::DataDescriptor{JS::Any(u"Empty"), false, false, false});

    instance->defineOwnProperty(u"constructor", JS::DataDescriptor{JS::Any(getConstructor(instance)), false, false, false});
    instance->defineOwnProperty(u"toString", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Function::toString, 0, u"toString", instance)), true, false, true});
    instance->defineOwnProperty(u"apply", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Function::apply, 2, u"apply", instance)), true, false, true});
    instance->defineOwnProperty(u"call", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Function::call, 1, u"call", instance)), true, false, true});
    instance->defineOwnProperty(u"bind", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Function::bind, 1, u"bind", instance)), true, false, true});
    initialized = true;
    return instance;
}

std::shared_ptr<JS::InternalObject> JS::Function::getPrototypePropertiesCopy(std::shared_ptr<JS::InternalObject> constructor, std::shared_ptr<JS::InternalObject> prototype) {
    return std::make_shared<JS::InternalObject>(JS::Properties{
        {u"constructor", JS::DataDescriptor{JS::Any(constructor), false, false,false}},
    }, JS::Object::getPrototypeProperties(prototype) , FUNCTION_CLASS_NAME, true);
}