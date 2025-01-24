#include "../../includes/global/global_isFinite.hpp"

bool global_isFinite(const JS::Any& number) {
    return std::isfinite(JS::CONVERT::ToNumber(number));
}

