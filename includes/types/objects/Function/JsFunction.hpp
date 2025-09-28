#ifndef JSFUNCTION_HPP
#define JSFUNCTION_HPP

#include "types/objects/JsObject.hpp"

#define DEFAULT_FCT [](const JS::Any&, const JS::Any&) -> JS::Any { return JS::Any(std::make_shared<JS::Object>()); }

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
    explicit Function(FunctionType f = DEFAULT_FCT, int length = 0, const std::u16string& name = u"Anonymous");
    /** @brief Constructs a Function object with a callable `FunctionType` and explicit prototype. */
    explicit Function(FunctionType f, int length, const std::u16string& name, const std::shared_ptr<InternalObject>& prototype);
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

    /** @brief Returns the content of the object formatted to a string. */
    [[nodiscard]] std::u16string getContent() const override;

    /** @brief Function to get the methods of the property prototype */
    static std::shared_ptr<JS::InternalObject>& getPrototypeProperties(const std::shared_ptr<JS::InternalObject>& constructor = nullptr);

    /** @brief Function to get the methods of the property constructor by copying */
    static std::shared_ptr<JS::InternalObject> getPrototypePropertiesCopy(std::shared_ptr<JS::InternalObject> constructor,std::shared_ptr<JS::InternalObject> prototype = nullptr);

    /**
     * @name Methods that represent the functions needed for calling and constructing
     */
    ///@{
    /** @brief Function that represent the constructor of the Object */
    static Any internal_constructor(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Function that is used when object is call as a function */
    static Any internal_call(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /**
     * @name Internal Utility Methods
     */
    ///@{
    /** @brief Get the instance of the function object. */
    [[nodiscard]] static std::shared_ptr<JS::Function> getConstructor();
    /** @brief Override of the Internal object method. */
    void initialize() override;
    ///@}

};

} // namespace JS

#endif // JSFUNCTION_HPP
