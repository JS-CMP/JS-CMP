//
// Created by Simon BANDIERA on 26/02/2025.
//

#ifndef IN_HPP
#define IN_HPP

#include "SyntaxSmith.hpp"
#include <types/JsAny.hpp>
#include <utils/Compare.hpp>
#include <utils/Convert.hpp>

inline JS::Any inFunction(JS::Any a, JS::Any b) {
    if (JS::COMPARE::Type(a, JS::OBJECT) == false) {
        throw std::runtime_error("TypeError: Cannot use 'in' operator on non-object"); // TODO: type error
    }

    auto obj = std::get<std::shared_ptr<JS::InternalObject>>(a.getValue());
//    return JS::Any(obj->hasProperty(JS::CONVERT::ToString(b))); TODO: uncomment when merging functions
    return {};
}

CREATE_OPERATOR(in, inFunction)
#define in <inClass()>



#endif //IN_HPP
