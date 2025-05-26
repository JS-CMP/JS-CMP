#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

DECLARE_1FUNC(JS::Any JS::Any::operator&&, const {
    return !JS::CONVERT::ToBoolean(*this) ? *this : JS::Any(value);
})

namespace JS {

DECLARE_2FUNC(JS::Any operator&&,{
    return !JS::CONVERT::ToBoolean(value) ? JS::Any(value) : JS::Any(any);
})
} // namespace JS