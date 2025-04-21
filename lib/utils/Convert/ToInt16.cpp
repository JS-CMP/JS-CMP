#include "types/JsAny.hpp"

#include <cmath>
#include <utils/Convert.hpp>

namespace JS::CONVERT {

template <typename T>
int16_t ToInt16(T value) {
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

template int16_t ToInt16(const int&);
template int16_t ToInt16(const double&);
template int16_t ToInt16(const bool&);
template int16_t ToInt16(const std::string&);
template int16_t ToInt16(const char*);
template int16_t ToInt16(const Rope&);
template int16_t ToInt16(const JS::Null&);
template int16_t ToInt16(const JS::Undefined&);
template int16_t ToInt16(const JS::Any&);
} // namespace JS::CONVERT