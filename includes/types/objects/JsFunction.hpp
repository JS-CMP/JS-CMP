#ifndef JSFUNCTION_HPP
#define JSFUNCTION_HPP

#include "types/objects/Object/JsObject.hpp"

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
    /** @brief Constructs a Function object with a callable `FunctionType`. */
    explicit Function(FunctionType f);
    /** @brief Copy constructor */
    Function(const Function& f);
    /** @brief Move constructor */
    Function(Function&& f) noexcept;
    /** @brief Copy assignment operator */
    Function& operator=(const Function& function);
    /** @brief Move assignment operator */
    Function& operator=(Function&& f) noexcept;
    ///@}

    /** @brief Destructor */
    ~Function() = default;

    /**
     * @brief Initializes the function object.
     * An empty method that can be overridden by subclasses if needed.
     */
    void init() {};
};

} // namespace JS

#endif // JSFUNCTION_HPP
