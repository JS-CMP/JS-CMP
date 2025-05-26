#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

DECLARE_1FUNC(JS::Any JS::Any::operator>>, const {
    return JS::Any(JS::CONVERT::ToInt32(*this) >> (JS::CONVERT::ToUint32(value) & 0x1F));
})

namespace JS {
DECLARE_2FUNC(JS::Any operator>>, {
    return JS::Any(JS::CONVERT::ToInt32(value) >> (JS::CONVERT::ToUint32(any) & 0x1F));
})

} // namespace JS