#include "internals/PropertyProxy.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

#include <types/JsAny.hpp>
#include <types/objects/Function/JsFunction.hpp>

template <typename T>
JS::PropertyProxy JS::Any::operator[](T key) const {
    JS::COMPARE::CheckObjectCoercible(*this);
    auto value = JS::CONVERT::ToObject(*this);
    return JS::PropertyProxy(value, JS::CONVERT::ToString(key));
}
template JS::PropertyProxy JS::Any::operator[](int) const;
template JS::PropertyProxy JS::Any::operator[](unsigned int) const;
template JS::PropertyProxy JS::Any::operator[](double) const;
template JS::PropertyProxy JS::Any::operator[](bool) const;
template JS::PropertyProxy JS::Any::operator[](const char*) const;
template JS::PropertyProxy JS::Any::operator[](const std::string&) const;
template JS::PropertyProxy JS::Any::operator[](const JS::Null&) const;
template JS::PropertyProxy JS::Any::operator[](const JS::Undefined&) const;
template JS::PropertyProxy JS::Any::operator[](const JS::Any&) const;
template JS::PropertyProxy JS::Any::operator[](const JS::PropertyProxy&) const;
template JS::PropertyProxy JS::Any::operator[](JS::Any) const;
template JS::PropertyProxy JS::Any::operator[](JS::PropertyProxy) const;

JS::Any JS::Any::call(const JS::Any& args) const {
    if (value.index() == JS::OBJECT && std::get<std::shared_ptr<JS::InternalObject>>(value)->isCallable()) {
        return std::get<std::shared_ptr<JS::InternalObject>>(value)->call_function(
            JS::Any(JS::Undefined{}), args); // TODO fix this to pass the correct this aka global object
    }
    throw std::runtime_error("Value is not a function");
}