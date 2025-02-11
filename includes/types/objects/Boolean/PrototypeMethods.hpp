#ifndef JS_CMP_PROTOTYPEMETHODSBOOLEAN_HPP
#define JS_CMP_PROTOTYPEMETHODSBOOLEAN_HPP

#include "types/Types.hpp"

namespace JS::BOOL {
    class PrototypeMethods {
    public:
        static JS::Any toString(const std::vector<JS::Any>& args);
        static JS::Any valueOf(const std::vector<JS::Any>& args);
    };
}


#endif //JS_CMP_PROTOTYPEMETHODSBOOLEAN_HPP
