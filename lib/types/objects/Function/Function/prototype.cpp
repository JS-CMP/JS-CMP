#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/Function/JsFunctionBinded.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

#include <types/objects/Error/JsTypeError.hpp>
#include <utils/Is.hpp>

namespace JS {
JS::Any Function::toString(const JS::Any& thisArg, const JS::Any& args) {
    // TODO: Implement this
    return JS::Any("[object Function]");
}

JS::Any Function::apply(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::IS::Callable(thisArg)) {
        throw JS::Any(std::make_shared<JS::TypeError>(JS::Any("Function.prototype.apply called on non-object")));
    }
    JS::Any thisArgArg = args[u"0"];
    JS::Any argArray = args[u"1"];
    if (JS::COMPARE::Type(argArray, JS::UNDEFINED) || JS::COMPARE::Type(argArray, JS::NULL_TYPE)) {
        return std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())
            ->call_function(thisArg, JS::Arguments::CreateArgumentsObject({}));
    }
    if (!JS::COMPARE::Type(argArray, JS::OBJECT)) {
        throw JS::Any(std::make_shared<JS::TypeError>(JS::Any("Function.prototype.apply called with non-object args")));
    }
    auto n = JS::CONVERT::ToUint32(argArray[u"length"]);
    std::vector<JS::Any> argList;
    int index = 0;
    while (index < n) {
        argList.push_back(argArray[index]);
        index++;
    }
    return std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())
        ->call_function(thisArgArg, JS::Arguments::CreateArgumentsObject(argList));
}

JS::Any Function::call(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::IS::Callable(thisArg)) {
        throw JS::Any(std::make_shared<JS::TypeError>(JS::Any("Function.prototype.call called on non-object")));
    }
    JS::Any thisArgArg = args[u"0"];
    JS::Any argArray = args[u"1"];
    std::vector<JS::Any> argList;
    auto n = JS::CONVERT::ToUint32(argArray[u"length"]);
    int index = 1;
    while (index < n) {
        argList.push_back(args[index]);
        index++;
    }
    return std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())
        ->call_function(thisArgArg, JS::Arguments::CreateArgumentsObject(argList));
}

JS::Any Function::bind(const JS::Any& thisArg, const JS::Any& args) {
    const JS::Any& target = thisArg;
    if (!JS::IS::Callable(target)) {
        throw JS::Any(std::make_shared<JS::TypeError>(JS::Any("Function.prototype.bind called on non-object")));
    }
    std::vector<JS::Any> A;
    auto n = JS::CONVERT::ToUint32(args[u"length"]);
    int index = 1;
    while (index < n) {
        A.push_back(args[index]);
        index++;
    }
    const std::shared_ptr<JS::FunctionBinded> F = std::make_shared<JS::FunctionBinded>(
        std::get<std::shared_ptr<JS::InternalObject>>(target.getValue()), args[0], A);
    F->class_name = u"Function Binded"; // temporary
    if (JS::COMPARE::Object(target, u"Function")) {
        const int L = JS::CONVERT::ToInteger(target[u"length"]) - static_cast<int>(A.size());
        F->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(L < 0 ? 0 : L), false, false, true}, false);
    } else {
        F->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(0), false, false, true}, false);
    }
    // TODO: make a [[ThrowTypeError]] function object
    std::shared_ptr<JS::InternalObject> thrower =
        std::make_shared<JS::Function>([](const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
            throw JS::Any(std::make_shared<JS::TypeError>(
                JS::Any("Cannot access 'caller' or 'arguments.callee' in strict mode")));
        });
    F->defineOwnProperty(u"caller", JS::AccessorDescriptor{thrower, thrower, false, false}, false);
    F->defineOwnProperty(u"arguments", JS::AccessorDescriptor{thrower, thrower, false, false}, false);
    return JS::Any(F);
}
} // namespace JS