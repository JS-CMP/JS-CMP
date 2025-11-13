#include <internals/Operator.hpp>
#include <types/JsAny.hpp>

JS::Any JS::Operator::operator!=(const JS::Operator& other) const {
    return !(*this == other);
};