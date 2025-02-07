#ifndef JS_CMP_PROTO_HPP
#define JS_CMP_PROTO_HPP

#include "types/Types.hpp"
#include "types/objects/JsFunction.hpp"
#include <memory>
#include <unordered_map>

namespace JS {
    class Prototype {
    public:
        static std::shared_ptr<JS::InternalObject>& get() {
            static std::unordered_map<std::string, JS::Any> properties_prototype = {
                    {"toString", JS::Any(std::make_shared<JS::Function>(Object::toString))},
                    {"toLocaleString", JS::Any(std::make_shared<JS::Function>(Object::toLocaleString))},
                    {"valueOf", JS::Any(std::make_shared<JS::Function>(Object::valueOf))},
                    {"hasOwnProperty", JS::Any(std::make_shared<JS::Function>(Object::hasOwnProperty))},
                    {"isPrototypeOf", JS::Any(std::make_shared<JS::Function>(Object::isPrototypeOf))},
                    {"propertyIsEnumerable", JS::Any(std::make_shared<JS::Function>(Object::propertyIsEnumerable))},
            };
            static std::shared_ptr<JS::InternalObject> instance =
                    std::make_shared<JS::InternalObject>(properties_prototype);
            return instance;
        }
    };

    // Access using JS::Prototype::get()
}

#endif //JS_CMP_PROTO_HPP
