#include "internals/Object.hpp"
#include "types/objects/JsObject.hpp"
#include "utils/Convert.hpp"
#include "utils/Is.hpp"

#include <utils/Compare.hpp>
#include <types/objects/Function/JsFunction.hpp>

std::u16string JS::Object::getContent() const {
    return JS::CONVERT::ObjectToString(shared_from_this());
}

std::shared_ptr<JS::Function> JS::Object::getConstructor() {
    static auto constructor = std::make_shared<JS::Function>([] (const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
        JS::Any value = args[u"0"];
        if (JS::COMPARE::Type(value, JS::OBJECT)) {
            return value;
        }
        if (JS::COMPARE::Type(value, JS::BOOLEAN) || JS::COMPARE::Type(value, JS::NUMBER) ||
            JS::COMPARE::Type(value, JS::STRING)) {
            return JS::Any(JS::CONVERT::ToObject(value));
        }
        if (JS::COMPARE::Type(value, JS::UNDEFINED) || JS::COMPARE::Type(value, JS::NULL_TYPE)) {
            return JS::Any(std::make_shared<JS::Object>());
        }
        return JS::Any(JS::CONVERT::ToObject(value));
    }, 1, OBJECT_CLASS_NAME);

    constructor->class_name = OBJECT_CLASS_NAME;
    constructor->extensible = true;
    constructor->prototype = Function::getPrototypeProperties();
    constructor->properties = std::make_shared<JS::Properties>(JS::Properties({
        {u"length", JS::DataDescriptor{JS::Any(1), false, false, false}},
        {u"name", JS::DataDescriptor{JS::Any(OBJECT_CLASS_NAME), false, false, false}},
        {u"keys", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::keys)), true, false, true}},
        {u"create", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::create)), true, false, true}},
        {u"defineProperty",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::defineProperty)), true, false, true}},
        {u"defineProperties",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::defineProperties)), true, false, true}},
        {u"freeze", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::freeze)), true, false, true}},
        {u"getPrototypeOf",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::getPrototypeOf)), true, false, true}},
        {u"getOwnPropertyDescriptor",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::getOwnPropertyDescriptor)), true, false,
                            true}},
        {u"getOwnPropertyNames",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::getOwnPropertyNames)), true, false, true}},
        {u"isSealed", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::isSealed)), true, false, true}},
        {u"isFrozen", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::isFrozen)), true, false, true}},
        {u"isExtensible",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::isExtensible)), true, false, true}},
        {u"preventExtensions",
         JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::preventExtensions)), true, false, true}},
        {u"seal", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::seal)), true, false, true}},
        {u"prototype", JS::DataDescriptor(JS::Any(Object::getPrototypeProperties()), false , false, false)}
    }));
    return constructor;
}

// Static Object constructor
// Object::Object(const JS::Properties& properties)
//     : JS::InternalObject(properties, JS::Function::getPrototypeProperties(), OBJECT_CLASS_NAME, true) {
//     this->InternalObject::defineOwnProperty(u"prototype", DataDescriptor({
//                                                               JS::Any(getPrototypeProperties()),
//                                                               false,
//                                                               false,
//                                                               false,
//                                                           }));
//     this->call_function = &JS::Object::internal_call;
//     this->construct = &JS::Object::internal_constructor;
// }
