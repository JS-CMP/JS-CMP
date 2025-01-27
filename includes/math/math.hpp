#ifndef JS_CMP_MATH_HPP
#define JS_CMP_MATH_HPP
#include "../includes/types/Types.hpp"
#include "../includes/utils/Convert.hpp"

class Math {
public:
    JS::Any abs(const JS::Any& x);
    JS::Any acos(const JS::Any& x);
    JS::Any asin(const JS::Any& x);
    JS::Any atan(const JS::Any& x);
    JS::Any atan2(const JS::Any& y, const JS::Any& x);
    JS::Any ceil(const JS::Any& x);
    JS::Any cos(const JS::Any& x);
    JS::Any exp(const JS::Any& x);
    JS::Any floor(const JS::Any& x);
    JS::Any log(const JS::Any& x);
    JS::Any max(const std::vector<JS::Any>& x);
    JS::Any min(const JS::Any& x);
    JS::Any pow(const JS::Any& x, const JS::Any& y);
    JS::Any random();
    JS::Any round(const JS::Any& x);
    JS::Any sin(const JS::Any& x);
    JS::Any sqrt(const JS::Any& x);
    JS::Any tan(const JS::Any& x);

private:
    constexpr static double e = 2.7182818284590452354;
    constexpr static double ln10 = 2.302585092994046;
    constexpr static double ln2 = 0.6931471805599453;
    constexpr static double log2e = 2.302585092994046;
    constexpr static double log10e = 0.4342944819032518;
    constexpr static double pi = 3.1415926535897932;
    constexpr static double sqrt1_2 = 0.7071067811865476;
    constexpr static double sqrt2 = 1.4142135623730951;
};

#endif // JS_CMP_MATH_HPP
