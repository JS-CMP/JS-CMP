#include "internals/Object.hpp"
#include "utils/Convert.hpp"
namespace JS {

JS::PropertyProxy  InternalObject::operator[](const std::string& key) {
    return {*this, key};
}
JS::PropertyProxy  InternalObject::operator[](size_t index) {
    return (*this)[std::to_string(index)];
}

} // namespace JS