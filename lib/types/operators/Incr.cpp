#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any& JS::Any::operator++() {
    this->value = JS::CONVERT::ToNumber(*this) + 1;
    return *this;
}

JS::Any JS::Any::operator++(int) {
    JS::Any tmp = *this;
    this->value = JS::CONVERT::ToNumber(*this) + 1;
    return tmp;
}