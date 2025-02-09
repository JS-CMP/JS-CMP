#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

template <JS::AllowedType T, JS::AllowedType U>
JS::Any UnsignedRightShiftOperator(T any, U other) {
    return JS::Any(static_cast<int>(JS::CONVERT::ToUint32(any) >> (JS::CONVERT::ToUint32(other) & 0x1F)));
}
