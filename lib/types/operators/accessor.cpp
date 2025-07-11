#include "internals/PropertyProxy.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

#include <internals/Operator.hpp>
#include <types/JsAny.hpp>
#include <types/objects/Function/JsFunction.hpp>

DECLARE_1FUNC(
    JS::PropertyProxy JS::Operator::operator[], const {
        JS::COMPARE::CheckObjectCoercible(*this);
        auto data = JS::CONVERT::ToObject(*this);
        return JS::PropertyProxy(data, JS::CONVERT::ToString(value));
    })

JS::Any JS::Operator::call(const JS::Any& args) const {
    if (this->getValue().index() == JS::OBJECT && std::get<std::shared_ptr<JS::InternalObject>>(this->getValue())->isCallable()) {
        return std::get<std::shared_ptr<JS::InternalObject>>(this->getValue())->call_function(
            this->get(), args); // TODO fix this to pass the correct this aka global object
    }
    throw std::runtime_error("Value is not a function");
}

JS::Any JS::Operator::constructor(const JS::Any& args) const {
    if (this->getValue().index() == JS::OBJECT) {
        auto Obj = std::get<std::shared_ptr<JS::InternalObject>>(this->getValue());
        if (Obj->construct != nullptr) {
            return Obj->construct(JS::Any(Obj), args);
        }
    }
    throw std::runtime_error("Value does not have a constructor");
}

namespace JS {
std::ostream& operator<<(std::ostream& os, const JS::Operator& any) {
    os << JS::CONVERT::ToUtf8(JS::CONVERT::ToString(any));
    return os;
}
} // namespace JS