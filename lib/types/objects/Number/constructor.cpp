#include "types/objects/Number/JsNumber.hpp"
#include "types/objects/Number/PrototypeProperties.hpp"

#include "utils/Convert.hpp"

namespace JS {
    Number::Number() : JS::InternalObject({}, NUM::PrototypeProperties::get(), "Number", true) {
        this->primitiveValue = 0.0;
        this->defineOwnProperty("length",JS::DataDescriptor{
                JS::Any(1),
                false,
                false,
                false});
        this->defineOwnProperty("prototype",JS::DataDescriptor{
                JS::Any(NUM::PrototypeProperties::get()),
                false,
                false,
                false});
    }

    Number::Number(const JS::Any &value) : JS::InternalObject({}, NUM::PrototypeProperties::get(), "Number", true) {
        double v = JS::CONVERT::ToNumber(value);
        this->primitiveValue = v;
        this->defineOwnProperty("length",JS::DataDescriptor{
                JS::Any(1),
                false,
                false,
                false});
        this->defineOwnProperty("prototype",JS::DataDescriptor{
                JS::Any(NUM::PrototypeProperties::get()),
                false,
                false,
                false});
    }
}