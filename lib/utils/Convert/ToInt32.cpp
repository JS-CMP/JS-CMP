#include "types/JsAny.hpp"

#include <cmath>
#include <utils/Convert.hpp>

namespace JS::CONVERT {
template <typename T>
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

template int32_t ToInt32(int);
template int32_t ToInt32(double);
template int32_t ToInt32(bool);
template int32_t ToInt32(const std::string&);
template int32_t ToInt32(const char*);
template int32_t ToInt32(const Rope&);
template int32_t ToInt32(JS::Null);
template int32_t ToInt32(JS::Undefined);
template int32_t ToInt32(JS::Any);
template int32_t ToInt32(const JS::Any&);
} // namespace JS::CONVERT