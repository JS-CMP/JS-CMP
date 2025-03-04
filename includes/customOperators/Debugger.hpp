//
// Created by Simon BANDIERA on 04/03/2025.
//

#ifndef DEBUGGER_HPP
#define DEBUGGER_HPP

#include "SyntaxSmith.hpp"

#include <types/JsAny.hpp>

inline JS::Any debugFunction() { exit(0); }

CREATE_ONE_SIDE_OPERATOR(debug, debugFunction)
#define debugger debugClass()

#endif // DEBUGGER_HPP
