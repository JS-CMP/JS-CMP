#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/Function/JsFunctionBinded.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

namespace JS {
JS::Any Function::toString(const JS::Any& thisArg, const JS::Any& args) {
    // TODO: Implement this
    return JS::Any("[object Function]");
}

JS::Any Function::apply(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(thisArg, JS::OBJECT) &&
        !std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())->isCallable()) {
        throw std::runtime_error("TypeError: Function.prototype.apply called on non-object"); // TypeError
    }
    JS::Any thisArgArg = args["0"];
    JS::Any argArray = args["1"];
    if (JS::COMPARE::Type(argArray, JS::UNDEFINED) || JS::COMPARE::Type(argArray, JS::NULL_TYPE)) {
        return std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())
            ->call_function(thisArg, JS::Arguments::CreateArgumentsObject({}));
    }
    if (!JS::COMPARE::Type(argArray, JS::OBJECT)) {
        throw std::runtime_error("TypeError: Function.prototype.apply called with non-object args"); // TypeError
    }
    int n = JS::CONVERT::ToInteger(argArray["length"]); // TODO replace ToInteger with ToUint32
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
    if (!JS::COMPARE::Type(thisArg, JS::OBJECT) &&
        !std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())->isCallable()) {
        throw std::runtime_error("TypeError: Function.prototype.call called on non-object"); // TypeError
    }
    JS::Any thisArgArg = args["0"];
    JS::Any argArray = args["1"];
    std::vector<JS::Any> argList;
    int n = JS::CONVERT::ToInteger(argArray["length"]); // TODO replace ToInteger with ToUint32
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
    if (!JS::COMPARE::Type(target, JS::OBJECT) &&
        !std::get<std::shared_ptr<JS::InternalObject>>(target.getValue())->isCallable()) {
        throw std::runtime_error("TypeError: Function.prototype.bind called on non-object"); // TypeError
    }
    std::vector<JS::Any> A;
    int n = JS::CONVERT::ToInteger(args["length"]); // TODO replace ToInteger with ToUint32
    int index = 1;
    while (index < n) {
        A.push_back(args[index]);
        index++;
    }
    const std::shared_ptr<JS::FunctionBinded> F = std::make_shared<JS::FunctionBinded>(
        std::get<std::shared_ptr<JS::InternalObject>>(target.getValue()), args[0], A);
    F->class_name = "Function Binded"; // temporary
    if (std::get<std::shared_ptr<JS::InternalObject>>(target.getValue())->class_name == "Function") {
        const int L = JS::CONVERT::ToInteger(target["length"]) - static_cast<int>(A.size());
        F->defineOwnProperty("length", JS::DataDescriptor{JS::Any(L < 0 ? 0 : L), false, false, true}, false);
    } else {
        F->defineOwnProperty("length", JS::DataDescriptor{JS::Any(0), false, false, true}, false);
    }
    // TODO: make a [[ThrowTypeError]] function object
    std::shared_ptr<JS::InternalObject> thrower =
        std::make_shared<JS::Function>([](const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
            throw std::runtime_error("TypeError: Cannot access 'caller' or 'arguments.callee' in strict mode");
        });
    F->defineOwnProperty("caller", JS::AccessorDescriptor{thrower, thrower, false, false}, false);
    F->defineOwnProperty("arguments", JS::AccessorDescriptor{thrower, thrower, false, false}, false);
    return JS::Any(F);
}
} // namespace JS