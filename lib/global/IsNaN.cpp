#include "types/JsAny.hpp"
#include "utils/Convert.hpp"
#include "internals/PropertyProxy.hpp"
#include <cmath>

namespace JS::GLOBAL {
JS::Any isNaN(const JS::Any &thisArgs, const JS::Any &args) { return JS::Any(std::isnan(JS::CONVERT::ToNumber(args["0"]))); }
} // namespace JS::GLOBAL