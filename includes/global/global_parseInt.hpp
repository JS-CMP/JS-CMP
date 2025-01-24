#ifndef JS_CMP_GLOBAL_PARSEINT_HPP
#define JS_CMP_GLOBAL_PARSEINT_HPP

#include "../includes/types/JsAny.hpp"
#include "../includes/utils/Convert.hpp"
#include <cctype>
#include <stdexcept>
#include <cmath>
#include <iostream>
JS::Any global_parseInt(JS::Any inputStringAny, JS::Any radixAny);

#endif //JS_CMP_GLOBAL_PARSEINT_HPP
