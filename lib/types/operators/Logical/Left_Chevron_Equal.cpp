#include <internals/Operator.hpp>
#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Operator::operator<=(const JS::Operator& other) const {
    return (*this < other) || (*this == other);
}