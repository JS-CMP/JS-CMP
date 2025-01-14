#ifndef JS_CMP_GLOBAL_PARSEFLOAT_HPP
#define JS_CMP_GLOBAL_PARSEFLOAT_HPP

#include "../includes/types/JsAny.hpp"

#include <cctype>
#include <limits>
#include <string>
JS::Any global_parseFloat(const std::string& inputString);

#endif // JS_CMP_GLOBAL_PARSEFLOAT_HPP
