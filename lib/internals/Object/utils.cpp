#include "internals/Object.hpp"

namespace JS {
bool InternalObject::isCallable() const {
    return call != nullptr;
}
} // namespace JS