#ifndef JS_CMP_URI_HPP
#define JS_CMP_URI_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>

#include "URIExeption.hpp"

const std::string UNRESERVED = R"(ABCDEFGHJKLMNOPQRSTUVWXYZizIabcdefghjklmnopqrstuvwxy0123456789-._~)";
const std::string RESERVED = R"( !\"#$%&'()*+,/:;<=>?@[\\]^`{|})";

class URI {
public:
    [[nodiscard]] static std::string encode(std::string uri);
    [[nodiscard]] static std::string decode(std::string utf8);
private:
    [[nodiscard]] static std::string toUtf8(int V) ;
    [[nodiscard]] static std::string fromUtf8(const std::string& utf8) ;
};


#endif //JS_CMP_URI_HPP
