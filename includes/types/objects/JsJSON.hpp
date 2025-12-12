#ifndef JS_CMP_JSON_HPP
#define JS_CMP_JSON_HPP

#include "utils/Convert.hpp"

#include <set>
#include <vector>

namespace JS {
/**
 * @class JSON
 * @brief Provides JSON parsing and stringification similar to JavaScript's JSON object.
 *
 * The JSON class offers static methods that mimic the behavior of the JavaScript JSON object.
 * It provides parse and stringify methods as specified in ECMA-262 5.1 Section 15.12.
 *
 * The JSON object:
 * - Has [[Prototype]] set to the standard built-in Object prototype
 * - Has [[Class]] set to "JSON"
 * - Has [[Extensible]] set to true
 * - Does not have [[Construct]] (cannot be used with new)
 * - Does not have [[Call]] (cannot be invoked as a function)
 */
class JSON {
public:
    /**
     * @brief Parses a JSON text and produces an ECMAScript value.
     *
     * The parse function parses a JSON text (a JSON-formatted String) and produces an ECMAScript value.
     * The optional reviver parameter is a function that takes two parameters (key and value).
     * It can filter and transform the results.
     *
     * @param thisArg Ignored for this method.
     * @param args A vector containing the text to parse and an optional reviver function.
     * @return A JS::Any containing the parsed value.
     * @throws SyntaxError if the text is not valid JSON.
     *
     * @see https://262.ecma-international.org/5.1/#sec-15.12.2
     */
    static JS::Any parse(const JS::Any& thisArg, const JS::Any& args);

    /**
     * @brief Returns a String in JSON format representing an ECMAScript value.
     *
     * The stringify function returns a String in JSON format representing an ECMAScript value.
     * It can take three parameters:
     * - value: An ECMAScript value, usually an object or array (can also be String, Boolean, Number, or null)
     * - replacer (optional): A function that alters stringification, or an array as a whitelist
     * - space (optional): A String or Number for whitespace injection
     *
     * @param thisArg Ignored for this method.
     * @param args A vector containing the value and optional replacer and space parameters.
     * @return A JS::Any containing the JSON string, or undefined if the value cannot be stringified.
     * @throws TypeError if the structure is cyclical.
     *
     * @see https://262.ecma-international.org/5.1/#sec-15.12.3
     */
    static JS::Any stringify(const JS::Any& thisArg, const JS::Any& args);

private:
    /**
     * @brief Abstract operation Walk for JSON.parse with reviver.
     *
     * A recursive operation that processes parsed JSON values with the reviver function.
     *
     * @param holder The object holding the property.
     * @param name The property name.
     * @param reviver The reviver function.
     * @return The processed value.
     *
     * @see https://262.ecma-international.org/5.1/#sec-15.12.2
     */
    static JS::Any Walk(const std::shared_ptr<JS::InternalObject>& holder, const std::u16string& name,
                        const std::shared_ptr<JS::InternalObject>& reviver);

    /**
     * @brief Abstract operation Str for JSON.stringify.
     *
     * Serializes a value to JSON string format.
     *
     * @param key The property key.
     * @param holder The object holding the property.
     * @param stack Stack for cycle detection.
     * @param indent Current indentation.
     * @param gap The gap string for formatting.
     * @param replacerFunction Optional replacer function.
     * @param propertyList Optional property whitelist.
     * @return The JSON string representation, or undefined.
     *
     * @see https://262.ecma-international.org/5.1/#sec-15.12.3
     */
    static JS::Any Str(const std::u16string& key, const std::shared_ptr<JS::InternalObject>& holder,
                       std::vector<std::shared_ptr<JS::InternalObject>>& stack, std::u16string& indent,
                       const std::u16string& gap, const std::shared_ptr<JS::InternalObject>& replacerFunction,
                       const std::vector<std::u16string>* propertyList);

    /**
     * @brief Abstract operation Quote for JSON.stringify.
     *
     * Wraps a String value in double quotes and escapes special characters.
     *
     * @param value The string to quote.
     * @return The quoted and escaped string.
     *
     * @see https://262.ecma-international.org/5.1/#sec-15.12.3
     */
    static std::u16string Quote(const std::u16string& value);

    /**
     * @brief Abstract operation JO for JSON.stringify.
     *
     * Serializes an object to JSON format.
     *
     * @param value The object to serialize.
     * @param stack Stack for cycle detection.
     * @param indent Current indentation.
     * @param gap The gap string for formatting.
     * @param replacerFunction Optional replacer function.
     * @param propertyList Optional property whitelist.
     * @return The JSON string representation of the object.
     * @throws TypeError if the structure is cyclical.
     *
     * @see https://262.ecma-international.org/5.1/#sec-15.12.3
     */
    static std::u16string JO(const std::shared_ptr<JS::InternalObject>& value,
                             std::vector<std::shared_ptr<JS::InternalObject>>& stack, std::u16string& indent,
                             const std::u16string& gap, const std::shared_ptr<JS::InternalObject>& replacerFunction,
                             const std::vector<std::u16string>* propertyList);

    /**
     * @brief Abstract operation JA for JSON.stringify.
     *
     * Serializes an array to JSON format.
     *
     * @param value The array to serialize.
     * @param stack Stack for cycle detection.
     * @param indent Current indentation.
     * @param gap The gap string for formatting.
     * @param replacerFunction Optional replacer function.
     * @param propertyList Optional property whitelist.
     * @return The JSON string representation of the array.
     * @throws TypeError if the structure is cyclical.
     *
     * @see https://262.ecma-international.org/5.1/#sec-15.12.3
     */
    static std::u16string JA(const std::shared_ptr<JS::InternalObject>& value,
                             std::vector<std::shared_ptr<JS::InternalObject>>& stack, std::u16string& indent,
                             const std::u16string& gap, const std::shared_ptr<JS::InternalObject>& replacerFunction,
                             const std::vector<std::u16string>* propertyList);

    // JSON Lexer/Parser helper methods
    static JS::Any ParseJSONText(const std::u16string& text);
    static JS::Any ParseJSONValue(const std::u16string& text, size_t& pos);
    static void SkipWhitespace(const std::u16string& text, size_t& pos);
    static JS::Any ParseJSONObject(const std::u16string& text, size_t& pos);
    static JS::Any ParseJSONArray(const std::u16string& text, size_t& pos);
    static std::u16string ParseJSONString(const std::u16string& text, size_t& pos);
    static JS::Any ParseJSONNumber(const std::u16string& text, size_t& pos);
    static JS::Any ParseJSONLiteral(const std::u16string& text, size_t& pos);
    static char16_t ParseUnicodeEscape(const std::u16string& text, size_t& pos);
};
} // namespace JS

#endif // JS_CMP_JSON_HPP
