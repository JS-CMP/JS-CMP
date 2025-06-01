#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Any::operator~() const {
    return JS::Any(~JS::CONVERT::ToInt32(*this));
}