#ifndef JS_CMP_STATICMETHODSNUMBER_HPP
#define JS_CMP_STATICMETHODSNUMBER_HPP

#include "types/JsAny.hpp"

namespace JS::NUM {
    class StaticMethods {
    public:
        // const variable
        constexpr static double MAX_VALUE = 1.7976931348623157e308;
        constexpr static double MIN_VALUE = 5e-324;
        constexpr static double NaN = NAN;
        constexpr static double NEGATIVE_INFINITY = -INFINITY;
        constexpr static double POSITIVE_INFINITY = INFINITY;
    };
}

#endif //JS_CMP_STATICMETHODSNUMBER_HPP
