#ifndef JS_CMP_PROTOTYPEPROPERTIESOBJECT_HPP
#define JS_CMP_PROTOTYPEPROPERTIESOBJECT_HPP

#include <memory>
#include <unordered_map>

#include "types/Types.hpp"

namespace JS::OBJ {
    class PrototypeProperties {
    public:
        static std::shared_ptr<JS::InternalObject>& get();
    };
}

#endif //JS_CMP_PROTOTYPEPROPERTIESOBJECT_HPP
