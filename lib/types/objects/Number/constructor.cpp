#include "types/objects/JsNumber.hpp"
#include "utils/Convert.hpp"

namespace JS {
Number::Number() : JS::InternalObject({}, getPrototypeProperties(), u"Number", true) {
    this->primitiveValue = 0.0;
    this->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(1), false, false, false});
    this->defineOwnProperty(u"prototype", JS::DataDescriptor{JS::Any(getPrototypeProperties()), false, false, false});
}

Number::Number(const JS::Any& value) : JS::InternalObject({}, getPrototypeProperties(), u"Number", true) {
    double v = JS::CONVERT::ToNumber(value);
    this->primitiveValue = v;
    this->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(1), false, false, false});
    this->defineOwnProperty(u"prototype", JS::DataDescriptor{JS::Any(getPrototypeProperties()), false, false, false});
}

Number::Number(const std::unordered_map<std::u16string, JS::Attribute>& properties)
    : InternalObject({}, getPrototypeProperties(), u"Number", true) {
    this->primitiveValue = 0.0;
    for (const auto& [key, value] : properties) {
        this->InternalObject::defineOwnProperty(key, value);
    }
    this->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(1), false, false, false});
    this->defineOwnProperty(u"prototype", DataDescriptor({
                                              JS::Any(getPrototypeProperties()),
                                              false,
                                              false,
                                              false,
                                          }));
}
} // namespace JS