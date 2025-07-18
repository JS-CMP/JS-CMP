#ifndef INSTANCEOF_HPP
#define INSTANCEOF_HPP

#include "SyntaxSmith.hpp"

#include <internals/Object.hpp>
#include <types/JsAny.hpp>
#include <types/objects/Error/JsTypeError.hpp>
#include <utils/Compare.hpp>

inline JS::Any instanceOfFunction(JS::Any a,
                                  const JS::Any& b) { // TODO: fix CREATE_OPERATOR to handle a has a reference to avoid
                                                      // a copy with std::forward and std::move
    if (JS::COMPARE::Type(a, JS::OBJECT) == false) {
        throw JS::Any(std::make_shared<JS::TypeError>(JS::Any("Left-hand side of 'instanceof' is not an object")));
    }

    auto obj = std::get<std::shared_ptr<JS::InternalObject>>(a.getValue());
    return JS::Any(obj->hasInstance(b));
}

CREATE_OPERATOR(instanceOf, instanceOfFunction)
#define instanceof <instanceOfClass()>

#endif // INSTANCEOF_HPP
