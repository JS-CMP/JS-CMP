#ifndef JSARRAY_HPP
#define JSARRAY_HPP

#include "types/objects/JsObject.hpp"

namespace JS {

static const std::u16string ArraySeparator = u","; // Default separator, can be overridden by host environment

/**
 * @class Array
 * @brief Represents a JavaScript-like array object in C++.
 *
 * The `Array` class represents an array object in JavaScript. It inherits from `InternalObject`
 * and provides methods for working with arrays in a JavaScript-like syntax.
 */
class Array : public JS::InternalObject {
public:
    /**
     * @name Constructors
     * These constructors create a new Array object with the given value
     */
    ///@{
    /** @brief Default constructor initializes an empty array */
    Array();
    /** @brief Default constructor initializes an empty array of given length */
    explicit Array(const JS::Any& args);
    /** @brief Default constructor initializes an array with the given vector of Any */
    explicit Array(const std::vector<JS::Any>& data);
    /** @brief Constructor for properties with a given set of properties */
    explicit Array(const JS::Properties& properties);
    ///@}

    /** @brief The destructor for the object defaulted */
    ~Array() override = default;

    /**
     * @name Methods that override internal methods of the Object
     */
    ///@{
    /**
     * @brief Define a property in the Array object.
     * https://262.ecma-international.org/5.1/#sec-15.4.5.1
     */
    bool defineOwnProperty(const std::u16string& key, JS::Attribute attribute, bool is_throw = false) final;
    ///@}

    /**
     * @name Prototype methods of the Array object built-in
     */
    ///@{
    /** @brief Returns a string representing the specified object. https://262.ecma-international.org/5.1/#sec-15.4.4.2
     */
    static JS::Any toString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the locale string of it. https://262.ecma-international.org/5.1/#sec-15.4.4.3 */
    static JS::Any toLocaleString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Concatenates the array with other values. https://262.ecma-international.org/5.1/#sec-15.4.4.4 */
    static JS::Any concat(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Joins all elements of the array into a string. https://262.ecma-international.org/5.1/#sec-15.4.4.5 */
    static JS::Any join(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Removes the last element from the array and returns it.
     * https://262.ecma-international.org/5.1/#sec-15.4.4.6 */
    static JS::Any pop(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Adds one or more elements to the end of the array and returns the new length.
     * https://262.ecma-international.org/5.1/#sec-15.4.4.7 */
    static JS::Any push(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Reverses the order of the elements in the array. https://262.ecma-international.org/5.1/#sec-15.4.4.8 */
    static JS::Any reverse(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Removes the first element from the array and returns it.
     * https://262.ecma-international.org/5.1/#sec-15.4.4.9 */
    static JS::Any shift(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns a shallow copy of a portion of the array. https://262.ecma-international.org/5.1/#sec-15.4.4.10
     */
    static JS::Any slice(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sorts the elements of the array in place. https://262.ecma-international.org/5.1/#sec-15.4.4.11 */
    static JS::Any sort(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Changes the contents of the array by removing or replacing elements.
     * https://262.ecma-international.org/5.1/#sec-15.4.4.12 */
    static JS::Any splice(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Adds one or more elements to the beginning of the array and returns the new length.
     * https://262.ecma-international.org/5.1/#sec-15.4.4.13 */
    static JS::Any unshift(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the first index at which a given element can be found.
     * https://262.ecma-international.org/5.1/#sec-15.4.4.14 */
    static JS::Any indexOf(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the last index at which a given element can be found.
     * https://262.ecma-international.org/5.1/#sec-15.4.4.15 */
    static JS::Any lastIndexOf(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Tests whether all elements in the array pass the provided function.
     * https://262.ecma-international.org/5.1/#sec-15.4.4.16 */
    static JS::Any every(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Tests whether at least one element in the array passes the provided function.
     * https://262.ecma-international.org/5.1/#sec-15.4.4.17 */
    static JS::Any some(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Executes a provided function once for each array element.
     * https://262.ecma-international.org/5.1/#sec-15.4.4.18 */
    static JS::Any forEach(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Creates a new array with the results of calling a provided function on every element.
     * https://262.ecma-international.org/5.1/#sec-15.4.4.19 */
    static JS::Any map(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Creates a new array with all elements that pass the provided function.
     * https://262.ecma-international.org/5.1/#sec-15.4.4.20 */
    static JS::Any filter(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Applies a function against an accumulator and each element to reduce it to a single value.
     * https://262.ecma-international.org/5.1/#sec-15.4.4.21 */
    static JS::Any reduce(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Applies a function against an accumulator and each element from right to left to reduce it to a single
     * value. https://262.ecma-international.org/5.1/#sec-15.4.4.22 */
    static JS::Any reduceRight(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /**
     * @name Static methods of the Array object built-in
     */
    ///@{
    /** @brief Determines whether the passed value is an array. This method returns true if the value is an array, and
     * false otherwise. https://262.ecma-international.org/5.1/#sec-15.4.3.2 */
    static JS::Any isArray(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /** @brief Returns a shared pointer to the prototype properties of the Array object. */
    static std::shared_ptr<JS::InternalObject>& getPrototypeProperties();

    /**
     * @name Methods that represent the functions needed for calling and constructing
     */
    ///@{
    /** @brief Function that represent the constructor of the Object */
    static Any internal_constructor(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Function that is used when object is call as a function */
    static Any internal_call(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    [[nodiscard]] std::u16string getContent() const override;
};

} // namespace JS
#endif // JSARRAY_HPP