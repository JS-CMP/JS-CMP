#include "types/JsAny.hpp"
#include "types/objects/JsNumber.hpp"
#include "types/objects/JsString.hpp"
#include "types/objects/JsBoolean.hpp"

namespace JS::CONVERT {

std::shared_ptr<JS::InternalObject> ToObject(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.9
    if (any.getValue().index() == JS::UNDEFINED || any.getValue().index() == JS::NULL_TYPE) {
        throw std::invalid_argument("Cannot convert undefined or null to object");
    }
    switch (any.getValue().index()) {
        case STRING:
            return std::make_shared<JS::String>(any);
        case BOOLEAN:
            return std::make_shared<JS::Boolean>(any);
        case NUMBER:
            return std::make_shared<JS::Number>(any);
        case OBJECT:
            return std::get<std::shared_ptr<JS::InternalObject>>(any.getValue());
        default:
            throw std::invalid_argument("Cannot convert value to object");
    }
}
} // namespace JS::CONVERT