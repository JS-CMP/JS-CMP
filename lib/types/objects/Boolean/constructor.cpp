#include <utils/Convert.hpp>

#include "types/objects/Boolean/JsBoolean.hpp"

namespace JS {
    Boolean::Boolean() : InternalObject({}, getPrototypeProperties(), "Boolean", true) {
        this->primitiveValue = true;
        this->defineOwnProperty("length",JS::DataDescriptor{
                Any(1),
                false,
                false,
                false});
        this->defineOwnProperty("prototype",JS::DataDescriptor{
                Any(getPrototypeProperties()),
                false,
                false,
                false});
    }

    Boolean::Boolean(const JS::Any &value) : InternalObject({}, getPrototypeProperties(), "Boolean", true) {
        bool v = CONVERT::ToBoolean(value);
        this->primitiveValue = v;
        this->defineOwnProperty("length",JS::DataDescriptor{
                Any(1),
                false,
                false,
                false});
        this->defineOwnProperty("prototype",JS::DataDescriptor{
                Any(getPrototypeProperties()),
                false,
                false,
                false});
    }

}