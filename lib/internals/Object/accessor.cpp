#include "internals/Object.hpp"
#include "internals/PropertyProxy.hpp"
namespace JS {

JS::PropertyProxy InternalObject::operator[](const std::u16string& key) {
    return JS::PropertyProxy(shared_from_this(), key);
}
} // namespace JS