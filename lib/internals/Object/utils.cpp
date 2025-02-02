#include "internals/Object.hpp"

namespace JS {
bool InternalObject::isCallable() const { return call_function != nullptr; }
} // namespace JS