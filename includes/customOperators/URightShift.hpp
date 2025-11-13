#ifndef URIGHTSHIFT_HPP
#define URIGHTSHIFT_HPP

#include "SyntaxSmith.hpp"

#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

inline JS::Any UnsignedRightShiftOperatorFunction(JS::Any any,
                                                  const JS::Any& other) { // TODO: fix CREATE_OPERATOR to handle any has a reference to
                                                                          // avoid a copy with std::forward and std::move
    return JS::Any(static_cast<int>(JS::CONVERT::ToUint32(any) >> (JS::CONVERT::ToUint32(other) & 0x1F)));
}

CREATE_OPERATOR(UnsignedRightShiftOperator, UnsignedRightShiftOperatorFunction)
#define URightShift <UnsignedRightShiftOperatorClass()>

#endif // URIGHTSHIFT_HPP
