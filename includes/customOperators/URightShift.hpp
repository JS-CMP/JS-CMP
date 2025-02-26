#ifndef URIGHTSHIFT_HPP
#define URIGHTSHIFT_HPP

#include <types/JsAny.hpp>
#include "SyntaxSmith.hpp"
#include <utils/Convert.hpp>

// TODO: by essence, custom operators can't be templated since a templated function cant be called with & \
//  which is necessary in SyntaxSmith to stock the return value / args type you want to use, need to rework this if \
//  other types are needed

//
// template <typename T, typename U>
// JS::Any UnsignedRightShiftOperatorFunction(T any, U other) {
//     return JS::Any(static_cast<int>(JS::CONVERT::ToUint32(any) >> (JS::CONVERT::ToUint32(other) & 0x1F)));
// }
//
// template JS::Any UnsignedRightShiftOperatorFunction(const JS::Any&, const JS::Any&);
// template JS::Any UnsignedRightShiftOperatorFunction(const JS::Any&, int);
// template JS::Any UnsignedRightShiftOperatorFunction(const JS::Any&, double);
// template JS::Any UnsignedRightShiftOperatorFunction(const JS::Any&, const char*);
// template JS::Any UnsignedRightShiftOperatorFunction(const JS::Any&, bool);
// template JS::Any UnsignedRightShiftOperatorFunction(const JS::Any&, JS::Null);
// template JS::Any UnsignedRightShiftOperatorFunction(const JS::Any&, JS::Undefined);
// template JS::Any UnsignedRightShiftOperatorFunction(int, const JS::Any&);
// template JS::Any UnsignedRightShiftOperatorFunction(double, const JS::Any&);
// template JS::Any UnsignedRightShiftOperatorFunction(const char*, const JS::Any&);
// template JS::Any UnsignedRightShiftOperatorFunction(bool, const JS::Any&);
// template JS::Any UnsignedRightShiftOperatorFunction(JS::Null, const JS::Any&);
// template JS::Any UnsignedRightShiftOperatorFunction(JS::Undefined, const JS::Any&);

 JS::Any UnsignedRightShiftOperatorFunction(JS::Any any, JS::Any other) {
     return JS::Any(static_cast<int>(JS::CONVERT::ToUint32(any) >> (JS::CONVERT::ToUint32(other) & 0x1F)));
 }


CREATE_OPERATOR(UnsignedRightShiftOperator, UnsignedRightShiftOperatorFunction)
 #define UnsignedRightShiftOperator <UnsignedRightShiftOperatorClass()>



#endif //URIGHTSHIFT_HPP
