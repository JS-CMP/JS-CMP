#include "internals/Object.hpp"
#include "types/objects/JsFunction.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"
#include "utils/Is.hpp"

namespace JS {
JS::Any Object::toString(const JS::Any& thisArg, const JS::Any& args) {
    switch (thisArg.getValue().index()) {
        case JS::UNDEFINED:
            return JS::Any("[object Undefined]");
        case JS::NULL_TYPE:
            return JS::Any("[object Null]");
    }
    const std::shared_ptr<InternalObject> O = JS::CONVERT::ToObject(thisArg);
    return JS::Any("[object " + O->class_name + "]");
}

JS::Any Object::toLocaleString(const JS::Any& thisArg, const JS::Any& args) {
    const std::shared_ptr<InternalObject> O = JS::CONVERT::ToObject(thisArg);
    JS::Any toString = O->get("toString");
    if (JS::IS::Callable(toString)) {
        return toString();
    }
    throw std::runtime_error("TypeError: Object.prototype.toLocaleString called on non-object");
}

JS::Any Object::valueOf(const JS::Any& thisArg, const JS::Any& args) { return JS::Any(JS::CONVERT::ToObject(thisArg)); }

JS::Any Object::hasOwnProperty(const JS::Any& thisArg, const JS::Any& args) {
    const std::string P = JS::CONVERT::ToString(args["0"]);
    std::shared_ptr<InternalObject> O = JS::CONVERT::ToObject(thisArg);
    if (O->getOwnProperty(P).has_value()) {
        return JS::Any(true);
    }
    return JS::Any(false);
}

JS::Any Object::isPrototypeOf(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args["0"], JS::OBJECT)) {
        return JS::Any(false);
    }
    std::shared_ptr<InternalObject> O = JS::CONVERT::ToObject(thisArg);
    auto V = std::get<std::shared_ptr<JS::InternalObject>>(args["0"].getValue());
    while (V->prototype != nullptr) {
        V = V->prototype;
        if (V.get() == O.get()) {
            return JS::Any(true);
        }
    }
    return JS::Any(false);
}

JS::Any Object::propertyIsEnumerable(const JS::Any& thisArg, const JS::Any& args) {
    const std::string P = JS::CONVERT::ToString(args["0"]);
    const std::shared_ptr<InternalObject> O = JS::CONVERT::ToObject(thisArg);
    const std::optional<JS::Attribute> desc = O->getOwnProperty(P);
    if (!desc.has_value()) {
        return JS::Any(false);
    }
    return JS::Any(JS::IS::DataDescriptor(desc.value()) && std::get<JS::DataDescriptor>(desc.value()).enumerable ||
                   JS::IS::AccessorDescriptor(desc.value()) &&
                       std::get<JS::AccessorDescriptor>(desc.value())
                           .enumerable); // TODO can be optimized with a genericDescriptor with enumerable
}
} // namespace JS
