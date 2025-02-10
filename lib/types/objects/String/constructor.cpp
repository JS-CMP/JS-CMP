#include "types/objects/String/JsString.hpp"
#include "types/objects/JsFunction.hpp"
#include "types/objects/String/PrototypeProperties.hpp"

namespace JS {
    String::String() : JS::InternalObject({}, STR::PrototypeProperties::get(), "String", true) {
        this->defineOwnProperty("length",JS::DataDescriptor{JS::Any(0),
                                                   false,
                                                   false,
                                                   false});
        this->primitiveValue = Rope("");
        this->defineOwnProperty("prototype",JS::DataDescriptor{
                JS::Any(STR::PrototypeProperties::get()),
                false,
                false,
                false});
    }

    String::String(JS::Any value) : JS::InternalObject({}, STR::PrototypeProperties::get(), "String", true) {
        auto v = Rope(JS::CONVERT::ToString(value));
        auto length = JS::Any(int(v.length()));
        this->defineOwnProperty("length",JS::DataDescriptor{ length,false,false,false});
        this->primitiveValue = v;
        this->defineOwnProperty("prototype",JS::DataDescriptor{
            JS::Any(STR::PrototypeProperties::get()),
            false,
            false,
            false});
    }
}