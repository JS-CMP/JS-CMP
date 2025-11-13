#include <internals/Operator.hpp>
#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Operator::operator!() const {
    return JS::Any(!JS::CONVERT::ToBoolean(this->get()));
}