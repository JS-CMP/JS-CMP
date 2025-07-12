#ifndef TYPEOF_HPP
#define TYPEOF_HPP

#include "SyntaxSmith.hpp"
#include <types/JsAny.hpp>

inline JS::Any type_of(const JS::Any& a) {
    switch (a.getValue().index()) {
        case JS::NUMBER:
            return JS::Any("number");
        case JS::STRING:
            return JS::Any("string");
        case JS::BOOLEAN:
            return JS::Any("boolean");
        case JS::UNDEFINED:
            return JS::Any("undefined");
        case JS::NULL_TYPE:
            return JS::Any("object");
        default:
            return JS::Any("object");
    }
}

CREATE_ONE_SIDE_OPERATOR(typeOf, type_of)
#define typeOf typeOfClass() >

#endif // TYPEOF_HPP
