#include "internals/Operator.hpp"
#include "types/JsAny.hpp"

#include <cmath>
#include <utils/Convert.hpp>

#define APPLY_MODULO_UINT16(value) ((uint16_t)((value) % 0x10000))

namespace JS::CONVERT {
uint16_t ToUint16(int value) {
    return APPLY_MODULO_UINT16(value < 0 ? -static_cast<int64_t>(value) : value);
}
uint16_t ToUint16(double value) {
    if (std::isnan(value) || value == 0 || !std::isfinite(value)) {
        return 0;
    }
    double posInt = std::signbit(value) ? -std::floor(std::abs(value)) : std::floor(std::abs(value));
    return APPLY_MODULO_UINT16(static_cast<int64_t>(posInt));
}
uint16_t ToUint16(bool value) {
    return value ? 1 : 0;
}
uint16_t ToUint16(unsigned int value) {
    return value <= 0xFFFF ? static_cast<uint16_t>(value) : 0xFFFF;
}
uint16_t ToUint16(const char* value) {
    return ToUint16(ToNumber(value));
}
uint16_t ToUint16(const char16_t* value) {
    return ToUint16(ToNumber(value));
}
uint16_t ToUint16(const std::string& str) {
    return ToUint16(ToNumber(str));
}
uint16_t ToUint16(const std::u16string& str) {
    return ToUint16(ToNumber(str));
}
uint16_t ToUint16(const Rope& rope) {
    return ToUint16(rope.toString());
}
uint16_t ToUint16(JS::Null /*unused*/) {
    return 0;
}
uint16_t ToUint16(JS::Undefined /*unused*/) {
    return 0;
}
uint16_t ToUint16(const JS::Operator& any) { // https://262.ecma-international.org/5.1/#sec-9.7
    switch (any.getValue().index()) {
        case NUMBER:
            return ToUint16(std::get<double>(any.getValue()));
        case STRING:
            return ToUint16(std::get<Rope>(any.getValue()));
        case BOOLEAN:
            return ToUint16(std::get<bool>(any.getValue()));
        case UNDEFINED:
            return ToUint16(JS::Undefined());
        case NULL_TYPE:
            return ToUint16(JS::Null());
        default:
            return 0;
    }
}
} // namespace JS::CONVERT