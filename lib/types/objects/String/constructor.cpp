#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsString.hpp"
#include "utils/Convert.hpp"

namespace JS {
String::String() : JS::InternalObject({}, getPrototypeProperties(), u"String", true) {
    this->primitiveValue = Rope("");
    this->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(0), false, false, false});
    this->defineOwnProperty(u"prototype", JS::DataDescriptor{JS::Any(getPrototypeProperties()), false, false, false});
}

String::String(const JS::Any& value) : JS::InternalObject({}, getPrototypeProperties(), u"String", true) {
    Rope v = Rope(JS::CONVERT::ToString(value));
    this->primitiveValue = v;
    this->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(int(v.length())), false, false, false});
    this->defineOwnProperty(u"prototype", JS::DataDescriptor{JS::Any(getPrototypeProperties()), false, false, false});
}

String::String(const std::unordered_map<std::u16string, JS::Any>& properties)
    : InternalObject({}, getPrototypeProperties(), u"String", true) {
    this->primitiveValue = Rope("");
    for (const auto& [key, value] : properties) {
        this->InternalObject::put(key, value);
    }
    this->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(0), false, false, false});
    this->defineOwnProperty(u"prototype", DataDescriptor({
                                              JS::Any(getPrototypeProperties()),
                                              false,
                                              false,
                                              false,
                                          }));
}
} // namespace JS