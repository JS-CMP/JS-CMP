#include "utils/Convert.hpp"

#include <types/JsAny.hpp>
#include <types/objects/JsObject.hpp>
#include <utils/Compare.hpp>

JS::Value JS::Any::getValue() const { return this->value; }

const char *JS::Any::what() const noexcept {
    if (this->value.index() != JS::OBJECT) { // TODO: cast is property proxy shenanigan, fix
        return ("Uncaught " + CONVERT::ToString(this)).c_str();
    }
    auto obj = CONVERT::ToObject(JS::Any(this));
    // if (obj.class_name != "Error") {
    //     return ("Uncaught " + CONVERT::ToString(this)).c_str();
    // }

    JS::Any temp = obj["message"];// bad varian access because toobject
    JS::Any name = obj["name"];
    std::cout << "here" << std::endl;
    JS::Any message = COMPARE::Type(temp, JS::UNDEFINED) ? JS::Any("") : temp; // TODO: find a solution to do temp == undefined
    return CONVERT::ToString("Uncaught " + name + ": " + message).c_str();
}


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