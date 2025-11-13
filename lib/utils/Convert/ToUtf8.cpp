#include <string>
#include <types/JsAny.hpp>
#include <types/objects/Error/JsTypeError.hpp>
#include <unicode/unistr.h>
#include <unicode/ustream.h>

namespace JS::CONVERT {
std::string ToUtf8(const std::u16string& utf16_str) {
    try {
        icu::UnicodeString unicode_str(reinterpret_cast<const UChar*>(utf16_str.c_str()), utf16_str.length());
        std::string utf8_str;
        utf8_str.reserve(utf16_str.length() * 2);
        unicode_str.toUTF8String(utf8_str);
        return utf8_str;
    } catch (const std::exception& e) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("UTF-8 conversion failed: " + std::string(e.what()))));
    }
}

std::string ToUtf8(char16_t ch) {
    if (ch >= 0xD800 && ch <= 0xDFFF) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Invalid UTF-16 surrogate code unit")));
    }
    if (ch <= 0x7F) {
        return std::string(1, static_cast<char>(ch));
    }
    try {
        icu::UnicodeString unicode_str(reinterpret_cast<const UChar*>(&ch), 1);
        std::string utf8_str;
        unicode_str.toUTF8String(utf8_str);
        return utf8_str;
    } catch (const std::exception& e) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("UTF-8 conversion failed: " + std::string(e.what()))));
    }
}
} // namespace JS::CONVERT

std::ostream& operator<<(std::ostream& os, const std::u16string& str) {
    os << JS::CONVERT::ToUtf8(str);
    return os;
}