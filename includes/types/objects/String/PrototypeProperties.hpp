#ifndef JS_CMP_PROTOTYPEPROPERTIESSTRING_HPP
#define JS_CMP_PROTOTYPEPROPERTIESSTRING_HPP

#include <memory>
#include <unordered_map>

#include "types/Types.hpp"

namespace JS::STR {
    class PrototypeProperties {
    public:
        static std::shared_ptr<JS::InternalObject> &get();
    };
};


#endif //JS_CMP_PROTOTYPEPROPERTIESTRING_HPP
