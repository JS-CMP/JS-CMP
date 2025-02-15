#include "global/Console.hpp"

#include "internals/PropertyProxy.hpp"
#include "utils/Convert.hpp"

namespace JS {
JS::Any Console::log(const JS::Any& thisArg, const JS::Any& args) {
    const uint32_t i = JS::CONVERT::ToUint32(args["length"]);
    for (uint32_t j = 0; j < i; j++) {
        if (j > 0) {
            std::cout << " ";
        }
        std::cout << args[j];
    }
    std::cout << std::endl;
    return JS::Any(JS::Undefined{});
}
} // namespace JS