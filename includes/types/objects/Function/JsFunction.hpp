#ifndef JSFUNCTION_HPP
#define JSFUNCTION_HPP

#include "types/objects/JsObject.hpp"

namespace JS {

/**
 * @class Function
 * @brief Represents a JavaScript-like function object in C++.
 *
 * The `Function` class encapsulates a callable entity, allowing it to store
 * and invoke a function. This class provides a JavaScript-inspired interface,
 * enabling function calls with various arguments.
 */
class Function : public JS::InternalObject {
public:
    /**
     * @name Constructors
     * These constructors create a new Function object.
     */
    ///@{
    /** @brief Default constructor initializes the object with an empty map */
    Function();
    /** @brief Constructs a Function object with a callable `FunctionType`. */
    explicit Function(FunctionType f, int length = 0);
    /** @brief Copy constructor */
    Function(const Function& f) = default;
    /** @brief Move constructor */
    Function(Function&& f) noexcept;
    /** @brief Copy assignment operator */
    Function& operator=(const Function& function);
    /** @brief Move assignment operator */
    Function& operator=(Function&& f) noexcept;
    ///@}

    /** @brief Destructor */
    ~Function() override = default;

    /**
     * @name Methods to make prototype methods of the Function built-in
     */
    ///@{
    /** @brief return the stringified version of the function https://262.ecma-international.org/5.1/#sec-15.3.4.2 */
    static JS::Any toString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief apply given arguments to the function https://262.ecma-international.org/5.1/#sec-15.3.4.3 */
    static JS::Any apply(const JS::Any& thisArg, const JS::Any& args);
    /** @brief call the function with given arguments https://262.ecma-international.org/5.1/#sec-15.3.4.4 */
    static JS::Any call(const JS::Any& thisArg, const JS::Any& args);
    /** @brief bind the function to a given object https://262.ecma-international.org/5.1/#sec-15.3.4.5 */
    static JS::Any bind(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /**
     * @name Internal Properties Overriden from Function
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Get a property of the object with all the parent included and all the checks for descriptor
     * https://262.ecma-international.org/5.1/#sec-15.3.5.4 */
    [[nodiscard]] JS::Any get(const std::u16string& key) const final;
    /** @brief Check if the object is an instance of another object */
    [[nodiscard]] bool hasInstance(const JS::Any& value) const override;
    ///@}

    [[nodiscard]] std::u16string getContent() const override;

};

} // namespace JS

#endif // JSFUNCTION_HPP
