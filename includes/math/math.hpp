#ifndef JS_CMP_MATH_HPP
#define JS_CMP_MATH_HPP

#include <vector>
#include "../includes/types/Types.hpp"
#include "../includes/utils/Convert.hpp"

class Math {
public:
    static JS::Any abs(const std::vector<JS::Any>& args);
    static JS::Any acos(const std::vector<JS::Any>& args);
    static JS::Any asin(const std::vector<JS::Any>& args);
    static JS::Any atan(const std::vector<JS::Any>& args);
    static JS::Any atan2(const std::vector<JS::Any>& args);
    static JS::Any ceil(const std::vector<JS::Any>& args);
    static JS::Any cos(const std::vector<JS::Any>& args);
    static JS::Any exp(const std::vector<JS::Any>& args);
    static JS::Any floor(const std::vector<JS::Any>& args);
    static JS::Any log(const std::vector<JS::Any>& args);
    static JS::Any max(const std::vector<JS::Any>& args);
    static JS::Any min(const std::vector<JS::Any>& args);
    static JS::Any pow(const std::vector<JS::Any>& args);
    static JS::Any random(const std::vector<JS::Any>& args);
    static JS::Any round(const std::vector<JS::Any>& args);
    static JS::Any sin(const std::vector<JS::Any>& args);
    static JS::Any sqrt(const std::vector<JS::Any>& args);
    static JS::Any tan(const std::vector<JS::Any>& args);

    constexpr static double E = 2.7182818284590452354;
    constexpr static double LN10 = 2.302585092994046;
    constexpr static double LN2 = 0.6931471805599453;
    constexpr static double LOG2e = 2.302585092994046;
    constexpr static double LOG10E = 0.4342944819032518;
    constexpr static double PI = 3.1415926535897932;
    constexpr static double SQRT1_2 = 0.7071067811865476;
    constexpr static double SQRT2 = 1.4142135623730951;
};

#endif // JS_CMP_MATH_HPP
