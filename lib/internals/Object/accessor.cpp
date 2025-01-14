#include "internals/Object.hpp"
#include "internals/PropertyProxy.hpp"
namespace JS {

JS::PropertyProxy  InternalObject::operator[](const std::string& key) {
    return JS::PropertyProxy(std::make_shared<JS::InternalObject>(*this), key);
}
JS::PropertyProxy  InternalObject::operator[](size_t index) {
    return (*this)[std::to_string(index)];
}

} // namespace JS