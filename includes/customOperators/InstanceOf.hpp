//
// Created by Simon BANDIERA on 26/02/2025.
//

#ifndef INSTANCEOF_HPP
#define INSTANCEOF_HPP

#include "SyntaxSmith.hpp"
#include <types/JsAny.hpp>
#include <utils/Compare.hpp>


inline JS::Any instanceOfFunction(JS::Any a, JS::Any b) {
    if (JS::COMPARE::Type(a, JS::OBJECT) == false) {
        throw std::runtime_error("TypeError: Left-hand side of 'instanceof' is not an object"); // TODO: type error
    }

    auto obj = std::get<std::shared_ptr<JS::InternalObject>>(a.getValue());
    //    return JS::Any(obj->hasInstance(b)); TODO: uncomment when merging https://github.com/JS-CMP/JS-CMP/pull/60
    return {};
}

CREATE_OPERATOR(instanceOf, instanceOfFunction)
#define instanceOf <instanceOfClass()>




#endif //INSTANCEOF_HPP
