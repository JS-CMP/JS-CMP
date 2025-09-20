#include "types/objects/Function/JsFunction.hpp"

std::shared_ptr<JS::InternalObject>& JS::Function::getPrototypeProperties() {
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
        u"toString", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Function::toString, instance)), true,
                                        false, true});
    instance->defineOwnProperty(
        u"apply",
        JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Function::apply, instance)), true, false, true});
    instance->defineOwnProperty(
        u"call",
        JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Function::call, instance)), true, false, true});
    instance->defineOwnProperty(
        u"bind",
        JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Function::bind, instance)), true, false, true});
    initialized = true;
    return instance;
}