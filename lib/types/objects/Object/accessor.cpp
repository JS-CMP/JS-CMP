#include "types/objects/JsObject.hpp"
#include "utils/Convert.hpp"

#include <utils/Compare.hpp>

JS::Any JS::Object::internal_call(const JS::Any& thisArg, const JS::Any& args) {
    if (CONVERT::ToUint32(args["length"]) == 0 || JS::COMPARE::Type(thisArg, JS::UNDEFINED) ||
        JS::COMPARE::Type(thisArg, JS::NULL_TYPE)) {
        return JS::Any(std::make_shared<JS::Object>());
    }
    return JS::Any(JS::CONVERT::ToObject(args[u"0"]));
}

JS::Any JS::Object::internal_constructor(const JS::Any& thisArgs, const JS::Any& args) {
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
}