#include "types/JsAny.hpp"
#include "utils/Convert.hpp"

#include <cmath>

namespace JS::GLOBAL {
JS::Any isFinite(const std::vector<JS::Any>& args) { return JS::Any(std::isfinite(JS::CONVERT::ToNumber(args[1]))); }
} // namespace JS::GLOBAL
