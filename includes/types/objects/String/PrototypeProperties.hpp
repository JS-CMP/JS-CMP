#ifndef JS_CMP_PROTOTYPEPROPERTIES_HPP
#define JS_CMP_PROTOTYPEPROPERTIES_HPP

#include <memory>
#include <unordered_map>

#include "types/objects/JsFunction.hpp"
#include "types/objects/String/JsString.hpp"
#include "types/objects/String/PrototypeMethods.hpp"

namespace JS {
    class PrototypeProperties {
    public:
        static std::shared_ptr<JS::InternalObject>& get() {
            static std::unordered_map<std::string, JS::Any> properties_prototype = {
                    {"toString", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toString))},
                    {"valueOf", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::valueOf))},
                    {"charAt", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::charAt))},
                    {"charCodeAt", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::charCodeAt))},
                    {"concat", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::concat))},
                    {"indexOf", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::indexOf))},
                    {"lastIndexOf", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::lastIndexOf))},
                    {"localeCompare", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::localeCompare))},
                    {"match", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::match))},
                    {"replace", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::replace))},
                    {"search", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::search))},
                    {"slice", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::slice))},
                    {"split", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::split))},
                    {"substring", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::substring))},
                    {"toLowerCase", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toLowerCase))},
                    {"toLocaleLowerCase", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toLocaleLowerCase))},
                    {"toUpperCase", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toUpperCase))},
                    {"toLocaleUpperCase", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::toLocaleUpperCase))},
                    {"trim", JS::Any(std::make_shared<JS::Function>(JS::STR::PrototypeMethods::trim))},
            };
            static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(properties_prototype);
            return instance;
        }
    };

    // Access using JS::Prototype::get()
}

#endif //JS_CMP_PROTOTYPEPROPERTIES_HPP
