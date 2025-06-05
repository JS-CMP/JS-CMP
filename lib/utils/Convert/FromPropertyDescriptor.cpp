#include "types/objects/JsObject.hpp"

namespace JS::CONVERT {
JS::Any FromPropertyDescriptor(const AccessorDescriptor& desc) { // https://262.ecma-international.org/5.1/#sec-8.10.4
    if (desc.get == nullptr && desc.set == nullptr) {
        return {};
    }
    JS::Object obj;
    obj.put(u"get", desc.get == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(*desc.get));
    obj.put(u"set", desc.set == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(*desc.set));
    obj.put(u"enumerable", JS::Any(desc.enumerable));
    obj.put(u"configurable", JS::Any(desc.configurable));
    return JS::Any(obj);
}

JS::Any FromPropertyDescriptor(const JS::Attribute& desc) { // https://262.ecma-international.org/5.1/#sec-8.10.4
    switch (desc.index()) {
        case JS::DATA_DESCRIPTOR:
            return FromPropertyDescriptor(std::get<JS::DataDescriptor>(desc));
        case JS::ACCESSOR_DESCRIPTOR:
            return FromPropertyDescriptor(std::get<JS::AccessorDescriptor>(desc));
        default:
            return {};
    }
}

JS::Any FromPropertyDescriptor(const JS::DataDescriptor& desc) { // https://262.ecma-international.org/5.1/#sec-8.10.4
    JS::Object obj;
    obj.put(u"value", desc.value);
    obj.put(u"writable", JS::Any(desc.writable));
    obj.put(u"enumerable", JS::Any(desc.enumerable));
    obj.put(u"configurable", JS::Any(desc.configurable));
    return JS::Any(obj);
}
} // namespace JS::CONVERT