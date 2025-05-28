#include <string>
#include <unicode/unistr.h>
#include <unicode/ustream.h>

namespace JS::CONVERT {

std::u16string ToUtf16(const std::string& utf8_str) {
    try {
        UErrorCode status = U_ZERO_ERROR;
        icu::UnicodeString unicode_str = icu::UnicodeString::fromUTF8(icu::StringPiece(utf8_str, status));
        if (U_FAILURE(status)) {
            throw std::invalid_argument("Invalid UTF-8 input");
        }
        if (unicode_str.isEmpty()) {
            return std::u16string();
        }
        std::u16string utf16_str;
        utf16_str.reserve(unicode_str.length());
        utf16_str.resize(unicode_str.length());
        unicode_str.extract(0, unicode_str.length(), reinterpret_cast<UChar*>(&utf16_str[0]));
        return utf16_str;
    } catch (const std::exception& e) {
        throw std::runtime_error("UTF-16 conversion failed: " + std::string(e.what()));
    }
}

std::u16string ToUtf16(char ch) {
    if (static_cast<unsigned char>(ch) <= 0x7F) {
        return std::u16string(1, static_cast<char16_t>(ch));
    }
    if (static_cast<unsigned char>(ch) > 0x7F) {
        throw std::invalid_argument("Non-ASCII char not supported for single-char conversion");
    }
    try {
        std::string utf8_str(1, ch);
        UErrorCode status = U_ZERO_ERROR;
        icu::UnicodeString unicode_str = icu::UnicodeString::fromUTF8(icu::StringPiece(utf8_str, status));
        if (U_FAILURE(status)) {
            throw std::invalid_argument("Invalid UTF-8 input");
        }
        std::u16string utf16_str;
        utf16_str.resize(unicode_str.length());
        unicode_str.extract(0, unicode_str.length(), reinterpret_cast<UChar*>(&utf16_str[0]));
        return utf16_str;
    } catch (const std::exception& e) {
        throw std::runtime_error("UTF-16 conversion failed: " + std::string(e.what()));
    }
}
} // namespace JS::CONVERT