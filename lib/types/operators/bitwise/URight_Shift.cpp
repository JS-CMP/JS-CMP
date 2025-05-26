#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

DECLARE_2FUNC_TWO_WAYS(JS::Any UnsignedRightShiftOperator, {
    return JS::Any(static_cast<int>(JS::CONVERT::ToUint32(any) >> (JS::CONVERT::ToUint32(value) & 0x1F)));
})
