#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsString.hpp"
#include "utils/Convert.hpp"

namespace JS {

String::String(const JS::Any& value) : JS::InternalObject({}, getPrototypeProperties(), STRING_CLASS_NAME, true) {
    Rope v = JS::CONVERT::ToRope(value);
    this->primitiveValue = v;
    this->call_function = &JS::String::internal_call;
    this->construct = &JS::String::internal_constructor;
    this->InternalObject::defineOwnProperty(u"length",
                            JS::DataDescriptor{JS::Any(static_cast<uint32_t>(v.length())), false, false, false});
}

} // namespace JS