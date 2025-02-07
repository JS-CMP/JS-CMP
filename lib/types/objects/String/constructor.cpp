#include "types/objects/String/JsString.hpp"
#include "types/objects/JsFunction.hpp"
#include <types/objects/String/PrototypeProperties.hpp>

namespace JS {
    String::String() : JS::InternalObject({}, PrototypeProperties::get(), "String", true) {
        this->defineOwnProperty("length",JS::DataDescriptor{JS::Any(0),
                                                   false,
                                                   false,
                                                   false});
        this->primitiveValue = Rope("");
    }

    String::String(JS::Any value) : JS::InternalObject({}, PrototypeProperties::get(), "String", true) {
        auto v = Rope(JS::CONVERT::ToString(value));
        auto length = JS::Any(int(v.length()));
        this->defineOwnProperty("length",JS::DataDescriptor{ length,false,false,false});
        this->primitiveValue = v;
    }
}