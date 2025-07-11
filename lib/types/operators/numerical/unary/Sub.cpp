#include <internals/Operator.hpp>
#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Operator::operator-() const {
    double value = -JS::CONVERT::ToNumber(*this);
    return JS::Any(value == -0.0 ? 0.0 : value);
}