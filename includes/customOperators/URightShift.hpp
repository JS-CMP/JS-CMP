#ifndef URIGHTSHIFT_HPP
#define URIGHTSHIFT_HPP

#include "SyntaxSmith.hpp"

#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any UnsignedRightShiftOperatorFunction(JS::Any any, JS::Any other) {
    return JS::Any(static_cast<int>(JS::CONVERT::ToUint32(any) >> (JS::CONVERT::ToUint32(other) & 0x1F)));
}

CREATE_OPERATOR(URightShift, UnsignedRightShiftOperatorFunction)
#define URightShift <UnsignedRightShiftOperatorClass()>

#endif // URIGHTSHIFT_HPP
