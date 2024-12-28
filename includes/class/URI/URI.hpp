#ifndef JS_CMP_URI_HPP
#define JS_CMP_URI_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>

#include "URIExeption.hpp"

const std::string MARK = R"(-_.!~*'())";
const std::string RESERVED = R"(;/?:@&=+$, )";
const std::string ALPHA = R"(ABCDEFGHJKLMNOPQRSTUVWXYZizIabcdefghjklmnopqrstuvwxy)";
const std::string DECIMAL_DIGIT = R"(0123456789)";
const std::string HEX_DIGIT = DECIMAL_DIGIT + R"(ABCDEFabcdef)";

const std::string UNESCAPED = ALPHA + DECIMAL_DIGIT + MARK;
const std::string ESCAPED = "%" + HEX_DIGIT;

class URI {
public:

    [[nodiscard]] static std::string encodeURI(const std::string& uri);
    [[nodiscard]] static std::string decodeURI(const std::string& uri);
    [[nodiscard]] static std::string encodeURIComponent(const std::string& uri);
    [[nodiscard]] static std::string decodeURIComponent(const std::string& uri);

private:
    [[nodiscard]] static std::string encode(std::string uri, const std::string& unescapedSet);
    [[nodiscard]] static std::string decode(std::string utf8, const std::string& reservedSet);
    [[nodiscard]] static std::string toUtf8(int V);
};


#endif //JS_CMP_URI_HPP
