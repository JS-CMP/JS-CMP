#include "internals/Object.hpp"
#include "types/JsAny.hpp"
#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsArray.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"
#include "utils/Is.hpp"

#include <types/objects/Error/JsTypeError.hpp>
#include <types/objects/JsArray.hpp>

namespace JS {
JS::Any Object::getPrototypeOf(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args[u"0"], JS::OBJECT)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Object.getPrototypeOf called on non-object")));
    }
    std::shared_ptr<JS::InternalObject> prototype = std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue())->prototype;
    if (prototype == nullptr) {
        return JS::Any(JS::Null{});
    }
    return JS::Any(prototype);
}

JS::Any Object::getOwnPropertyDescriptor(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args[u"0"], JS::OBJECT)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Object.getOwnPropertyDescriptor called on non-object")));
    }
    const std::shared_ptr<JS::InternalObject> O = std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    const std::u16string P = JS::CONVERT::ToString(args[u"1"]);
    std::optional<Attribute> desc = O->getOwnProperty(P);
    if (desc.has_value()) {
        return JS::CONVERT::FromPropertyDescriptor(desc.value());
    }
    return JS::Any(JS::Undefined{});
}

JS::Any Object::getOwnPropertyNames(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args[u"0"], JS::OBJECT)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Object.getOwnPropertyNames called on non-object")));
    }
    std::shared_ptr<JS::InternalObject> O = std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    std::shared_ptr<JS::InternalObject> array = JS::InternalObject::create<JS::Array>();
    int n = 0;
    for (const auto& [key, value] : *O->properties) {
        array->defineOwnProperty(JS::CONVERT::ToString(n), JS::DataDescriptor{JS::Any(key), true, true, true}, false);
        n++;
    }
    array->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(n), false, false, false}, false);
    return JS::Any(array);
}

JS::Any Object::create(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args[u"0"], JS::OBJECT) && !JS::COMPARE::Type(args[u"0"], JS::NULL_TYPE)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Object.create called on non-object")));
    }
    std::shared_ptr<JS::InternalObject> O = std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    std::shared_ptr<JS::InternalObject> obj = JS::InternalObject::create<JS::Object>();
    obj->prototype = O;
    if (!JS::COMPARE::Type(args[u"1"], JS::UNDEFINED)) {
        Object::defineProperties(JS::Any(JS::Null{}), JS::Arguments::CreateArgumentsObject(std::vector<JS::Any>{JS::Any(obj), args[2]}));
    }
    return JS::Any(obj);
}

JS::Any Object::defineProperty(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args[u"0"], JS::OBJECT)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Object.defineProperty called on non-object")));
    }
    std::shared_ptr<JS::InternalObject> O = std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    const std::u16string& name = JS::CONVERT::ToString(args[u"1"]);
    JS::Attribute desc = JS::CONVERT::ToPropertyDescriptor(args[u"2"]);
    O->defineOwnProperty(name, desc);
    return args[0];
}

JS::Any Object::defineProperties(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args[u"0"], JS::OBJECT)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Object.defineProperties called on non-object")));
    }
    std::shared_ptr<JS::InternalObject> O = std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    auto props = JS::CONVERT::ToObject(args[u"1"]);
    std::vector<std::pair<std::u16string, JS::Attribute>> descriptors;
    for (const auto& [key, value] : *props->properties) {
        // TODO can be optimized with a list of enumerable in the object / a genericDescriptor with enumerable
        if (!(JS::IS::DataDescriptor(value) && std::get<JS::DataDescriptor>(value).enumerable || JS::IS::AccessorDescriptor(value) && std::get<JS::AccessorDescriptor>(value).enumerable)) {
            continue;
        }
        O->defineOwnProperty(key, JS::CONVERT::ToPropertyDescriptor(props->get(key)), true);
    }
    return args[0];
}

