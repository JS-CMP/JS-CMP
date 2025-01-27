#include "../../../../includes/types/JsAny.hpp"
#include "../../../../includes/utils/Convert.hpp"

JS::Any JS::Any::operator>>(const JS::Any& other) const {
    int32_t lnum = JS::CONVERT::ToInt32(*this);
    uint32_t shiftCount = JS::CONVERT::ToUint32(other) & 0x1F;
    return JS::Any(lnum >> shiftCount);
}

JS::Any JS::Any::operator>>(int value) const {
    int32_t lnum = JS::CONVERT::ToInt32(*this);
    uint32_t shiftCount = JS::CONVERT::ToUint32(value) & 0x1F;
    return JS::Any(lnum >> shiftCount);
}

JS::Any JS::Any::operator>>(double value) const {
    int32_t lnum = JS::CONVERT::ToInt32(*this);
    uint32_t shiftCount = JS::CONVERT::ToUint32(value) & 0x1F;
    return JS::Any(lnum >> shiftCount);
}

JS::Any JS::Any::operator>>(const char* value) const {
    int32_t lnum = JS::CONVERT::ToInt32(*this);
    uint32_t shiftCount = JS::CONVERT::ToUint32(value) & 0x1F;
    return JS::Any(lnum >> shiftCount);
}

JS::Any JS::Any::operator>>(bool value) const {
    int32_t lnum = JS::CONVERT::ToInt32(*this);
    uint32_t shiftCount = JS::CONVERT::ToUint32(value) & 0x1F;
    return JS::Any(lnum >> shiftCount);
}

JS::Any JS::Any::operator>>(JS::Null value) const {
    int32_t lnum = JS::CONVERT::ToInt32(*this);
    uint32_t shiftCount = JS::CONVERT::ToUint32(value) & 0x1F;
    return JS::Any(lnum >> shiftCount);
}

JS::Any JS::Any::operator>>(JS::Undefined value) const {
    int32_t lnum = JS::CONVERT::ToInt32(*this);
    uint32_t shiftCount = JS::CONVERT::ToUint32(value) & 0x1F;
    return JS::Any(lnum >> shiftCount);
}

namespace JS {
JS::Any operator>>(int value, const JS::Any& any) {
    int32_t lnum = JS::CONVERT::ToInt32(value);
    uint32_t shiftCount = JS::CONVERT::ToUint32(any) & 0x1F;
    return JS::Any(lnum >> shiftCount);
}

JS::Any operator>>(double value, const JS::Any& any) {
    int32_t lnum = JS::CONVERT::ToInt32(value);
    uint32_t shiftCount = JS::CONVERT::ToUint32(any) & 0x1F;
    return JS::Any(lnum >> shiftCount);
}

JS::Any operator>>(const char* value, const JS::Any& any) {
    int32_t lnum = JS::CONVERT::ToInt32(value);
    uint32_t shiftCount = JS::CONVERT::ToUint32(any) & 0x1F;
    return JS::Any(lnum >> shiftCount);
}

JS::Any operator>>(bool value, const JS::Any& any) {
    int32_t lnum = JS::CONVERT::ToInt32(value);
    uint32_t shiftCount = JS::CONVERT::ToUint32(any) & 0x1F;
    return JS::Any(lnum >> shiftCount);
}

JS::Any operator>>(JS::Null value, const JS::Any& any) {
    int32_t lnum = JS::CONVERT::ToInt32(value);
    uint32_t shiftCount = JS::CONVERT::ToUint32(any) & 0x1F;
    return JS::Any(lnum >> shiftCount);
}

JS::Any operator>>(JS::Undefined value, const JS::Any& any) {
    int32_t lnum = JS::CONVERT::ToInt32(value);
    uint32_t shiftCount = JS::CONVERT::ToUint32(any) & 0x1F;
    return JS::Any(lnum >> shiftCount);
}

} // namespace JS