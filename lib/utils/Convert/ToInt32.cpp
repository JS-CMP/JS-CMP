#include "types/JsAny.hpp"

#include <cmath>
#include <utils/Convert.hpp>

namespace JS::CONVERT {
template <JS::AllowedType T>
int32_t ToInt32(T value) {
    constexpr double two32 = 4294967296.0;

    double temp = ToNumber(value);

    if (!std::isfinite(temp) || std::isnan(temp) || temp == 0) {
        return 0;
    }
    double posInt = std::copysign(std::floor(std::fabs(temp)), temp);
    double int32bit = std::fmod(posInt, two32);
    if (int32bit < 0) {
        int32bit += two32;
    }
    constexpr double two31 = 2147483648.0;
    if (int32bit >= two31) {
        return static_cast<int32_t>(int32bit - two32);
    }
    return static_cast<int32_t>(int32bit);
}


} // namespace JS::CONVERT