JS::Any Object::seal(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args[u"0"], JS::OBJECT)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Object.seal called on non-object")));
    }
    std::shared_ptr<JS::InternalObject> O = std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    for (const auto& [key, value] : *O->properties) {
        // TODO can be optimized with a genericDescriptor with configurable
        if (JS::IS::DataDescriptor(value)) {
            JS::DataDescriptor desc = std::get<JS::DataDescriptor>(value);
            desc.configurable = false;
            O->defineOwnProperty(key, desc, true);
        } else if (JS::IS::AccessorDescriptor(value)) {
            JS::AccessorDescriptor desc = std::get<JS::AccessorDescriptor>(value);
            desc.configurable = false;
            O->defineOwnProperty(key, desc, true);
        }
    }
    O->extensible = false;
    return args[0];
}

JS::Any Object::freeze(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args[u"0"], JS::OBJECT)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Object.freeze called on non-object")));
    }
    std::shared_ptr<JS::InternalObject> O = std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    for (const auto& [key, value] : *O->properties) {
        // TODO can be optimized with a genericDescriptor with configurable
        if (JS::IS::DataDescriptor(value)) {
            JS::DataDescriptor desc = std::get<JS::DataDescriptor>(value);
            desc.configurable = false;
            desc.writable = false;
            O->defineOwnProperty(key, desc, true);
        } else if (JS::IS::AccessorDescriptor(value)) {
            JS::AccessorDescriptor desc = std::get<JS::AccessorDescriptor>(value);
            desc.configurable = false;
            O->defineOwnProperty(key, desc, true);
        }
    }
    O->extensible = false;
    return args[0];
}

JS::Any Object::preventExtensions(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args[u"0"], JS::OBJECT)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Object.preventExtensions called on non-object")));
    }
    std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue())->extensible = false;
    return args[0];
}

JS::Any Object::isSealed(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args[u"0"], JS::OBJECT)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Object.isSealed called on non-object")));
    }
    std::shared_ptr<JS::InternalObject> O = std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    for (const auto& [key, value] : *O->properties) {
        // TODO can be optimized with a genericDescriptor with configurable
        if (JS::IS::DataDescriptor(value) && std::get<JS::DataDescriptor>(value).configurable || JS::IS::AccessorDescriptor(value) && std::get<JS::AccessorDescriptor>(value).configurable) {
            return JS::Any(false);
        }
    }
    return JS::Any(!O->extensible);
}

JS::Any Object::isFrozen(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args[u"0"], JS::OBJECT)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Object.isFrozen called on non-object")));
    }
    std::shared_ptr<JS::InternalObject> O = std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    for (const auto& [key, value] : *O->properties) {
        // TODO can be optimized with a genericDescriptor with configurable
        if (JS::IS::DataDescriptor(value) && (std::get<JS::DataDescriptor>(value).configurable || std::get<JS::DataDescriptor>(value).writable) || JS::IS::AccessorDescriptor(value) && std::get<JS::AccessorDescriptor>(value).configurable) {
            return JS::Any(false);
        }
    }
    return JS::Any(!O->extensible);
}

JS::Any Object::isExtensible(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args[u"0"], JS::OBJECT)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Object.isExtensible called on non-object")));
    }
    return JS::Any(std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue())->extensible);
}

JS::Any Object::keys(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(args[u"0"], JS::OBJECT)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Object.keys called on non-object")));
    }
    std::shared_ptr<JS::InternalObject> O = std::get<std::shared_ptr<JS::InternalObject>>(args["0"].getValue());
    std::shared_ptr<JS::InternalObject> array = JS::InternalObject::create<JS::Array>();
    int index = 0;
    for (const auto& [key, value] : *O->properties) {
        // TODO can be optimized with a genericDescriptor with enumerable
        if (JS::IS::DataDescriptor(value) && std::get<JS::DataDescriptor>(value).enumerable || JS::IS::AccessorDescriptor(value) && std::get<JS::AccessorDescriptor>(value).enumerable) {
            array->defineOwnProperty(JS::CONVERT::ToString(index), JS::DataDescriptor{JS::Any(key), true, true, true}, false);
            index++;
        }
    }
    return JS::Any(array);
}
} // namespace JS
