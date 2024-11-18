#include <types/JsAny.hpp>

JS::Any::Any(const std::shared_ptr<JS::Object> v) {
    v->init();
    value = std::move(v);
}

JS::Any::Any(const JS::Object& v) {
    std::shared_ptr<JS::Object> obj = std::make_shared<JS::Object>(v);
    obj->init();
    value = std::move(obj);
}

JS::Any::Any(const JS::Any& v) {
    value = v.value;
}

JS::Any::Any(const JS::Any&& v) noexcept {
    value = std::move(v.value);
}

JS::Any& JS::Any::operator=(JS::Any&& other)  noexcept {
    value = std::move(other.value);
    return *this;
}

JS::Any& JS::Any::operator=(const JS::Any& other) {
    value = other.value;
    return *this;
}
