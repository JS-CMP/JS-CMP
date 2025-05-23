//
// Created by Simon BANDIERA on 04/03/2025.
//

#ifndef TYPEOF_HPP
#define TYPEOF_HPP

#include "SyntaxSmith.hpp"
#include "global/globalFunctions.hpp"

CREATE_ONE_SIDE_OPERATOR(typeOf, JS::GLOBAL::global_typeof)
#define typeOf typeOfClass() >

#endif // TYPEOF_HPP
