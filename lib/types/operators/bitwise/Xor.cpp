#include <internals/Operator.hpp>
#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

DECLARE_1FUNC(
    JS::Any JS::Operator::operator^, const { return JS::Any(JS::CONVERT::ToInt32(*this) ^ JS::CONVERT::ToInt32(value)); })

namespace JS {

DECLARE_2FUNC(JS::Any operator^,{ return JS::Any(JS::CONVERT::ToInt32(value) ^ JS::CONVERT::ToInt32(any)); })
} // namespace JS
