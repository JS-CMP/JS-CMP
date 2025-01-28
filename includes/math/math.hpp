#ifndef JS_CMP_MATH_HPP
#define JS_CMP_MATH_HPP
#include "../includes/types/Types.hpp"
#include "../includes/utils/Convert.hpp"

class Math {
public:
    static JS::Any abs(const JS::Any &x);
    static JS::Any acos(const JS::Any &x);
    static JS::Any asin(const JS::Any &x);
    static JS::Any atan(const JS::Any &x);
    static JS::Any atan2(const JS::Any &y, const JS::Any &x);
    static JS::Any ceil(const JS::Any &x);
    static JS::Any cos(const JS::Any &x);
    static JS::Any exp(const JS::Any &x);
    static JS::Any floor(const JS::Any &x);
    static JS::Any log(const JS::Any &x);
    static JS::Any max(const std::vector<JS::Any> &x);
    static JS::Any min(const std::vector<JS::Any> &x);
    static JS::Any pow(const JS::Any &x, const JS::Any &y);
    static JS::Any random();
    static JS::Any round(const JS::Any &x);
    static JS::Any sin(const JS::Any &x);
    static JS::Any sqrt(const JS::Any &x);
    static JS::Any tan(const JS::Any &x);
    constexpr static double e = 2.7182818284590452354;
    constexpr static double ln10 = 2.302585092994046;
    constexpr static double ln2 = 0.6931471805599453;
    constexpr static double log2e = 2.302585092994046;
    constexpr static double log10e = 0.4342944819032518;
    constexpr static double pi = 3.1415926535897932;
    constexpr static double sqrt1_2 = 0.7071067811865476;
    constexpr static double sqrt2 = 1.4142135623730951;

};

#endif //JS_CMP_MATH_HPP
