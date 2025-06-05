#include "internals/PropertyProxy.hpp"
#include "types/objects/JsString.hpp"

#include <utils/Convert.hpp>

// static
JS::Any JS::String::fromCharCode(const JS::Any& thisArg, const JS::Any& args) {
    size_t length = JS::CONVERT::ToUint32(args[u"length"]);
    std::u16string result;
    result.reserve(length);
    for (uint32_t i = 0; i < length; ++i) {
        char16_t ch = JS::CONVERT::ToUint16(args[i]);
        result.push_back(ch);
    }
    return JS::Any(result);
}