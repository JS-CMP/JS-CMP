#include "internals/Object.hpp"
#include "types/objects/JsBoolean.hpp"
#include "utils/Convert.hpp"

std::u16string JS::Boolean::getContent() const {
    return JS::CONVERT::ToString(this->primitiveValue);
}
