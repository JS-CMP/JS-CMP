#ifndef JS_CMP_PROTOTYPEPROPERTIES_HPP
#define JS_CMP_PROTOTYPEPROPERTIES_HPP

#include "internals/Object.hpp"

namespace JS::NUM {
    class PrototypeProperties {
    public:
        static std::shared_ptr<JS::InternalObject> &get();
    };
}


#endif //JS_CMP_PROTOTYPEPROPERTIES_HPP
