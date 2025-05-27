#ifndef INSTANCEOF_HPP
#define INSTANCEOF_HPP

#include "SyntaxSmith.hpp"

#include <internals/Object.hpp>
#include <types/JsAny.hpp>
#include <utils/Compare.hpp>

inline JS::Any instanceOfFunction(JS::Any a, JS::Any b) {
    if (JS::COMPARE::Type(a, JS::OBJECT) == false) {
        throw std::runtime_error("TypeError: Left-hand side of 'instanceof' is not an object"); // TODO: type error
    }

    auto obj = std::get<std::shared_ptr<JS::InternalObject>>(a.getValue());
    return JS::Any(obj->hasInstance(b));
}

CREATE_OPERATOR(instanceOf, instanceOfFunction)
#define instanceOf <instanceOfClass()>

#endif // INSTANCEOF_HPP
