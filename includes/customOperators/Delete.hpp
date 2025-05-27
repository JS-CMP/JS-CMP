#ifndef DELETE_HPP
#define DELETE_HPP

#include "SyntaxSmith.hpp"

#include <types/JsAny.hpp>

inline JS::Any deleteFunction(JS::Any a) {
    // todo: implement when global object contains all variables
    // should be implemented in the
    return {};
}

CREATE_ONE_SIDE_OPERATOR(del, deleteFunction)
#define del delClass()

#endif // DELETE_HPP
