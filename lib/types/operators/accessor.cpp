#include "internals/PropertyProxy.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"
#include "utils/Is.hpp"

#include <internals/Operator.hpp>
#include <types/JsAny.hpp>
#include <types/objects/Error/JsTypeError.hpp>
#include <types/objects/Function/JsFunction.hpp>

DECLARE_1FUNC(
    JS::PropertyProxy JS::Operator::operator[], const {
        JS::COMPARE::CheckObjectCoercible(*this);
        auto data = JS::CONVERT::ToObject(*this);
        return JS::PropertyProxy(data, JS::CONVERT::ToString(value));
    })

JS::Any JS::Operator::call(const JS::Any& args) const {
    if (JS::IS::Callable(this->getValue())) {
        return std::get<std::shared_ptr<JS::InternalObject>>(this->getValue())->call_function(
            JS::Any(JS::Undefined{}), args); // TODO fix this to pass the correct this aka global object
    }
    throw JS::Any(JS::TypeError(JS::Any("Value is not a function")));
}

JS::Any JS::Operator::constructor(const JS::Any& args) const {
    if (this->getValue().index() == JS::OBJECT) {
        auto Obj = std::get<std::shared_ptr<JS::InternalObject>>(this->getValue());
        if (Obj->construct != nullptr) {
            return Obj->construct(JS::Any(Obj), args);
        }
    }
    throw JS::Any(JS::TypeError(JS::Any("Value does not have a constructor")));
}

namespace JS {
std::ostream& operator<<(std::ostream& os, const JS::Operator& any) {
    os << JS::CONVERT::ToUtf8(JS::CONVERT::ToString(any));
    return os;
}
} // namespace JS