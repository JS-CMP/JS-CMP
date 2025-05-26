#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any::operator bool() { return JS::CONVERT::ToBoolean(*this); }
