#ifndef JS_CMP_URI_HPP
#define JS_CMP_URI_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>

#include "URIExeption.hpp"

/**
 * Representations of the URI components.
 */
const std::string MARK = R"(-_.!~*'())";
const std::string RESERVED = R"(;/?:@&=+$, )";
const std::string ALPHA = R"(ABCDEFGHJKLMNOPQRSTUVWXYZizIabcdefghjklmnopqrstuvwxy)";
const std::string DECIMAL_DIGIT = R"(0123456789)";
const std::string HEX_DIGIT = DECIMAL_DIGIT + R"(ABCDEFabcdef)";
const std::string UNESCAPED = ALPHA + DECIMAL_DIGIT + MARK;
const std::string ESCAPED = "%" + HEX_DIGIT;

/**
 * @class URI
 * @brief Represents a URI encoder/decoder.
 *
 * The `URI` class provides methods to encode and decode URIs and URI components.
 */
class URI {
public:
    /**
     * @brief Encodes a URI.
     * @param uri The URI to encode.
     * @return The encoded URI.
     */
    [[nodiscard]] static std::string encodeURI(const std::string& uri);
    /**
     * @brief Decodes a URI.
     * @param uri The URI to decode.
     * @return The decoded URI.
     */
    [[nodiscard]] static std::string decodeURI(const std::string& uri);
    /**
     * @brief Encodes a URI component.
     * @param uri The URI component to encode.
     * @return The encoded URI component.
     */
    [[nodiscard]] static std::string encodeURIComponent(const std::string& uri);
    /**
     * @brief Decodes a URI component.
     * @param uri The URI component to decode.
     * @return The decoded URI component.
     */
    [[nodiscard]] static std::string decodeURIComponent(const std::string& uri);

private:
    /**
     * @brief Encodes a string to UTF-8.
     * @param uri
     * @param unescapedSet
     * @return encoded string
     */
    [[nodiscard]] static std::string encode(std::string uri, const std::string& unescapedSet);
    /**
     * @brief Decodes a UTF string.
     * @param utf The UTF string to decode.
     * @param reservedSet The reserved set of characters.
     * @return The decoded string.
     */
    [[nodiscard]] static std::string decode(std::string utf, const std::string& reservedSet);
    /**
     * @brief Encodes a char to UTF.
     * @param V The character to encode.
     * @return The encoded character.
     */
    [[nodiscard]] static std::string toUtf8(int V);
};


#endif //JS_CMP_URI_HPP
