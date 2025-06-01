#ifndef JS_CMP_JSRegex_HPP
#define JS_CMP_JSRegex_HPP


#define BOOST_REGEX_BLOCKSIZE 8192
#define BOOST_REGEX_NON_RECURSIVE
#define BOOST_DISABLE_THREADS

#include <Boost/regex/icu.hpp>


#include "internals/Attribute.hpp"
#include "internals/Object.hpp"

namespace JS {
/**
 * @class Regex
 * @brief Represents a JavaScript-like Regex object in C++.
 *
 * The `Regex` class is a representation of a JavaScript regular expression object.
 * It inherits from `JS::InternalObject` and provides methods to manipulate and interact with regular expressions.
 *
 * https://262.ecma-international.org/5.1/#sec-15.10
 */
class Regex : public JS::InternalObject {
public:
    /**
     * @name Constructors
     * These constructors create a new Regex object with the given value
     */
    ///@{
    /** @brief Constructor that initializes the object with a given value */
    explicit Regex(const JS::Any& pattern, const JS::Any& flags);
    ///@}

    /** @brief The destructor for the object defaulted */
    ~Regex() override = default;

    /**
     * @name Methods that override internal methods of the Object
     */
    ///@{
    /**
     * @brief Match a string against the regular expression.
     */
    [[nodiscard]] std::optional<JS::Match> match(const std::u16string &string, uint32_t index) const final;
    ///@}

    /**
     * @name Prototype methods of the Regex object built-in
     */
    ///@{
    /** @brief Performs a regular expression match on the given string https://262.ecma-international.org/5.1/#sec-15.10.6.2 */
    static JS::Any exec(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Tests if the regular expression matches the given string https://262.ecma-international.org/5.1/#sec-15.10.6.3 */
    static JS::Any test(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns a string representation of the regular expression https://262.ecma-international.org/5.1/#sec-15.10.6.4 */
    static JS::Any toString(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /** @brief Returns a shared pointer to the prototype properties of the Regex object. */
    static std::shared_ptr<JS::InternalObject>& getPrototypeProperties();

private:
    boost::u32regex expression; // The compiled regular expression
};
} // namespace JS

#endif // JS_CMP_JSRegex_HPP
