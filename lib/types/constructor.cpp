#include "internals/Object.hpp"

#include <types/JsAny.hpp>

JS::Any::Any(std::shared_ptr<JS::InternalObject> v) {
    value = v;
}

JS::Any::Any(const JS::Any& v) {
    value = v.value;
}

JS::Any::Any(const JS::Any&& v) noexcept {
    value = v.value;
}

JS::Any& JS::Any::operator=(JS::Any&& other) noexcept {
    value = std::move(other.value);
    return *this;
}

JS::Any& JS::Any::operator=(const JS::Any& other) = default;
