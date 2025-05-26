#include "internals/PropertyProxy.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

#include <types/JsAny.hpp>
#include <types/objects/Function/JsFunction.hpp>

template <typename T>
JS::PropertyProxy JS::Any::operator[](T key) const {
    JS::COMPARE::CheckObjectCoercible(*this);
    auto value = JS::CONVERT::ToObject(*this);
    return JS::PropertyProxy(value, JS::CONVERT::ToString(key));
}

DECLARE_1FUNC(template JS::PropertyProxy JS::Any::operator[], const)
template JS::PropertyProxy JS::Any::operator[](JS::Any) const;
template JS::PropertyProxy JS::Any::operator[](JS::PropertyProxy) const;

JS::Any JS::Any::call(const JS::Any& args) const {
    if (value.index() == JS::OBJECT && std::get<std::shared_ptr<JS::InternalObject>>(value)->isCallable()) {
        return std::get<std::shared_ptr<JS::InternalObject>>(value)->call_function(
            JS::Any(JS::Undefined{}), args); // TODO fix this to pass the correct this aka global object
    }
    throw std::runtime_error("Value is not a function");
}