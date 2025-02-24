#include "types/JsAny.hpp"

#include <utils/Compare.hpp>

namespace JS::CONVERT {
JS::Any ToPrimitive(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.1
    if (JS::COMPARE::Type(any, JS::OBJECT)) {
        return JS::Any(std::get<std::shared_ptr<JS::InternalObject>>(any.getValue())); // TODO
    }
    return any;
}
} // namespace JS::CONVERT