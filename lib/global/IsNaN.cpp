#include "types/JsAny.hpp"
#include "utils/Convert.hpp"

#include <cmath>

JS::Any isNaN(const std::vector<JS::Any>& args) { return JS::Any(std::isnan(JS::CONVERT::ToNumber(args[0]))); }