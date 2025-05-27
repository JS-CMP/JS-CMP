#ifndef DEBUGGER_HPP
#define DEBUGGER_HPP

#include "SyntaxSmith.hpp"

#include <types/JsAny.hpp>

inline JS::Any debugFunction() { return {}; }

CREATE_NO_ARGS_OPERATOR(debug, debugFunction)
#define debugger debugClass()

#endif // DEBUGGER_HPP
