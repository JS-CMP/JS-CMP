#ifndef JSFUNCTION_HPP
#define JSFUNCTION_HPP

#include "JsObject.hpp"

namespace JS {

/**
 * @class Function
 * @brief Represents a JavaScript-like function object in C++.
 *
 * The `Function` class encapsulates a callable entity, allowing it to store
 * and invoke a function. This class provides a JavaScript-inspired interface,
 * enabling function calls with various arguments.
 */
class Function : public Object {
public:
    /**
     * @name Constructors
     * These constructors create a new Function object.
     */
    ///@{
    /** @brief Constructs a Function object with a callable `FunctionType`. */
    explicit Function(FunctionType f);
    /** @brief Copy constructor */
    explicit Function(Function& f);
    /** @brief Move constructor */
    explicit Function(Function&& f) noexcept;
    /** @brief Copy assignment operator */
    Function& operator=(const Function& function);
    /** @brief Move assignment operator */
    Function& operator=(Function&& f) noexcept;
    ///@}

    /** @brief Destructor */
    ~Function() = default;

    /**
     * @brief Invokes the function with the specified arguments.
     * @tparam Args Argument types.
     * @param args Arguments to pass to the function.
     * @return Result of the function call as a `JS::Any` object.
     */
    template <typename... Args>
    JS::Any operator()(Args... args) {
        return function(args...);
    }

    /**
     * @brief Initializes the function object.
     * An empty method that can be overridden by subclasses if needed.
     */
    void init() override {};

    /**
     * @brief Checks if the object is callable.
     * @return `true` since Function objects are callable by definition.
     */
    [[nodiscard]] bool isCallable() const override;

private:
    FunctionType function; /**< Holds the callable function entity. */
};

} // namespace JS

#endif // JSFUNCTION_HPP
