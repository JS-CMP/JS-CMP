#include "class/URI/URI.hpp"

#include <class/URI/URI.hpp>

std::string URI::toUtf8(int V) {
    std::ostringstream encoded;
    encoded << std::hex << std::uppercase << '%' << std::setw(2) << std::setfill('0') << V;
    return encoded.str();
}

std::string URI::encode(std::string uri, const std::string& unescapedSet) {
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

std::string URI::decode(std::string utf8, const std::string& reservedSet) {
    std::ostringstream decoded;
    for (int i = 0; i < utf8.size(); ++i) {
        if (reservedSet.contains(utf8[i])) {
            if (!(i + 2 < utf8.size() && std::isxdigit(utf8[i + 1]) && std::isxdigit(utf8[i + 2])))
                throw URIException("Invalid percent-encoding in utf8 string.");

            std::string hexValue = utf8.substr(i + 1, 2);
            decoded << static_cast<char>(std::stoi(hexValue, nullptr, 16));;
            i += 2;
        } else {
            decoded << utf8[i];
        }
    }
    return decoded.str();
}

std::string URI::encodeURI(const std::string& uri) {
    return encode(uri, RESERVED + UNESCAPED + "%");
}

std::string URI::decodeURI(const std::string& uri) {
    return decode(uri, "%#");
}

std::string URI::encodeURIComponent(const std::string& uri) {
    return encode(uri, UNESCAPED);
}

std::string URI::decodeURIComponent(const std::string& uri) {
    return decode(uri, "");
}

