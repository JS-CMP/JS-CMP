#include "internals/PropertyProxy.hpp"
#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsObject.hpp"

#include <utility>

namespace JS {

Object::Object() : JS::InternalObject({}, getPrototypeProperties(), u"Object", true) {
    this->InternalObject::defineOwnProperty(u"prototype", DataDescriptor({
                                                             JS::Any(getPrototypeProperties()),
                                                             false,
                                                             false,
                                                             false,
                                                         }));
}

Object::Object(const std::unordered_map<std::u16string, JS::Any>& properties)
    : JS::InternalObject({}, getPrototypeProperties(), u"Object", true) {
    for (const auto& [key, value] : properties) {
        this->InternalObject::put(key, value);
    }
    this->InternalObject::defineOwnProperty(u"prototype", DataDescriptor({
                                                             JS::Any(getPrototypeProperties()),
                                                             false,
                                                             false,
                                                             false,
                                                         }));
}

Object::Object(const Attribute& attribute) : JS::InternalObject(attribute) {
    this->InternalObject::defineOwnProperty(u"prototype", DataDescriptor({
                                                             JS::Any(getPrototypeProperties()),
                                                             false,
                                                             false,
                                                             false,
                                                         }));
}

Object::Object(const InternalObject&& internalObject) : JS::InternalObject(internalObject) {}
} // namespace JS