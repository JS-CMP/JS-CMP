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

    /** @brief Returns the content of the object formatted to a string. */
    [[nodiscard]] std::u16string getContent() const override;

    /**
     * @name Methods that represent the functions needed for calling and constructing
     */
    ///@{
    /** @brief Function that represent the constructor of the Object */
    static Any internal_constructor(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Function that is used when object is call as a function */
    static Any internal_call(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    std::shared_ptr<JS::InternalObject> targetFunction;
    JS::Any boundThis;
    std::vector<JS::Any> boundArguments;
};
} // namespace JS

#endif // JSFUNCTIONBINDED_HPP