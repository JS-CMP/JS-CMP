#include "utils/Convert.hpp"

#include <types/JsAny.hpp>
#include <types/objects/JsFunction.hpp>

JS::Any& JS::Any::operator[](const std::string& key) const {
    if (this->value.index() == OBJECT) {
        return std::get<std::shared_ptr<JS::Object>>(this->value)->operator[](key);
    }
    throw std::runtime_error("Value is not an object");
}

JS::Any& JS::Any::operator[](size_t index) const {
    if (this->value.index() == OBJECT) {
        return std::get<std::shared_ptr<JS::Object>>(this->value)->operator[](index);
    }
    throw std::runtime_error("Value is not an object");
}

JS::Any JS::Any::helper(std::vector<JS::Any>& args) const {
    if (value.index() == JS::OBJECT && std::get<std::shared_ptr<JS::Object>>(value)->isCallable()) {
        // TODO: change if function is not the only callable object
        return std::dynamic_pointer_cast<JS::Function>(std::get<std::shared_ptr<JS::Object>>(value))->operator()(args);
    }
    throw std::runtime_error("Value is not a function");
}

namespace JS {
std::ostream& operator<<(std::ostream& os, const Any& any) {
    os << JS::CONVERT::ToString(any);
    return os;
}
} // namespace JS