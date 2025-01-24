#include "../../includes/global/globalFunctions.hpp"
#include "../../includes/utils/Convert.hpp"

bool global_isNaN(const JS::Any& number) {
    return std::isnan(JS::CONVERT::ToNumber(number));
}