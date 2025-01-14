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

JS::PropertyProxy  JS::Any::operator[](size_t index) const {
    if (this->value.index() == OBJECT) {
        return std::get<std::shared_ptr<JS::InternalObject>>(this->value)->operator[](index);
    }
    throw std::runtime_error("Value is not an object");
}

JS::Any JS::Any::call(const std::vector<JS::Any>& args) const {
    std::cerr << " in JS::Any call" << std::endl;
    std::cerr << this << std::endl;
    if (value.index() == JS::OBJECT && std::get<std::shared_ptr<JS::InternalObject>>(value)->isCallable()) {
        std::cerr << "calling function" << std::endl;
        // TODO: change if function is not the only callable object
        // reinterpret_cast<JS::Function*>(std::get<std::shared_ptr<JS::InternalObject>>(value).get())->call(args);
        return reinterpret_cast<JS::Function*>(std::get<std::shared_ptr<JS::InternalObject>>(value).get())->operator()(args);
    }
    throw std::runtime_error("Value is not a function");
}

namespace JS {
std::ostream& operator<<(std::ostream& os, const Any& any) {
    os << JS::CONVERT::ToString(any);
    return os;
}
} // namespace JS