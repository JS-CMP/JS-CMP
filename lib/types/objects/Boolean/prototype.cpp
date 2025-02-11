#include "types/objects/Boolean/PrototypeMethods.hpp"
#include "types/objects/Function/JsFunction.hpp"

namespace JS::BOOL {
    Any PrototypeMethods::toString(const std::vector<JS::Any>& args) {
        return JS::Any("bool");
    }

    Any PrototypeMethods::valueOf(const std::vector<JS::Any>& args) {
        throw std::runtime_error("not implemented");
    }
}