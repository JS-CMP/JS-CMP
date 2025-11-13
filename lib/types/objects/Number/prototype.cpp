#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsNumber.hpp"

#include <utils/Convert.hpp>

JS::Any JS::Number::toString(const JS::Any& thisArg, const JS::Any& args) {
    // TODO: make the real func
    return JS::Any(JS::CONVERT::ToString(std::get<double>(std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())->primitiveValue)));
}

JS::Any JS::Number::toLocaleString(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::Number::valueOf(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::Number::toFixed(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::Number::toExponential(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}

JS::Any JS::Number::toPrecision(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}
