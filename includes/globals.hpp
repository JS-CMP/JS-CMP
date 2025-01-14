#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include "types/JsAny.hpp"
#include "types/objects/JsObject.hpp"
#include "types/objects/JsFunction.hpp"


std::unordered_map<std::string, JS::Any> properties = {
    	{"getPropertyOf", JS::Any(std::make_shared<JS::Function>(JS::Object::getPrototypeOf))},
        {"getOwnPropertyDescriptor", JS::Any(std::make_shared<JS::Function>(JS::Object::getOwnPropertyDescriptor))},
        {"getOwnPropertyNames", JS::Any(std::make_shared<JS::Function>(JS::Object::getOwnPropertyNames))},
        {"create", JS::Any(std::make_shared<JS::Function>(JS::Object::create))},
        {"defineProperty", JS::Any(std::make_shared<JS::Function>(JS::Object::defineProperty))},
        {"defineProperties", JS::Any(std::make_shared<JS::Function>(JS::Object::defineProperties))},
        {"seal", JS::Any(std::make_shared<JS::Function>(JS::Object::seal))},
        {"freeze", JS::Any(std::make_shared<JS::Function>(JS::Object::freeze))},
        {"preventExtensions", JS::Any(std::make_shared<JS::Function>(JS::Object::preventExtensions))},
        {"isSealed", JS::Any(std::make_shared<JS::Function>(JS::Object::isSealed))},
        {"isFrozen", JS::Any(std::make_shared<JS::Function>(JS::Object::isFrozen))},
        {"isExtensible", JS::Any(std::make_shared<JS::Function>(JS::Object::isExtensible))},
        {"keys", JS::Any(std::make_shared<JS::Function>(JS::Object::keys))},
};
JS::Any Object = JS::Any(std::make_shared<JS::Object>(properties));

Object();
#endif //GLOBALS_HPP
