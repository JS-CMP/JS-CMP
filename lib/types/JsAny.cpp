#include "utils/Convert.hpp"

#include <types/JsAny.hpp>
#include <types/objects/JsObject.hpp>
#include <utils/Compare.hpp>

JS::Value JS::Any::getValue() const { return this->value; }

const char *JS::Any::what() const noexcept {
    thread_local std::string utf8_buffer;

    if (this->value.index() != JS::OBJECT) {
        utf8_buffer = CONVERT::ToUtf8(u"Uncaught " + CONVERT::ToString(*this));
        return utf8_buffer.c_str();
    }

    auto obj = CONVERT::ToObject(*this);
    if (obj->class_name != u"Error") {
        utf8_buffer = CONVERT::ToUtf8(u"Uncaught " + obj->getContent());
    } else {
        JS::Any temp = obj->get(u"message");
        JS::Any name = obj->get(u"name");
        JS::Any message = COMPARE::Type(temp, JS::UNDEFINED) ? JS::Any("") : temp;

        utf8_buffer = CONVERT::ToUtf8(u"Uncaught " + CONVERT::ToString(name) +
                                      (message != JS::Any("") ? u": " : u"") +
                                      CONVERT::ToString(message));
    }
    return utf8_buffer.c_str();
}


namespace JS {
std::ostream& operator<<(std::ostream& os, const Any& any) {
    os << JS::CONVERT::ToUtf8(JS::CONVERT::ToString(any));
    return os;
}

// TODO: remove and rework assert when custom operator merged
bool JS::Any::strictEq(const JS::Any& other) const {
    // TODO: handle identity
    std::cout << value.index() << " " << other.value.index() << '\n';
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