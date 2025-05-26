#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

DECLARE_1FUNC(JS::Any JS::Any::operator-, const {
    return JS::Any(JS::CONVERT::ToNumber(*this) - JS::CONVERT::ToNumber(value));
})

namespace JS {
DECLARE_2FUNC(JS::Any operator-,{
    return JS::Any(JS::CONVERT::ToNumber(value) - JS::CONVERT::ToNumber(any));
})
} // namespace JS
