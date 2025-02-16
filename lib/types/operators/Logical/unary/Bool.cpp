#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any::operator bool() const { return JS::CONVERT::ToBoolean(*this); }
