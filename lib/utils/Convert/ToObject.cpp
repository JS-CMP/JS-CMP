#include "types/JsAny.hpp"

namespace JS::CONVERT {
JS::Any ToObject(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.9
    return any;
}
} // namespace JS::CONVERT