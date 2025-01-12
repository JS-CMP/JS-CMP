#ifndef JS_CMP_GLOBAL_PARSEFLOAT_HPP
#define JS_CMP_GLOBAL_PARSEFLOAT_HPP

#include "../includes/types/JsAny.hpp"
#include <string>
#include <cctype>
#include <limits>
JS::Any global_parseFloat(const std::string& inputString);

#endif //JS_CMP_GLOBAL_PARSEFLOAT_HPP
