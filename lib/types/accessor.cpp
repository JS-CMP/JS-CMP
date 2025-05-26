#include "internals/PropertyProxy.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

#include <types/JsAny.hpp>
#include <types/objects/Function/JsFunction.hpp>

DECLARE_1FUNC(JS::PropertyProxy JS::Any::operator[], const {
    JS::COMPARE::CheckObjectCoercible(*this);
    auto data = JS::CONVERT::ToObject(*this);
    return JS::PropertyProxy(data, JS::CONVERT::ToString(value));
})

JS::Any JS::Any::call(const JS::Any& args) const {
    if (value.index() == JS::OBJECT && std::get<std::shared_ptr<JS::InternalObject>>(value)->isCallable()) {
        return std::get<std::shared_ptr<JS::InternalObject>>(value)->call_function(
            JS::Any(JS::Undefined{}), args); // TODO fix this to pass the correct this aka global object
    }
    throw std::runtime_error("Value is not a function");
}