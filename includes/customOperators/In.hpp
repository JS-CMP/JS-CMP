#ifndef IN_HPP
#define IN_HPP
#include "SyntaxSmith.hpp"

#include <internals/Object.hpp>
#include <types/JsAny.hpp>
#include <types/objects/Error/JsTypeError.hpp>
#include <utils/Compare.hpp>
#include <utils/Convert.hpp>

inline JS::Any inFunction(JS::Any a, const JS::Any& b) { // TODO: fix CREATE_OPERATOR to handle a has a reference to
                                                         // avoid a copy with std::forward and std::move
    if (JS::COMPARE::Type(a, JS::OBJECT) == false) {
        throw JS::Any(std::make_shared<JS::TypeError>(JS::Any("Cannot use 'in' operator on non-object")));
    }

    auto obj = std::get<std::shared_ptr<JS::InternalObject>>(a.getValue());
    return JS::Any(obj->hasProperty(JS::CONVERT::ToString(b)));
}

CREATE_OPERATOR(in, inFunction)
#define in <inClass()>

#endif // IN_HPP
