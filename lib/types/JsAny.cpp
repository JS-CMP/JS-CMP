#include "utils/Convert.hpp"

#include <types/JsAny.hpp>
#include <types/objects/JsObject.hpp>
#include <utils/Compare.hpp>

JS::Value JS::Any::getValue() const {
    return this->value;
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