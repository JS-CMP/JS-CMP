#include "utils/Convert.hpp"

#include <types/JsAny.hpp>
#include <types/objects/JsObject.hpp>
#include <utils/Compare.hpp>

JS::Value JS::Any::getValue() const {
    return this->value;
}

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

JS::Any& JS::Any::get() {
    return *this;
}
JS::Any JS::Any::get() const {
    return *this;
}

void JS::Any::setValue(const JS::Value& value) {
    this->value = value;
}

void JS::Any::set(const JS::Any& value) {
    this->value = value.value;
}