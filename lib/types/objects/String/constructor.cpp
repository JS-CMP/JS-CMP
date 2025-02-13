#include "types/objects/JsString.hpp"
#include "types/objects/JsFunction.hpp"

namespace JS {
    String::String() : JS::InternalObject({}, getPrototypeProperties(), "String", true) {
        this->primitiveValue = Rope("");
        this->defineOwnProperty("length",JS::DataDescriptor{
            JS::Any(0),
            false,
            false,
            false});
        this->defineOwnProperty("prototype",JS::DataDescriptor{
                JS::Any(getPrototypeProperties()),
                false,
                false,
                false});
    }

    String::String(const JS::Any& value) : JS::InternalObject({}, getPrototypeProperties(), "String", true) {
        Rope v = Rope(JS::CONVERT::ToString(value));
        this->primitiveValue = v;
        this->defineOwnProperty("length",JS::DataDescriptor{
            JS::Any(int(v.length())),
            false,
            false,
            false});
        this->defineOwnProperty("prototype",JS::DataDescriptor{
            JS::Any(getPrototypeProperties()),
            false,
            false,
            false});
    }

    String::String(const std::unordered_map<std::string, JS::Any>& properties) : InternalObject({}, getPrototypeProperties(), "Boolean", true) {
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
            JS::Any(getPrototypeProperties()),
            false,
            false,
            false,
        }));
    }
}