#ifndef EQUALITY_HPP
#define EQUALITY_HPP

#include "SyntaxSmith.hpp"

#include <types/JsAny.hpp>

inline JS::Any strictEqFunction(JS::Any a, const JS::Any& b) { // TODO: fix CREATE_OPERATOR to handle a has a reference
                                                               // to avoid a copy with std::forward and std::move
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

inline JS::Any strictNeqFunction(JS::Any a, const JS::Any& b) {
    return !strictEqFunction(a, b);
}

CREATE_OPERATOR(strictNeq, strictNeqFunction)
#define strictNeq <strictNeqClass()>

#endif // EQUALITY_HPP
