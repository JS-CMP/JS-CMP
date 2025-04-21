#include "types/objects/Function/JsFunctionBinded.hpp"

namespace JS {
bool FunctionBinded::hasInstance(const JS::Any& value) const { return targetFunction->hasInstance(value); }
} // namespace JS