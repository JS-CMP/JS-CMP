#ifndef JS_CMP_GLOBAL_PARSEINT_HPP
#define JS_CMP_GLOBAL_PARSEINT_HPP

#include "../includes/types/JsAny.hpp"
#include <cctype>
#include <stdexcept>
#include <cmath>
#include <iostream>
JS::Any global_parseInt(const std::string& inputString, int radix);

#endif //JS_CMP_GLOBAL_PARSEINT_HPP
