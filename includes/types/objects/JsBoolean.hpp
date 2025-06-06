#ifndef JS_CMP_JSBOOLEAN_HPP
#define JS_CMP_JSBOOLEAN_HPP

#include "internals/Object.hpp"

namespace JS {
/**
 * @class Boolean
 * @brief Represent the boolean object in C++
 *
 * The `Boolean` class represents a JavaScript-like boolean object in C++. It provides the different methods define in
 * the ECMA of the boolean. It also provides a method to get an internal object that hold the methods of the property
 * prototype.
 *
 * https://262.ecma-international.org/5.1/#sec-15.6
 */
class Boolean : public JS::InternalObject {
public:
    /**
     * @name Constructors
     * These constructors create a new Object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the Boolean with true */
    Boolean();
    /** @brief Constructor that take a value */
    explicit Boolean(const JS::Any& value);
    ///@}

    /** @brief The destructor for the boolean defaulted */
    ~Boolean() override = default;

    /**
     * @name Methods to make prototype methods of the Object built-in
     */
    ///@{
    /** @brief Returns the prototype of the boolean https://262.ecma-international.org/5.1/#sec-15.6.4.2 */
    static JS::Any toString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the value of the boolean https://262.ecma-international.org/5.1/#sec-15.6.4.3 */
    static JS::Any valueOf(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /** @brief Function to get the methods of the property prototype */
    static std::shared_ptr<JS::InternalObject>& getPrototypeProperties();

//    [[nodiscard]] std::string getContent() const override;
};
} // namespace JS

#endif // JS_CMP_JSBOOLEAN_HPP
