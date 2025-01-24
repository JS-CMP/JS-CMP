#include "../../includes/global/global_isNaN.hpp"

bool global_isNaN(const JS::Any& number) {
    return std::isnan(JS::CONVERT::ToNumber(number));
}