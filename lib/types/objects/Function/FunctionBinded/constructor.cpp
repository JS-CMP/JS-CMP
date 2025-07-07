#include "types/objects/JsObject.hpp"
#include "utils/Convert.hpp"

#include <types/objects/Function/JsFunctionBinded.hpp>

namespace JS {

FunctionBinded::FunctionBinded(const std::shared_ptr<JS::InternalObject>& TargetFunction, const JS::Any& BoundThis,
                               const std::vector<JS::Any>& BoundArguments)
    : targetFunction(TargetFunction), boundThis(BoundThis), boundArguments(BoundArguments) {
    this->call_function = [TargetFunction, BoundThis, BoundArguments](const JS::Any& thisArg,
                                                                      const JS::Any& args) -> JS::Any {
        std::vector<JS::Any> newArgs;
        auto n = JS::CONVERT::ToUint32(args[u"length"]);
        newArgs.reserve(BoundArguments.size() + n);
        for (const auto& arg : BoundArguments) {
            newArgs.push_back(arg);
        }
        int index = 0;
        while (index < n) {
            newArgs.push_back(args[index]);
            index++;
        }
        return TargetFunction->call_function(BoundThis, JS::Arguments::CreateArgumentsObject(newArgs));
    };
    this->construct = [TargetFunction, BoundThis, BoundArguments](const JS::Any& thisArg,
                                                                  const JS::Any& args) -> JS::Any {
        std::vector<JS::Any> newArgs;
        auto n = JS::CONVERT::ToUint32(args[u"length"]);
        newArgs.reserve(BoundArguments.size() + n);
        for (const auto& arg : BoundArguments) {
            newArgs.push_back(arg);
        }
        int index = 0;
        while (index < n) {
            newArgs.push_back(args[index]);
            index++;
        }
        return TargetFunction->construct(BoundThis, JS::Arguments::CreateArgumentsObject(newArgs));
    };
}

FunctionBinded::FunctionBinded(const FunctionBinded& f) : JS::Function(f) {
    this->targetFunction = f.targetFunction;
    this->boundThis = f.boundThis;
    this->boundArguments = f.boundArguments;
}

FunctionBinded::FunctionBinded(FunctionBinded&& f) noexcept : JS::Function(std::move(static_cast<JS::Function&&>(f))) {
    this->targetFunction = std::move(f.targetFunction);
    this->boundThis = std::move(f.boundThis);
    this->boundArguments = std::move(f.boundArguments);
}

FunctionBinded& FunctionBinded::operator=(FunctionBinded&& f) noexcept {
    this->targetFunction = std::move(f.targetFunction);
    this->boundThis = std::move(f.boundThis);
    this->boundArguments = std::move(f.boundArguments);
    JS::Function::operator=(std::move(f));
    return *this;
}

} // namespace JS