#include "types/objects/Function/JsFunction.hpp"
#include "utils/Compare.hpp"

#include <types/objects/Error/JsTypeError.hpp>
#include <utils/Convert.hpp>

namespace JS {
JS::Any Function::get(const std::u16string& key) const {
    if (key == u"caller") {
        throw JS::Any(
            JS::InternalObject::create<JS::TypeError>(JS::Any("Cannot access 'caller' or 'arguments.callee' in strict mode")));
    }
    return InternalObject::get(key);
}

bool Function::hasInstance(const JS::Any& value) const {
    if (!JS::COMPARE::Type(value, JS::OBJECT)) {
        return false;
    }
    JS::Any O = this->get(u"prototype");
    if (!JS::COMPARE::Type(O, JS::OBJECT)) {
        throw JS::Any(
            JS::InternalObject::create<JS::TypeError>(JS::Any("Function.prototype[Symbol.hasInstance] called on non-object")));
    }
    std::shared_ptr<JS::InternalObject> obj = std::get<std::shared_ptr<JS::InternalObject>>(O.getValue());
    std::shared_ptr<JS::InternalObject> V = std::get<std::shared_ptr<JS::InternalObject>>(value.getValue());
    while (V->prototype != nullptr) {
        V = V->prototype;
        if (V.get() == obj.get()) {
            return true;
        }
    }
    return false;
}

std::u16string Function::getContent() const {
    return u"[Function: ]"; // TODO: add function name
}

std::shared_ptr<JS::Function> JS::Function::getConstructor(std::shared_ptr<JS::InternalObject> instance) {
    auto prototype = instance ? instance : Function::getPrototypeProperties();
    static auto constructor = JS::InternalObject::create<JS::Function>( [] (const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
        auto len = CONVERT::ToUint32(args[u"length"]);
        if (len < 1) {
            return JS::Any(JS::InternalObject::create<JS::Function>());
        }
        throw std::runtime_error("Not implemented"); // TODO:: Fix + change error
    }, 1, OBJECT_CLASS_NAME, prototype);

    constructor->class_name = OBJECT_CLASS_NAME;
    constructor->extensible = true;
    constructor->prototype = prototype;
    constructor->properties = std::make_shared<JS::Properties>(JS::Properties{
        {u"length", JS::DataDescriptor{JS::Any(1), false, false, false}},
        {u"name", JS::DataDescriptor{JS::Any(FUNCTION_CLASS_NAME), false, false, false}},
    });
    return constructor;
}
} // namespace JS