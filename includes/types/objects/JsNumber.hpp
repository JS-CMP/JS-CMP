#ifndef JS_CMP_JSNUMBER_HPP
#define JS_CMP_JSNUMBER_HPP

#include "internals/Object.hpp"

namespace JS {
class Number : public JS::InternalObject {
    public:
        Number();
        explicit Number(const JS::Any& value);
        explicit Number(const std::unordered_map<std::string, JS::Attribute>& properties);

        ~Number() override = default;

        static JS::Any toString(const std::vector<JS::Any>& args);
        static JS::Any toLocaleString(const std::vector<JS::Any>& args);
        static JS::Any valueOf(const std::vector<JS::Any>& args);
        static JS::Any toFixed(const std::vector<JS::Any>& args);
        static JS::Any toExponential(const std::vector<JS::Any>& args);
        static JS::Any toPrecision(const std::vector<JS::Any>& args);

        // const variable
        constexpr static double MAX_VALUE = 1.7976931348623157e308;
        constexpr static double MIN_VALUE = 5e-324;
        constexpr static double NaN = NAN;
        constexpr static double NEGATIVE_INFINITY = -INFINITY;
        constexpr static double POSITIVE_INFINITY = INFINITY;

        static std::shared_ptr<JS::InternalObject> &getPrototypeProperties();
};
}


#endif //JS_CMP_JSNUMBER_HPP
