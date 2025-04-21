#include "utils/Convert.hpp"

#include <types/JsAny.hpp>

JS::Value JS::Any::getValue() const { return this->value; }

namespace JS {
std::ostream& operator<<(std::ostream& os, const Any& any) {
    os << JS::CONVERT::ToString(any);
    return os;
}

// TODO: remove and rework assert when custom operator merged
bool JS::Any::strictEq(const JS::Any& other) const {
    // TODO: handle identity
    std::cout << value.index() << " " << other.value.index() << std::endl;
    if (this->value.index() != other.value.index()) {
        return false;
    }
    switch (this->value.index()) {
        case NUMBER:
            return std::get<double>(this->value) == std::get<double>(other.value);
        case STRING:
            return std::get<Rope>(this->value) == std::get<Rope>(other.value);
        case BOOLEAN:
            return std::get<bool>(this->value) == std::get<bool>(other.value);
        case UNDEFINED:
            return true;
        case NULL_TYPE:
            return true;
        case OBJECT:
            return &std::get<std::shared_ptr<InternalObject>>(this->value) ==
                   &std::get<std::shared_ptr<InternalObject>>(other.value);
        default:
            return false;
    }
}

bool JS::Any::strictNeq(const JS::Any& other) const { return !this->strictEq(other); }
} // namespace JS