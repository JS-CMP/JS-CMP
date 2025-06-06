#include "internals/PropertyProxy.hpp"
#include "types/JsAny.hpp"

#include <utils/Compare.hpp>

namespace JS::CONVERT {
JS::Any ToPrimitive(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.1
    if (JS::COMPARE::Type(any, JS::OBJECT)) {
        return any[u"defaultValue"]();
    }
    return any;
}
} // namespace JS::CONVERT