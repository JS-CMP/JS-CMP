#include "internals/Object.hpp"
#include "types/objects/JsArray.hpp"
#include "utils/Convert.hpp"

std::u16string JS::Array::getContent() const {
    return JS::CONVERT::ArrayToString(shared_from_this());
}
