#include "types/JsAny.hpp"
namespace JS::CONVERT {

JS::Any ToObject(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.9
    if (any.getValue().index() == JS::OBJECT) { return any; }
    return JS::Any(any); // TODO should return the Object kind like Boolean primitive with value
}
} // namespace JS::CONVERT