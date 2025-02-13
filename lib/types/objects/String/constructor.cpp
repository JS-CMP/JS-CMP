#include "types/objects/String/JsString.hpp"
#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/String/PrototypeProperties.hpp"

namespace JS {
    String::String() : JS::InternalObject({}, STR::PrototypeProperties::get(), "String", true) {
        this->primitiveValue = Rope("");
        this->defineOwnProperty("length",JS::DataDescriptor{
            JS::Any(0),
            false,
            false,
            false});
        this->defineOwnProperty("prototype",JS::DataDescriptor{
                JS::Any(STR::PrototypeProperties::get()),
                false,
                false,
                false});
    }

    String::String(const JS::Any& value) : JS::InternalObject({}, STR::PrototypeProperties::get(), "String", true) {
        Rope v = Rope(JS::CONVERT::ToString(value));
        this->primitiveValue = v;
        this->defineOwnProperty("length",JS::DataDescriptor{
            JS::Any(int(v.length())),
            false,
            false,
            false});
        this->defineOwnProperty("prototype",JS::DataDescriptor{
            JS::Any(STR::PrototypeProperties::get()),
            false,
            false,
            false});
    }

    String::String(const std::unordered_map<std::string, JS::Any>& properties) : InternalObject({}, STR::PrototypeProperties::get(), "Boolean", true) {
        this->primitiveValue = Rope("");
        for (const auto& [key, value] : properties) {
            this->InternalObject::put(key, value);
        }
        this->defineOwnProperty("length",JS::DataDescriptor{
            JS::Any(0),
            false,
            false,
            false});
        this->defineOwnProperty("prototype", DataDescriptor({
            JS::Any(STR::PrototypeProperties::get()),
            false,
            false,
            false,
        }));
    }
}