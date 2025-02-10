#ifndef JS_CMP_PROTOTYPEPROPERTIESOBJECT_HPP
#define JS_CMP_PROTOTYPEPROPERTIESOBJECT_HPP

#include <memory>
#include <unordered_map>

#include "types/objects/JsFunction.hpp"
#include "types/objects/Object/PrototypeMethods.hpp"

namespace JS::OBJ {
    class PrototypeProperties {
    public:
        static std::shared_ptr<JS::InternalObject>& get() {
            static std::unordered_map<std::string, JS::Any> properties_prototype = {
                    {"toString", JS::Any(std::make_shared<JS::Function>(JS::OBJ::PrototypeMethods::toString))},
                    {"toLocaleString", JS::Any(std::make_shared<JS::Function>(JS::OBJ::PrototypeMethods::toLocaleString))},
                    {"valueOf", JS::Any(std::make_shared<JS::Function>(JS::OBJ::PrototypeMethods::valueOf))},
                    {"hasOwnProperty", JS::Any(std::make_shared<JS::Function>(JS::OBJ::PrototypeMethods::hasOwnProperty))},
                    {"isPrototypeOf", JS::Any(std::make_shared<JS::Function>(JS::OBJ::PrototypeMethods::isPrototypeOf))},
                    {"propertyIsEnumerable", JS::Any(std::make_shared<JS::Function>(JS::OBJ::PrototypeMethods::propertyIsEnumerable))},
            };
            static std::shared_ptr<JS::InternalObject> instance =
                    std::make_shared<JS::InternalObject>(properties_prototype);
            return instance;
        }
    };

}

#endif //JS_CMP_PROTOTYPEPROPERTIESOBJECT_HPP
