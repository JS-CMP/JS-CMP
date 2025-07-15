#include "internals/Object.hpp"
#include "types/objects/JsObject.hpp"
#include "utils/Convert.hpp"
#include "utils/Is.hpp"

std::u16string JS::Object::getContent() const {
    return JS::CONVERT::ObjectToString(shared_from_this());
}
