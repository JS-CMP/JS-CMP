#include "internals/Object.hpp"
#include "types/objects/JsNumber.hpp"
#include "utils/Convert.hpp"

std::u16string JS::Number::getContent() const {
    return JS::CONVERT::ToString(this->primitiveValue);
}

