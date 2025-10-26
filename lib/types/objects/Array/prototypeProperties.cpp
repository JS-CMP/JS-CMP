#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsArray.hpp"

std::shared_ptr<JS::InternalObject>& JS::Array::getPrototypeProperties(const std::shared_ptr<JS::InternalObject>& constructor) {
    static std::unordered_map<std::u16string, JS::Attribute> properties_prototype = {
        {u"toString", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::toString, 0, u"toString")), true, true, true}},
        {u"toLocaleString", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::toLocaleString, 0, u"toLocaleString")), true, true, true}},
        {u"concat", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::concat, 1, u"concat")), true, true, true}},
        {u"join", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::join, 1, u"join")), true, true, true}},
        {u"pop", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::pop, 0, u"pop")), true, true, true}},
        {u"push", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::push, 1, u"push")), true, true, true}},
        {u"reverse", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::reverse, 0, u"reverse")), true, true, true}},
        {u"shift", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::shift, 0, u"shift")), true, true, true}},
        {u"slice", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::slice, 2, u"slice")), true, true, true}},
        {u"sort", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::sort, 1, u"sort")), true, true, true}},
        {u"splice", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::splice, 2, u"splice")), true, true, true}},
        {u"unshift", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::unshift, 1, u"unshift")), true, true, true}},
        {u"indexOf", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::indexOf, 1, u"indexOf")), true, true, true}},
        {u"lastIndexOf", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::lastIndexOf, 1, u"lastIndexOf")), true, true, true}},
        {u"every", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::every, 1, u"every")), true, true, true}},
        {u"some", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::some, 1, u"some")), true, true, true}},
        {u"forEach", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::forEach, 1, u"forEach")), true, true, true}},
        {u"map", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::map, 1, u"map")), true, true, true}},
        {u"filter", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::filter, 1, u"filter")), true, true, true}},
        {u"reduce", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::reduce, 1, u"reduce")), true, true, true}},
        {u"reduceRight", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::reduceRight, 1, u"reduceRight")), true, true, true}},
        {u"constructor", JS::DataDescriptor{JS::Any(constructor ? constructor : JS::Array::getConstructor()), true, false, true}},
    };
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(properties_prototype, JS::Object::getPrototypeProperties(), OBJECT_CLASS_NAME, true);

    return instance;
}