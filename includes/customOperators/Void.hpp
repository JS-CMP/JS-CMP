#ifndef VOID_HPP
#define VOID_HPP

#include "SyntaxSmith.hpp"

#include <types/JsAny.hpp>

inline JS::Any voidFunction(const JS::Any& a) {
    // suposed to call getValue because of :
    // GetValue must be called even though its value is not used because it may have observable side-effects.
    // since we dont have references might be a problem hahahahahahhahahahahhaha
    static_cast<void>(a);
    return JS::Any(JS::Undefined());
}

CREATE_ONE_SIDE_OPERATOR(voidF, voidFunction)
#define Void voidFClass() >

#endif // VOID_HPP
