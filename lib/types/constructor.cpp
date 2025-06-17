#include "types/objects/JsObject.hpp"

#include <types/JsAny.hpp>
#include <utils/Convert.hpp>
#include <types/objects/JsNumber.hpp>
#include <types/objects/JsBoolean.hpp>
#include <types/objects/JsString.hpp>
#include <types/objects/Function/JsFunction.hpp>

JS::Any::Any(std::shared_ptr<JS::InternalObject> v) {
    value = v;
}

JS::Any::Any(const JS::InternalObject& v) {
    std::shared_ptr<JS::InternalObject> obj = std::make_shared<JS::InternalObject>(v);
    value = std::move(obj);
}

JS::Any::Any(const JS::Object& v) {
    std::shared_ptr<JS::InternalObject> obj = std::make_shared<JS::Object>(v);
    value = std::move(obj);
}

JS::Any::Any(const JS::Function& v) {
    std::shared_ptr<JS::InternalObject> obj = std::make_shared<JS::Function>(v);
    value = std::move(obj);
}

JS::Any::Any(const JS::Number& v) {
    std::shared_ptr<JS::InternalObject> obj = std::make_shared<JS::Number>(v);
    value = std::move(obj);
}

JS::Any::Any(const JS::Boolean& v) {
    std::shared_ptr<JS::InternalObject> obj = std::make_shared<JS::Boolean>(v);
    value = std::move(obj);
}

JS::Any::Any(const JS::String& v) {
    std::shared_ptr<JS::InternalObject> obj = std::make_shared<JS::String>(v);
    value = std::move(obj);
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
