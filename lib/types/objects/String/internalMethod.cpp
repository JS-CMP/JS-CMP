#include "internals/Object.hpp"
#include "types/objects/JsString.hpp"
#include "utils/Convert.hpp"

std::u16string JS::String::getContent() const {
    return JS::CONVERT::ToString(this->primitiveValue);
}
