#include "types/objects/Function/JsFunction.hpp"

std::shared_ptr<JS::InternalObject>& JS::Function::getPrototypeProperties() {
    std::cout << "Creating Function prototype properties" << std::endl;
    static bool initialized = false;
    static std::shared_ptr<JS::InternalObject> instance =
        std::make_shared<JS::InternalObject>(JS::Properties{}, nullptr, FUNCTION_CLASS_NAME, true);
    if (initialized) {
        return instance;
    }
    instance->prototype = JS::Object::getPrototypeProperties(instance);
    instance->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(0), false, false, false});
    instance->defineOwnProperty(u"name", JS::DataDescriptor{JS::Any(u"Empty"), false, false, false});
    instance->defineOwnProperty(
        u"constructor",
        JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Function::internal_constructor, instance)), false,
                           false, false});
    instance->defineOwnProperty(
        u"toString", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Function::toString, instance, 0, u"toString")), true, false, true});
    instance->defineOwnProperty(
        u"apply",
        JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Function::apply, instance, 2, u"apply")), true, false, true});
    instance->defineOwnProperty(
        u"call",
        JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Function::call, instance, 1, u"call")), true, false, true});
    instance->defineOwnProperty(
        u"bind",
        JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Function::bind, instance, 1, u"bind")), true, false, true});
    initialized = true;
    return instance;
}

std::shared_ptr<JS::InternalObject> JS::Function::getPrototypePropertiesCopy(const std::shared_ptr<JS::InternalObject>& constructor,std::shared_ptr<JS::InternalObject> prototype) {
    return std::make_shared<JS::InternalObject>(JS::Properties{
        {u"constructor",
         JS::DataDescriptor{JS::Any(constructor), false, false,false}},
    }, JS::Object::getPrototypeProperties(prototype) , FUNCTION_CLASS_NAME, true);
}