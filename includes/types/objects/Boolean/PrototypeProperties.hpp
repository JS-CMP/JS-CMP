#ifndef JS_CMP_PROTOTYPEPROPERTIESBOOLEAN_HPP
#define JS_CMP_PROTOTYPEPROPERTIESBOOLEAN_HPP

#include "internals/Object.hpp"

namespace JS::BOOL {
    class PrototypeProperties {
    public:
        static std::shared_ptr<JS::InternalObject> &get();
    };
}


#endif //JS_CMP_PROTOTYPEPROPERTIESBOOLEAN_HPP
