#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsBoolean.hpp"

#include <types/objects/Error/JsTypeError.hpp>
#include <utils/Compare.hpp>

JS::Any JS::Boolean::toString(const JS::Any& thisArg, const JS::Any& args) {
    bool b;
    if (JS::COMPARE::Type(thisArg, JS::BOOLEAN)) {
        b = std::get<bool>(thisArg.getValue());
    } else if (JS::COMPARE::Object(thisArg, BOOL_CLASS_NAME)) {
        b = std::get<bool>(std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())->primitiveValue);
    } else {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Boolean.prototype.toString is not generic"))); // TODO: make it generic
    }
    return JS::Any(b ? "true" : "false");
}

JS::Any JS::Boolean::valueOf(const JS::Any& thisArg, const JS::Any& args) {
    bool b;
    if (JS::COMPARE::Type(thisArg, JS::BOOLEAN)) {
        b = std::get<bool>(thisArg.getValue());
    } else if (JS::COMPARE::Object(thisArg, BOOL_CLASS_NAME)) {
        b = std::get<bool>(std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())->primitiveValue);
    } else {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Boolean.prototype.valueOf is not generic"))); // TODO: make it generic
    }
    return JS::Any(b);
}
