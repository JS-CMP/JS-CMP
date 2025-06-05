#include <types/JsAny.hpp>

JS::Any JS::Any::operator!=(const JS::Any& other) const {
    return !(*this == other);
};