#include "types/JsAny.hpp"

#include <cmath>
#include <utils/Convert.hpp>

namespace JS::CONVERT {
template <JS::AllowedType T>
int16_t ToInt16(const T& value) {
    double temp = ToNumber(value);

    if (!std::isfinite(temp) || std::isnan(temp) || temp == 0) {
        return 0;
    }

    double posInt = std::copysign(std::floor(std::fabs(temp)), temp);
    constexpr double two16 = 65536.0;
    double int16bit = std::fmod(posInt, two16);

    if (int16bit < 0) {
        int16bit += two16;
    }

    return static_cast<uint16_t>(int16bit);
}
} // namespace JS::CONVERT