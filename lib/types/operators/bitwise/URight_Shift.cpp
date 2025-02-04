#include "../../../../includes/types/JsAny.hpp"
#include "../../../../includes/utils/Convert.hpp"

JS::Any UnsignedRightShiftOperator(const JS::Any& any, const JS::Any& other) {
    uint32_t lnum = JS::CONVERT::ToUint32(any);
    uint32_t shiftCount = JS::CONVERT::ToUint32(other) & 0x1F;
    return JS::Any(static_cast<int>(lnum >> shiftCount));
}

JS::Any UnsignedRightShiftOperator(const JS::Any& any, int value) {
    uint32_t lnum = JS::CONVERT::ToUint32(any);
    uint32_t shiftCount = JS::CONVERT::ToUint32(value) & 0x1F;
    return JS::Any(static_cast<int>(lnum >> shiftCount));
}

JS::Any UnsignedRightShiftOperator(const JS::Any& any, double value) {
    uint32_t lnum = JS::CONVERT::ToUint32(any);
    uint32_t shiftCount = JS::CONVERT::ToUint32(value) & 0x1F;
    return JS::Any(static_cast<int>(lnum >> shiftCount));
}

JS::Any UnsignedRightShiftOperator(const JS::Any& any, const char* value) {
    uint32_t lnum = JS::CONVERT::ToUint32(any);
    uint32_t shiftCount = JS::CONVERT::ToUint32(value) & 0x1F;
    return JS::Any(static_cast<int>(lnum >> shiftCount));
}

JS::Any UnsignedRightShiftOperator(const JS::Any& any, bool value) {
    uint32_t lnum = JS::CONVERT::ToUint32(any);
    uint32_t shiftCount = JS::CONVERT::ToUint32(value) & 0x1F;
    return JS::Any(static_cast<int>(lnum >> shiftCount));
}

JS::Any UnsignedRightShiftOperator(const JS::Any& any, JS::Null value) {
    uint32_t lnum = JS::CONVERT::ToUint32(any);
    uint32_t shiftCount = JS::CONVERT::ToUint32(value) & 0x1F;
    return JS::Any(static_cast<int>(lnum >> shiftCount));
}

JS::Any UnsignedRightShiftOperator(const JS::Any& any, JS::Undefined value) {
    uint32_t lnum = JS::CONVERT::ToUint32(any);
    uint32_t shiftCount = JS::CONVERT::ToUint32(value) & 0x1F;
    return JS::Any(static_cast<int>(lnum >> shiftCount));
}

JS::Any UnsignedRightShiftOperator(int value, const JS::Any& other) {
    uint32_t lnum = JS::CONVERT::ToUint32(value);
    uint32_t shiftCount = JS::CONVERT::ToUint32(other) & 0x1F;
    return JS::Any(static_cast<int>(lnum >> shiftCount));
}

JS::Any UnsignedRightShiftOperator(double value, const JS::Any& other) {
    uint32_t lnum = JS::CONVERT::ToUint32(value);
    uint32_t shiftCount = JS::CONVERT::ToUint32(other) & 0x1F;
    return JS::Any(static_cast<int>(lnum >> shiftCount));
}

JS::Any UnsignedRightShiftOperator(const char* value, const JS::Any& other) {
    uint32_t lnum = JS::CONVERT::ToUint32(value);
    uint32_t shiftCount = JS::CONVERT::ToUint32(other) & 0x1F;
    return JS::Any(static_cast<int>(lnum >> shiftCount));
}

JS::Any UnsignedRightShiftOperator(bool value, const JS::Any& other) {
    uint32_t lnum = JS::CONVERT::ToUint32(value);
    uint32_t shiftCount = JS::CONVERT::ToUint32(other) & 0x1F;
    return JS::Any(static_cast<int>(lnum >> shiftCount));
}

JS::Any UnsignedRightShiftOperator(JS::Null value, const JS::Any& other) {
    uint32_t lnum = JS::CONVERT::ToUint32(value);
    uint32_t shiftCount = JS::CONVERT::ToUint32(other) & 0x1F;
    return JS::Any(static_cast<int>(lnum >> shiftCount));
}

JS::Any UnsignedRightShiftOperator(JS::Undefined value, const JS::Any& other) {
    uint32_t lnum = JS::CONVERT::ToUint32(value);
    uint32_t shiftCount = JS::CONVERT::ToUint32(other) & 0x1F;
    return JS::Any(static_cast<int>(lnum >> shiftCount));
}

