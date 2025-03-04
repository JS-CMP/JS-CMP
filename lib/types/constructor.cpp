#include "types/objects/JsObject.hpp"

#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any::Any(const std::shared_ptr<JS::InternalObject> v) { value = v; }

JS::Any::Any(const JS::InternalObject& v) {
    std::shared_ptr<JS::InternalObject> obj = std::make_shared<JS::InternalObject>(v);
    value = std::move(obj);
}

JS::Any::Any(const JS::Any& v) { value = v.value; }

JS::Any::Any(const JS::Any&& v) noexcept { value = v.value; }

JS::Any& JS::Any::operator=(JS::Any&& other) noexcept {
    value = std::move(other.value);
    return *this;
}

JS::Any& JS::Any::operator=(const JS::Any& other) = default;

JS::Any::operator bool() const { return JS::CONVERT::ToBoolean(*this); }