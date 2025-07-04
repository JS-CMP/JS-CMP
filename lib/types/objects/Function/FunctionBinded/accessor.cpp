#include "internals/PropertyProxy.hpp"
#include "types/objects/Function/JsFunctionBinded.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

JS::Any JS::FunctionBinded::internal_call(const JS::Any& thisArg, const JS::Any& args) {
    return internal_constructor(thisArg, args);
}

JS::Any JS::FunctionBinded::internal_constructor(const JS::Any& thisArgs, const JS::Any& args) {
    throw std::runtime_error("Not implemented"); // TODO:: Fix + change error
}