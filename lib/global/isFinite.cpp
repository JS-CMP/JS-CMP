#include "../../includes/global/globalFunctions.hpp"
#include "../../includes/types/JsAny.hpp"
#include "../../includes/utils/Convert.hpp"

bool global_isFinite(const JS::Any& number) { return std::isfinite(JS::CONVERT::ToNumber(number)); }
