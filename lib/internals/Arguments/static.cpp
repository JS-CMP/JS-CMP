#include "internals/Arguments.hpp"
#include "types/JsAny.hpp"
#include "types/objects/Function/JsFunction.hpp"
#include "utils/Convert.hpp"

#include <types/objects/Error/JsTypeError.hpp>

namespace JS::Arguments { // TODO Implement non-strict mode
JS::Any CreateArgumentsObject(const std::vector<JS::Any>& args, const std::shared_ptr<JS::InternalObject>& func, const std::vector<std::u16string>& names, const std::shared_ptr<JS::InternalObject>& env, bool strict) {
    int len = static_cast<int>(args.size());
    std::shared_ptr<JS::InternalObject> obj = JS::InternalObject::create<JS::Object>();
    obj->class_name = u"Arguments";
    obj->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(len), true, false, true}, false);
    std::shared_ptr<JS::InternalObject> map = JS::InternalObject::create<JS::Object>();
    std::vector<std::u16string> mappedNames;
    int indx = len - 1;
    while (indx >= 0) {
        const JS::Any& val = args[indx];
        std::u16string indxStr = JS::CONVERT::ToString(indx);
        obj->defineOwnProperty(indxStr, JS::DataDescriptor{val, true, true, true}, false);
        // theoretically, this should always be false in strict mode
        // if (!strict && indx < names.size()) {
        // const std::u16string& name = names[indx];
        // if (std::find(mappedNames.begin(), mappedNames.end(), name) == mappedNames.end()) {
        //     mappedNames.push_back(name);
        //     std::shared_ptr<JS::InternalObject> g = JS::InternalObject::create<JS::Function>(
        //         [name, env](const std::vector<JS::Any>& args) -> JS::Any { return env->get(name); });
        //     std::shared_ptr<JS::InternalObject> p = JS::InternalObject::create<JS::Function>(
        //         [name, env](const std::vector<JS::Any>& args) -> JS::Any {
        //             env->put(name, args[0]);
        //             return JS::Any(JS::Undefined{});
        //         });
        //     map->defineOwnProperty(indxStr, JS::AccessorDescriptor{p, g, true, true}, false);
        // }
        //}
        indx--;
    }
    // theoretically, this should always be false in strict mode
    // if (!mappedNames.empty()) {
    // TODO: set the [[ParameterMap]] internal property of obj to map
    // TODO: set the [[Get]], [[GetOwnProperty]], [[DefineOwnProperty]], and [[Delete]] internal methods of obj to the
    // definitions provided below with the class Arguments
    //}
    if (!strict) { // theoretically, this should always be false in strict mode
        obj->defineOwnProperty(u"callee", JS::DataDescriptor{JS::Any(func), true, false, true}, false);
    } else {
        static std::shared_ptr<JS::InternalObject> thrower = JS::InternalObject::create<JS::Function>(
            // TODO: make a [[ThrowTypeError]] function object
            [](const JS::Any& thisArg, const JS::Any& args) -> JS::Any { throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Cannot access 'caller' or 'arguments.callee' in strict mode"))); });
        obj->defineOwnProperty(u"caller", JS::AccessorDescriptor{thrower, thrower, false, false}, false);
        obj->defineOwnProperty(u"callee", JS::AccessorDescriptor{thrower, thrower, false, false}, false);
    }
    return JS::Any(obj);
}
} // namespace JS::Arguments