#include <utils/Convert.hpp>

#include "types/objects/Boolean/JsBoolean.hpp"
#include "types/objects/Boolean/PrototypeProperties.hpp"

namespace JS {
    Boolean::Boolean() : InternalObject({}, BOOL::PrototypeProperties::get(), "Boolean", true) {
        this->primitiveValue = true;
        this->defineOwnProperty("length",JS::DataDescriptor{
                Any(1),
                false,
                false,
                false});
        this->defineOwnProperty("prototype",JS::DataDescriptor{
                Any(BOOL::PrototypeProperties::get()),
                false,
                false,
                false});
    }

    Boolean::Boolean(const JS::Any &value) : InternalObject({}, BOOL::PrototypeProperties::get(), "Boolean", true) {
        bool v = CONVERT::ToBoolean(value);
        this->primitiveValue = v;
        this->defineOwnProperty("length",JS::DataDescriptor{
                Any(1),
                false,
                false,
                false});
        this->defineOwnProperty("prototype",JS::DataDescriptor{
                Any(BOOL::PrototypeProperties::get()),
                false,
                false,
                false});
    }

}