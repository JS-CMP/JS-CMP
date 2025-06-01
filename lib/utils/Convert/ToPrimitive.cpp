#include "internals/PropertyProxy.hpp"
#include "types/JsAny.hpp"

#include <internals/Object.hpp>
#include <utils/Compare.hpp>

namespace JS::CONVERT {
JS::Any ToPrimitive(const JS::Any& any,
                    const JS::Types& hint = JS::NUMBER) { // https://262.ecma-international.org/5.1/#sec-9.1
    if (JS::COMPARE::Type(any, JS::OBJECT)) {
        return std::get<std::shared_ptr<JS::InternalObject>>(any.getValue())->defaultValue(hint);
    }
    return any;
}
} // namespace JS::CONVERT