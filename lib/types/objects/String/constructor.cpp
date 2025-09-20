#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsString.hpp"
#include "utils/Convert.hpp"

namespace JS {
String::String() : JS::InternalObject({}, getPrototypeProperties(), STRING_CLASS_NAME, true) {
    this->primitiveValue = Rope("");
    this->call_function = &JS::String::internal_call;
    this->construct = &JS::String::internal_constructor;

    this->InternalObject::defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(0), false, false, false});
}

String::String(const JS::Any& value) : JS::InternalObject({}, getPrototypeProperties(), STRING_CLASS_NAME, true) {
    Rope v = JS::CONVERT::ToRope(value);
    this->primitiveValue = v;
    this->call_function = &JS::String::internal_call;
    this->construct = &JS::String::internal_constructor;
    this->InternalObject::defineOwnProperty(u"length",
                            JS::DataDescriptor{JS::Any(static_cast<uint32_t>(v.length())), false, false, false});
}

String::String(const std::unordered_map<std::u16string, JS::Any>& properties)
    : InternalObject({}, getPrototypeProperties(), STRING_CLASS_NAME, true) {
    this->primitiveValue = Rope("");
    this->call_function = &JS::String::internal_call;
    this->construct = &JS::String::internal_constructor;

    for (const auto& [key, value] : properties) {
        this->InternalObject::put(key, value);
    }
    this->InternalObject::defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(0), false, false, false});
}
String::String(const JS::Properties& properties)
    : InternalObject(properties, JS::Function::getPrototypeProperties(), STRING_CLASS_NAME, true) {
    this->primitiveValue = Rope("");
    this->call_function = &JS::String::internal_call;
    this->construct = &JS::String::internal_constructor;
    this->InternalObject::defineOwnProperty(u"prototype", DataDescriptor({JS::Any(getPrototypeProperties()), false, false, false}));
}
} // namespace JS