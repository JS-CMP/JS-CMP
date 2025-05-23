#ifndef JSFUNCTIONBINDED_HPP
#define JSFUNCTIONBINDED_HPP

#include "JsFunction.hpp"

namespace JS {

/**
 * @class FunctionBinded
 * @brief Represents a binded function object in C++. This class is a subclass of Function
 *
 * The `FunctionBinded` class encapsulates a Function object that has been binded to a specific object. It allows to
 * store boundArguments, boundThis and the original function.
 */
class FunctionBinded : public JS::Function {
public:
    /**
     * @name Constructors
     * These constructors create a new FunctionBinded object.
     */
    ///@{
    /** @brief Default constructor initializes the object with an empty map */
    FunctionBinded(const std::shared_ptr<JS::InternalObject>& TargetFunction, const JS::Any& BoundThis,
                   const std::vector<JS::Any>& BoundArguments);
    /** @brief Copy constructor */
    FunctionBinded(const FunctionBinded& f);
    /** @brief Move constructor */
    FunctionBinded(FunctionBinded&& f) noexcept;
    /** @brief Copy assignment operator */
    FunctionBinded& operator=(const FunctionBinded& function) = default;
    /** @brief Move assignment operator */
    FunctionBinded& operator=(FunctionBinded&& f) noexcept;
    ///@}

    /** @brief Destructor */
    ~FunctionBinded() override = default;

    /**
     * @name Internal Properties Overriden from Function
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Check if the object is an instance of another object */
    [[nodiscard]] bool hasInstance(const JS::Any& value) const final;
    ///@}

    std::shared_ptr<JS::InternalObject> targetFunction;
    JS::Any boundThis;
    std::vector<JS::Any> boundArguments;
};
} // namespace JS

#endif // JSFUNCTIONBINDED_HPP