#include "internals/PropertyProxy.hpp"
#include "utils/Convert.hpp"

#include <types/JsAny.hpp>
#include <types/objects/JsFunction.hpp>

JS::PropertyProxy JS::Any::operator[](const std::string& key) const {
    if (this->value.index() == OBJECT) {
        return std::get<std::shared_ptr<JS::InternalObject>>(this->value)->operator[](key);
    }
    throw std::runtime_error("Value is not an object");
}

JS::PropertyProxy JS::Any::operator[](size_t index) const {
    if (this->value.index() == OBJECT) {
        return std::get<std::shared_ptr<JS::InternalObject>>(this->value)->operator[](index);
    }
    throw std::runtime_error("Value is not an object");
}

JS::Any JS::Any::call(const JS::Any &args) const {
    if (value.index() == JS::OBJECT && std::get<std::shared_ptr<JS::InternalObject>>(value)->isCallable()) {
        return std::get<std::shared_ptr<JS::InternalObject>>(value)->call(JS::Any(JS::Undefined{}), args); // TODO fix this to pass the correct this aka global object
    }
    throw std::runtime_error("Value is not a function");
}

namespace JS {
std::ostream& operator<<(std::ostream& os, const Any& any) {
    os << JS::CONVERT::ToString(any);
    return os;
}
} // namespace JS