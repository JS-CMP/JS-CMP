#include "../../includes/global/global_isNaN.hpp"

bool global_isNaN(const JS::Any& number) {
    double value;
    try {
        value = JS::CONVERT::ToNumber(number);
    } catch (const std::exception&) { return false; }

    return std::isnan(value) || std::isinf(value);
}