#ifndef EQUALITY_HPP
#define EQUALITY_HPP

#include <types/JsAny.hpp>
#include "SyntaxSmith.hpp"

inline JS::Any strictEqFunction(JS::Any a, JS::Any b) {
    if (a.getValue().index() != b.getValue().index()) {
        return JS::Any(false);
    }

    if (a.getValue().index() == JS::OBJECT) {
        return JS::Any(std::get<std::shared_ptr<JS::InternalObject>>(a.getValue()) ==
               std::get<std::shared_ptr<JS::InternalObject>>(b.getValue()));
    }

    return JS::Any(a == b);
}

CREATE_OPERATOR(strictEq, strictEqFunction)
#define strictEq <strictEqClass()>

inline JS::Any strictNeqFunction(const JS::Any& a, const JS::Any& b) {
    return !strictEqFunction(a, b);
}

CREATE_OPERATOR(strictNeq, strictNeqFunction)
#define strictNeq <strictNeqClass()>

#endif //EQUALITY_HPP
