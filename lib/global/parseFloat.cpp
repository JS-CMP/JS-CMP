#include "types/JsAny.hpp"
#include "internals/PropertyProxy.hpp"

namespace JS::GLOBAL {
JS::Any parseFloat(const JS::Any &thisArgs, const JS::Any &args) { throw std::runtime_error("parseFloat not implemented"); }
} // namespace JS::GLOBAL