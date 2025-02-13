#include "types/objects/Number/PrototypeProperties.hpp"
#include "types/objects/Number/JsNumber.hpp"
#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/Object/PrototypeProperties.hpp"

namespace JS::NUM {
    std::shared_ptr<JS::InternalObject> &PrototypeProperties::get() {
        static std::unordered_map<std::string, JS::Attribute> properties_prototype = {
                {"toString", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toString)), true, true, true}},
                {"toLocaleString", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toLocaleString)), true, true, true}},
                {"valueOf", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::valueOf)), true, true, true}},
                {"toFixed", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toFixed)), true, true, true}},
                {"toExponential", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toExponential)), true, true, true}},
                {"toPrecision", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Number::toPrecision)), true, true, true}},
        };
        static std::shared_ptr<JS::InternalObject> instance =
                std::make_shared<JS::InternalObject>(properties_prototype, JS::OBJ::PrototypeProperties::get(), "Number", true);

        return instance;
    }
}