#include "internals/PropertyProxy.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

#include <types/JsAny.hpp>
#include <types/objects/Function/JsFunction.hpp>

DECLARE_1FUNC(
    JS::PropertyProxy JS::Any::operator[], const {
        JS::COMPARE::CheckObjectCoercible(*this);
        auto data = JS::CONVERT::ToObject(*this);
        return JS::PropertyProxy(data, JS::CONVERT::ToString(value));
    })

JS::Any JS::Any::call(const JS::Any& args) const {
    if (value.index() == JS::OBJECT && std::get<std::shared_ptr<JS::InternalObject>>(value)) {
        auto Obj = std::get<std::shared_ptr<JS::InternalObject>>(this->value);
        if (Obj->isCallable()) {
            return Obj->call_function(JS::Any(), args); // TODO replace with JS::Global
        }
    }
    throw std::runtime_error("Value is not a function");
}

JS::Any JS::Any::constructor(const JS::Any& args) const {
    if (value.index() == JS::OBJECT) {
        auto Obj = std::get<std::shared_ptr<JS::InternalObject>>(this->value);
        if (Obj->construct != nullptr) {
            return Obj->construct(JS::Any(Obj), args);
        }
    }
    throw std::runtime_error("Value does not have a constructor");
}