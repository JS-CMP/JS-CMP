#include <internals/Operator.hpp>
#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Operator::operator--() {
    this->setValue(JS::CONVERT::ToNumber(*this) - 1);
    return static_cast<const JS::Operator&>(*this).get();
}

JS::Any JS::Operator::operator--(int) {
    JS::Any tmp = static_cast<const JS::Operator&>(*this).get();
    this->setValue(JS::CONVERT::ToNumber(*this) - 1);
    return tmp;
}