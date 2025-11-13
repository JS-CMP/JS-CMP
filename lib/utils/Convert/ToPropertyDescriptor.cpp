#include "types/objects/JsObject.hpp"

#include <types/objects/Error/JsTypeError.hpp>
#include <utils/Compare.hpp>
#include <utils/Convert.hpp>
#include <utils/Is.hpp>

namespace JS::CONVERT {
JS::Attribute ToPropertyDescriptor(const Any& desc) {
    if (!COMPARE::Type(desc, OBJECT)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Property descriptor must be an object")));
    }
    std::shared_ptr<JS::InternalObject> obj = std::get<std::shared_ptr<JS::InternalObject>>(desc.getValue());
    JS::DataDescriptor data;
    JS::AccessorDescriptor accessor;
    bool get_or_set = false;
    bool value_or_writable = false;
    if (obj->hasProperty(u"enumerable")) {
        data.enumerable = ToBoolean(obj->get(u"value"));
        accessor.enumerable = ToBoolean(obj->get(u"value"));
    }
    if (obj->hasProperty(u"configurable")) {
        data.configurable = ToBoolean(obj->get(u"configurable"));
        accessor.configurable = ToBoolean(obj->get(u"configurable"));
    }
    if ((value_or_writable = value_or_writable || obj->hasProperty(u"value"))) {
        data.value = obj->get(u"value");
    }
    if ((value_or_writable = value_or_writable || obj->hasProperty(u"writable"))) {
        data.writable = ToBoolean(obj->get(u"writable"));
    }
    if ((get_or_set = get_or_set || obj->hasProperty(u"get"))) {
        JS::Any tmp = obj->get(u"get");
        if (COMPARE::Type(tmp, UNDEFINED)) {
            accessor.get = nullptr;
        } else if (IS::Callable(tmp)) {
            accessor.get = std::get<std::shared_ptr<JS::InternalObject>>(tmp.getValue());
        } else {
            throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("get must be callable or undefined")));
        }
    }
    if ((get_or_set = get_or_set || obj->hasProperty(u"set"))) {
        JS::Any tmp = obj->get(u"set");
        if (COMPARE::Type(tmp, UNDEFINED)) {
            accessor.set = nullptr;
        } else if (IS::Callable(tmp)) {
            accessor.set = std::get<std::shared_ptr<JS::InternalObject>>(tmp.getValue());
        } else {
            throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("set must be callable or undefined")));
        }
    }
    if (get_or_set) {
        if (value_or_writable) {
            throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Property descriptor cannot be both accessor and data descriptor")));
        }
        return accessor;
    }
    return data;
}
} // namespace JS::CONVERT