#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

template <typename T, typename U>
JS::Any UnsignedRightShiftOperator(T any, U other) {
    return JS::Any(static_cast<int>(JS::CONVERT::ToUint32(any) >> (JS::CONVERT::ToUint32(other) & 0x1F)));
}

template JS::Any UnsignedRightShiftOperator(const JS::Any&, const JS::Any&);
template JS::Any UnsignedRightShiftOperator(const JS::Any&, int);
template JS::Any UnsignedRightShiftOperator(const JS::Any&, double);
template JS::Any UnsignedRightShiftOperator(const JS::Any&, const char*);
template JS::Any UnsignedRightShiftOperator(const JS::Any&, bool);
template JS::Any UnsignedRightShiftOperator(const JS::Any&, JS::Null);
template JS::Any UnsignedRightShiftOperator(const JS::Any&, JS::Undefined);
template JS::Any UnsignedRightShiftOperator(int, const JS::Any&);
template JS::Any UnsignedRightShiftOperator(double, const JS::Any&);
template JS::Any UnsignedRightShiftOperator(const char*, const JS::Any&);
template JS::Any UnsignedRightShiftOperator(bool, const JS::Any&);
template JS::Any UnsignedRightShiftOperator(JS::Null, const JS::Any&);
template JS::Any UnsignedRightShiftOperator(JS::Undefined, const JS::Any&);
