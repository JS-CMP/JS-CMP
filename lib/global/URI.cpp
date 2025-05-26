#include "internals/PropertyProxy.hpp"

#include <cctype>
#include <iomanip>
#include <sstream>
#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

static const std::string MARK = R"(-_.!~*'())";
static const std::string RESERVED = R"(;/?:@&=+$,)";
static const std::string ALPHA = R"(ABCDEFGHJKLMNOPQRSTUVWXYZizIabcdefghjklmnopqrstuvwxy)";
static const std::string DECIMAL_DIGIT = R"(0123456789)";
static const std::string HEX_DIGIT = DECIMAL_DIGIT + R"(ABCDEFabcdef)";
static const std::string UNESCAPED = ALPHA + DECIMAL_DIGIT + MARK;
static const std::string ESCAPED = "%" + HEX_DIGIT;

std::string toUtf8(int V) {
    std::ostringstream encoded;
    encoded << std::hex << std::uppercase << '%' << std::setw(2) << std::setfill('0') << V;
    return encoded.str();
}

std::string encode(std::string uri, const std::string& unescapedSet) {
    std::string res;
    for (int k = 0; k < uri.length(); k++) {
        unsigned char c = uri[k];
        if (unescapedSet.contains(c)) {
            res += c;
        } else {
            res += toUtf8(c);
        }
    }
    return res;
}

std::string decode(std::string utf, const std::string& reservedSet) {
    std::ostringstream decoded;
    for (int i = 0; i < utf.size(); ++i) {
        if (reservedSet.contains(utf[i])) {
            if (!(i + 2 < utf.size() && std::isxdigit(utf[i + 1]) && std::isxdigit(utf[i + 2]))) {
                throw std::runtime_error("Invalid percent-encoding in utf8 string.");
            }

            std::string hexValue = utf.substr(i + 1, 2);
            decoded << static_cast<char>(std::stoi(hexValue, nullptr, 16));
            i += 2;
        } else {
            decoded << utf[i];
        }
    }
    return decoded.str();
}

namespace JS::GLOBAL {
JS::Any encodeURI(const JS::Any& thisArgs, const JS::Any& args) {
    auto uriStr = JS::CONVERT::ToUtf8(JS::CONVERT::ToString(args[1]));
    return JS::Any(JS::CONVERT::ToUtf16(encode(uriStr, RESERVED + UNESCAPED + "%")));
}

JS::Any decodeURI(const JS::Any& thisArgs, const JS::Any& args) {
    auto uriStr = JS::CONVERT::ToUtf8(JS::CONVERT::ToString(args["0"]));
    return JS::Any(JS::CONVERT::ToUtf16(decode(uriStr, "%#")));
}

JS::Any encodeURIComponent(const JS::Any& thisArgs, const JS::Any& args) {
    auto uriStr = JS::CONVERT::ToUtf8(JS::CONVERT::ToString(args["0"]));
    return JS::Any(JS::CONVERT::ToUtf16(encode(uriStr, UNESCAPED)));
}

JS::Any decodeURIComponent(const JS::Any& thisArgs, const JS::Any& args) {
    auto uriStr = JS::CONVERT::ToUtf8(JS::CONVERT::ToString(args["0"]));
    return JS::Any(JS::CONVERT::ToUtf16(decode(uriStr, "")));
}
} // namespace JS::GLOBAL
