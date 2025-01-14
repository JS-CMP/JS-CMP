#include "../../includes/global/global_isFinite.hpp"

bool global_isFinite(const JS::Any& number) {
    try {
        double value = JS::CONVERT::ToNumber(number);

        if (std::isnan(value) || value == std::numeric_limits<double>::infinity() ||
            value == -std::numeric_limits<double>::infinity()) {
            return false;
        }
        return true;
    } catch (const std::exception&) { return false; }
}
