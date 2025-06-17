#include "types/objects/Function/JsFunctionBinded.hpp"

namespace JS {
bool FunctionBinded::hasInstance(const JS::Any& value) const {
    return targetFunction->hasInstance(value);
}

std::u16string FunctionBinded::getContent() const {
    return u"[Function: ]"; // TODO: add function name
}
} // namespace JS