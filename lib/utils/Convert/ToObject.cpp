#include "types/JsAny.hpp"
#include "types/objects/JsBoolean.hpp"
#include "types/objects/JsNumber.hpp"
#include "types/objects/JsString.hpp"
#include "utils/Compare.hpp"

namespace JS::CONVERT {



std::shared_ptr<JS::InternalObject> ToObject(const JS::Operator& any) { // https://262.ecma-international.org/5.1/#sec-9.9
    if (JS::COMPARE::Type(any, UNDEFINED) || JS::COMPARE::Type(any, NULL_TYPE)) {
        throw std::invalid_argument("Cannot convert undefined or null to object");
    }
    switch (any.getValue().index()) {
        case STRING:
            return std::make_shared<JS::String>(any.get());
        case BOOLEAN:
            return std::make_shared<JS::Boolean>(any.get());
        case NUMBER:
            return std::make_shared<JS::Number>(any.get());
        case OBJECT:
            return std::get<std::shared_ptr<JS::InternalObject>>(any.getValue());
        default:
            throw std::invalid_argument("Cannot convert value to object");
    }
}
} // namespace JS::CONVERT