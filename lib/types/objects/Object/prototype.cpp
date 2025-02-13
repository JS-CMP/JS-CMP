#include "internals/Object.hpp"
#include "types/objects/JsFunction.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"
#include "utils/Is.hpp"

namespace JS {
// TODO Implement correctly ToObject to make all the methods work (ToObject should always return an object so the
// compare type should always be true)
JS::Any Object::toString(const JS::Any& thisArg, const JS::Any& args) {
    switch (thisArg.getValue().index()) {
        case JS::UNDEFINED:
            return JS::Any("[object Undefined]");
        case JS::NULL_TYPE:
            return JS::Any("[object Null]");
    }
    JS::Any O = JS::CONVERT::ToObject(thisArg);
    // TODO to remove when ToObject is implemented correctly
    if (!JS::COMPARE::Type(O, JS::OBJECT)) {
        throw std::runtime_error(
            "TypeError: Object.prototype.toString called on non-object (this should never happen)");
        // this should never happen
    }
    return JS::Any("[object " + std::get<std::shared_ptr<JS::InternalObject>>(O.getValue())->class_name + "]");
}

JS::Any Object::toLocaleString(const JS::Any& thisArg, const JS::Any& args) {
    JS::Any O = JS::CONVERT::ToObject(thisArg);
    // TODO to remove when ToObject is implemented correctly
    if (!JS::COMPARE::Type(O, JS::OBJECT)) {
        throw std::runtime_error(
            "TypeError: Object.prototype.toLocaleString called on non-object (this should never happen)");
        // this should never happen
    }
    JS::Any toString = std::get<std::shared_ptr<JS::InternalObject>>(O.getValue())->get("toString");
    if (JS::IS::Callable(toString)) {
        return toString();
    }
    throw std::runtime_error("TypeError: Object.prototype.toLocaleString called on non-object");
}

JS::Any Object::valueOf(const JS::Any& thisArg, const JS::Any& args) {
    JS::Any O = JS::CONVERT::ToObject(thisArg);
    // TODO to remove when ToObject is implemented correctly
    if (!JS::COMPARE::Type(O, JS::OBJECT)) {
        throw std::runtime_error("TypeError: Object.prototype.valueOf called on non-object (this should never happen)");
        // this should never happen
    }
    return O;
}

JS::Any Object::hasOwnProperty(const JS::Any& thisArg, const JS::Any& args) {
    std::string P = JS::CONVERT::ToString(args["0"]);
    JS::Any O = JS::CONVERT::ToObject(thisArg);
    // TODO to remove when ToObject is implemented correctly
    if (!JS::COMPARE::Type(O, JS::OBJECT)) {
        throw std::runtime_error(
            "TypeError: Object.prototype.hasOwnProperty called on non-object (this should never happen)");
        // this should never happen
    }
    std::shared_ptr<JS::InternalObject> obj = std::get<std::shared_ptr<JS::InternalObject>>(O.getValue());
    if (obj->getOwnProperty(P).has_value()) {
        return JS::Any(true);
    }
    return JS::Any(false);
}

JS::Any Object::isPrototypeOf(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args["0"], JS::OBJECT)) {
        return JS::Any(false);
    }
    JS::Any O = JS::CONVERT::ToObject(thisArg);
    // TODO to remove when ToObject is implemented correctly
    if (!JS::COMPARE::Type(O, JS::OBJECT)) {
        throw std::runtime_error(
            "TypeError: Object.prototype.isPrototypeOf called on non-object (this should never happen)");
        // this should never happen
    }
    std::shared_ptr<JS::InternalObject> obj = std::get<std::shared_ptr<JS::InternalObject>>(O.getValue());
    std::shared_ptr<JS::InternalObject> V = std::get<std::shared_ptr<JS::InternalObject>>(args["0"].getValue());
    while (V->prototype != nullptr) {
        V = V->prototype;
        if (V.get() == obj.get()) {
            return JS::Any(true);
        }
    }
    return JS::Any(false);
}

JS::Any Object::propertyIsEnumerable(const JS::Any& thisArg, const JS::Any& args) {
    std::string P = JS::CONVERT::ToString(args["0"]);
    JS::Any O = JS::CONVERT::ToObject(thisArg);
    // TODO to remove when ToObject is implemented correctly
    if (!JS::COMPARE::Type(O, JS::OBJECT)) {
        throw std::runtime_error("TypeError: Object.prototype.propertyIsEnumerable called on non-object (this should "
                                 "never happen)"); // this should never happen
    }
    std::shared_ptr<JS::InternalObject> obj = std::get<std::shared_ptr<JS::InternalObject>>(O.getValue());
    std::optional<JS::Attribute> desc = obj->getOwnProperty(P);
    if (!desc.has_value()) {
        return JS::Any(false);
    }
    return JS::Any(JS::IS::DataDescriptor(desc.value()) && std::get<JS::DataDescriptor>(desc.value()).enumerable ||
                   JS::IS::AccessorDescriptor(desc.value()) &&
                       std::get<JS::AccessorDescriptor>(desc.value())
                           .enumerable); // TODO can be optimized with a genericDescriptor with enumerable
}
} // namespace JS
