#ifndef JS_CMP_PROTOTYPEMETHODSNUMBER_HPP
#define JS_CMP_PROTOTYPEMETHODSNUMBER_HPP

#include "types/Types.hpp"

namespace JS::NUM {
    class PrototypeMethods {
    public:
        static JS::Any toString(const std::vector<JS::Any>& args);
        static JS::Any toLocaleString(const std::vector<JS::Any>& args);
        static JS::Any valueOf(const std::vector<JS::Any>& args);
        static JS::Any toFixed(const std::vector<JS::Any>& args);
        static JS::Any toExponential(const std::vector<JS::Any>& args);
        static JS::Any toPrecision(const std::vector<JS::Any>& args);
    };
}


#endif //JS_CMP_PROTOTYPEMETHODSNUMBER_HPP
