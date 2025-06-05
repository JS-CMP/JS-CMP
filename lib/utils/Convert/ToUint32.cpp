#include "types/JsAny.hpp"

#include <cmath>
#include <utils/Convert.hpp>

#define APPLY_MODULO_UINT32(value) ((uint32_t)((value) % 0x100000000))

namespace JS::CONVERT {
uint32_t ToUint32(int value) {
    return APPLY_MODULO_UINT32(value < 0 ? -static_cast<int64_t>(value) : value);
}
uint32_t ToUint32(double value) {
    if (std::isnan(value) || value == 0 || !std::isfinite(value)) {
        return 0;
    }
    double posInt = std::signbit(value) ? -std::floor(std::abs(value)) : std::floor(std::abs(value));
    return APPLY_MODULO_UINT32(static_cast<int64_t>(posInt));
}
uint32_t ToUint32(bool value) {
    return value ? 1 : 0;
}
uint32_t ToUint32(unsigned int value) {
    return value <= 0xFFFFFFFF ? static_cast<uint32_t>(value) : 0xFFFFFFFF;
}
uint32_t ToUint32(const char* value) {
    return ToUint32(ToNumber(value));
}
uint32_t ToUint32(const char16_t* value) {
    return ToUint32(ToNumber(value));
}
uint32_t ToUint32(const std::string& str) {
    return ToUint32(ToNumber(str));
}
uint32_t ToUint32(const std::u16string& str) {
    return ToUint32(ToNumber(str));
}
uint32_t ToUint32(const Rope& rope) {
    return ToUint32(rope.toString());
}
uint32_t ToUint32(JS::Null /*unused*/) {
    return 0;
}
uint32_t ToUint32(JS::Undefined /*unused*/) {
    return 0;
}
uint32_t ToUint32(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.6
    switch (any.getValue().index()) {
        case NUMBER:
            return ToUint32(std::get<double>(any.getValue()));
        case STRING:
            return ToUint32(std::get<Rope>(any.getValue()));
        case BOOLEAN:
            return ToUint32(std::get<bool>(any.getValue()));
        case UNDEFINED:
            return ToUint32(JS::Undefined());
        case NULL_TYPE:
            return ToUint32(JS::Null());
        default:
            return 0;
    }
}
} // namespace JS::CONVERT