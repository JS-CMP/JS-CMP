#ifndef JS_CMP_GLOBAL_PARSEINT_HPP
#define JS_CMP_GLOBAL_PARSEINT_HPP

#include "../includes/types/JsAny.hpp"

#include <cctype>
#include <cmath>
#include <iostream>
#include <stdexcept>
JS::Any global_parseInt(const std::string& inputString, int radix);

#endif // JS_CMP_GLOBAL_PARSEINT_HPP
