#include <internals/Operator.hpp>
#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Operator::operator bool() {
    return JS::CONVERT::ToBoolean(*this);
}
