#include <types/objects/Boolean/PrototypeMethods.hpp>
#include <types/objects/Boolean/PrototypeProperties.hpp>

#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/Object/PrototypeProperties.hpp"

namespace JS::BOOL {
    std::shared_ptr<JS::InternalObject> &PrototypeProperties::get() {
        static std::unordered_map<std::string, Attribute> properties_prototype = {
                {"toString", DataDescriptor{Any(std::make_shared<JS::Function>(PrototypeMethods::toString)), true, true, true}},
                {"valueOf", DataDescriptor{Any(std::make_shared<JS::Function>(PrototypeMethods::valueOf)), true, true, true}},
        };
        static std::shared_ptr<InternalObject> instance =
                std::make_shared<InternalObject>(properties_prototype, JS::OBJ::PrototypeProperties::get(), "Number", true);

        return instance;
    }
}