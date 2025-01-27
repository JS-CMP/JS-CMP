#include "../../../../includes/types/JsAny.hpp"
#include "../../../../includes/utils/Convert.hpp"

JS::Any JS::Any::operator!() const { return JS::Any(!JS::CONVERT::ToBoolean(*this)); }