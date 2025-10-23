#include "types/objects/JsObject.hpp"

namespace JS::CONVERT {
JS::Any FromPropertyDescriptor(const AccessorDescriptor& desc) { // https://262.ecma-international.org/5.1/#sec-8.10.4
    if (desc.get == nullptr && desc.set == nullptr) {
        return {};
    }
    std::shared_ptr<JS::Object> obj = JS::InternalObject::create<JS::Object>();
    obj->put(u"get", desc.get == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(desc.get));
    obj->put(u"set", desc.set == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(desc.set));
    obj->put(u"enumerable", JS::Any(desc.enumerable));
    obj->put(u"configurable", JS::Any(desc.configurable));
    return JS::Any(obj);
}

JS::Any FromPropertyDescriptor(const JS::Attribute& desc) { // https://262.ecma-international.org/5.1/#sec-8.10.4
    switch (desc.index()) {
        case JS::DATA_DESCRIPTOR: {
            std::shared_ptr<JS::Object> obj = JS::InternalObject::create<JS::Object>();
            JS::DataDescriptor dataDesc = std::get<JS::DataDescriptor>(desc);
            obj->put(u"value", dataDesc.value);
            obj->put(u"writable", JS::Any(dataDesc.writable));
            obj->put(u"enumerable", JS::Any(dataDesc.enumerable));
            obj->put(u"configurable", JS::Any(dataDesc.configurable));
            return JS::Any(obj);
        }
        case JS::ACCESSOR_DESCRIPTOR: {
            JS::AccessorDescriptor accessorDesc = std::get<JS::AccessorDescriptor>(desc);
            if (accessorDesc.get == nullptr && accessorDesc.set == nullptr) {
                return {};
            }
            std::shared_ptr<JS::Object> obj = JS::InternalObject::create<JS::Object>();
            obj->put(u"get", accessorDesc.get == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(accessorDesc.get));
            obj->put(u"set", accessorDesc.set == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(accessorDesc.set));
            obj->put(u"enumerable", JS::Any(accessorDesc.enumerable));
            obj->put(u"configurable", JS::Any(accessorDesc.configurable));
            return JS::Any(obj);
        }
        default:
            return {};
    }
}

JS::Any FromPropertyDescriptor(const JS::DataDescriptor& desc) { // https://262.ecma-international.org/5.1/#sec-8.10.4
    std::shared_ptr<JS::Object> obj = JS::InternalObject::create<JS::Object>();
    obj->put(u"value", desc.value);
    obj->put(u"writable", JS::Any(desc.writable));
    obj->put(u"enumerable", JS::Any(desc.enumerable));
    obj->put(u"configurable", JS::Any(desc.configurable));
    return JS::Any(obj);
}
} // namespace JS::CONVERT