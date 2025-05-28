#include "types/objects/Function/JsFunction.hpp"
#include "utils/Compare.hpp"

namespace JS {
JS::Any Function::get(const std::u16string& key) const {
    if (key == u"caller") {
        throw std::runtime_error("TypeError: Cannot access 'caller' or 'arguments.callee' in strict mode"); // TypeError
    }
    return InternalObject::get(key);
}

bool Function::hasInstance(const JS::Any& value) const {
    if (!JS::COMPARE::Type(value, JS::OBJECT)) {
        return false;
    }
    JS::Any O = std::get<std::shared_ptr<InternalObject>>(value.getValue())->get(u"prototype");
    if (!JS::COMPARE::Type(O, JS::OBJECT)) {
        throw std::runtime_error("TypeError: Function.prototype[Symbol.hasInstance] called on non-object"); // TypeError
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
} // namespace JS