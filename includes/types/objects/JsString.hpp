#ifndef JS_CMP_JSSTRING_HPP
#define JS_CMP_JSSTRING_HPP

#include "internals/Attribute.hpp"
#include "internals/Object.hpp"

namespace JS {
/**
 * @class String
 * @brief Represents the string object in C++
 *
 * The `String` class represents a JavaScript-like string object in C++. It provides the different methods defined in
 * the ECMAScript specification for the String object. It also provides a method to get an internal object that holds
 * the methods of the property prototype.
 *
 * https://262.ecma-international.org/5.1/#sec-15.5
 */
class String : public JS::InternalObject {
public:
    /**
     * @name Constructors
     * These constructors create a new String object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the object with an empty map */
    String();
    /** @brief Constructor that initializes the object with a given value */
    explicit String(const JS::Any& value);
    /** @brief Constructor that initializes the object with a given set of properties */
    explicit String(const std::unordered_map<std::u16string, JS::Any>& properties);
    ///@}

    /** @brief The destructor for the object defaulted */
    ~String() override = default;

    /**
     * @name Methods that override internal methods of the Object
     */
    ///@{
    /**
     * @brief Retrieves the property descriptor of an own property.
     */
    [[nodiscard]] std::optional<JS::Attribute> getOwnProperty(const std::u16string& key) const final;
    ///@}

    /**
     * @name Prototype methods of the String object built-in
     */
    ///@{
    /** @brief Returns a string representing the specified object. https://262.ecma-international.org/5.1/#sec-15.5.4.2
     */
    static JS::Any toString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the primitive value of the specified object. https://262.ecma-international.org/5.1/#sec-15.5.4.3
     */
    static JS::Any valueOf(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns a string containing the character at the specified index.
     * https://262.ecma-international.org/5.1/#sec-15.5.4.4 */
    static JS::Any charAt(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns an integer between 0 and 65535 representing the UTF-16 code unit at the specified index.
     * https://262.ecma-international.org/5.1/#sec-15.5.4.5 */
    static JS::Any charCodeAt(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Concatenates the string arguments and returns the result as a new string.
     * https://262.ecma-international.org/5.1/#sec-15.5.4.6 */
    static JS::Any concat(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the index within the calling String object of the first occurrence of the specified value,
     * starting the search at fromIndex. https://262.ecma-international.org/5.1/#sec-15.5.4.7 */
    static JS::Any indexOf(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the index within the calling String object of the last occurrence of the specified value, or -1
     * if not found. https://262.ecma-international.org/5.1/#sec-15.5.4.8 */
    static JS::Any lastIndexOf(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Compares two strings in the current locale. https://262.ecma-international.org/5.1/#sec-15.5.4.9 */
    static JS::Any localeCompare(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Retrieves the result of matching a string against a regular expression.
     * https://262.ecma-international.org/5.1/#sec-15.5.4.10 */
    static JS::Any match(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns a new string with some or all matches of a pattern replaced by a replacement.
     * https://262.ecma-international.org/5.1/#sec-15.5.4.11 */
    static JS::Any replace(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Executes the search for a match between a regular expression and this String object.
     * https://262.ecma-international.org/5.1/#sec-15.5.4.12 */
    static JS::Any search(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Extracts a section of a string and returns it as a new string.
     * https://262.ecma-international.org/5.1/#sec-15.5.4.13 */
    static JS::Any slice(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Splits a String object into an array of strings by separating the string into substrings.
     * https://262.ecma-international.org/5.1/#sec-15.5.4.14 */
    static JS::Any split(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns a section of a string between two indices into a new string.
     * https://262.ecma-international.org/5.1/#sec-15.5.4.15 */
    static JS::Any substring(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Converts a string to lowercase letters. https://262.ecma-international.org/5.1/#sec-15.5.4.16 */
    static JS::Any toLowerCase(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Converts a string to lowercase letters, taking into account the host environment's current locale.
     * https://262.ecma-international.org/5.1/#sec-15.5.4.17 */
    static JS::Any toLocaleLowerCase(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Converts a string to uppercase letters. https://262.ecma-international.org/5.1/#sec-15.5.4.18 */
    static JS::Any toUpperCase(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Converts a string to uppercase letters, taking into account the host environment's current locale.
     * https://262.ecma-international.org/5.1/#sec-15.5.4.19 */
    static JS::Any toLocaleUpperCase(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Removes whitespace from both ends of a string. https://262.ecma-international.org/5.1/#sec-15.5.4.20 */
    static JS::Any trim(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /**
     * @name Static methods of the String object built-in
     */
    ///@{
    /** @brief Creates a string from a sequence of UTF-16 code unit values.
     * https://262.ecma-international.org/5.1/#sec-15.5.3.2 */
    [[nodiscard]] static JS::Any fromCharCode(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    [[nodiscard]] std::u16string getContent() const override;


    /** @brief Returns a shared pointer to the prototype properties of the String object. */
    static std::shared_ptr<JS::InternalObject>& getPrototypeProperties();
};
} // namespace JS

#endif // JS_CMP_JSSTRING_HPP
