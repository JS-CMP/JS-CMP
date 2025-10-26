#ifndef PROPERTIESPROXY_HPP
#define PROPERTIESPROXY_HPP
#include "internals/Arguments.hpp"
#include "types/JsAny.hpp"
#include "types/Types.hpp"

namespace JS {
/**
 * @class PropertyProxy
 * @brief Represents a proxy for accessing properties of an object in JavaScript.
 *
 * The `PropertyProxy` class allows you to access and manipulate properties of a JavaScript-like object
 * using C++ syntax. It provides methods to get and set property values, as well as to call functions
 * stored in properties.
 */
class PropertyProxy : public Operator {
public:
    PropertyProxy(const std::shared_ptr<JS::InternalObject>& obj, std::u16string key) : obj_(obj), key_(std::move(key)) {}
    /** @name Getters and Setters
     * These operators allow the PropertyProxy to be used like a property
     */
    ///@{
    /** @brief Set the value of the property */
    PropertyProxy& operator=(const JS::Any& value);
    /** @brief Get the value of the property */
    operator JS::Any(); // NOLINT(hicpp-explicit-conversions)
    /** @brief Get the value of the property */
    operator JS::Any() const; // NOLINT(hicpp-explicit-conversions)
    ///@}

    /**
     * @name Accessors
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Accessors to call function stored in properties on an object stored in value */
    template <typename... Args>
    JS::Any operator()(Args&&... args) {
        return call(JS::Arguments::CreateArgumentsObject(std::vector<JS::Any>{std::move(args)...}));
    }
    ///@}

    /** @brief Override the call operator to add obj_ as the this argument */
    JS::Any call(const JS::Any& args) const override;

    /** @name Getters
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Get the value of the property */
    JS::Any& get() override;
    /** @brief Get the value of the property */
    JS::Any get() const override;
    /** @brief Get the value of the property */
    JS::Value getValue() const override;
    ///@}

    /** @name Setters
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Set the value of the property */
    void set(const JS::Any& value) override;
    /** @brief Set the value of the property */
    void setValue(const JS::Value& value) override;
    ///@}

private:
    std::shared_ptr<JS::InternalObject> obj_;
    std::u16string key_;
};
} // namespace JS
#endif // PROPERTIESPROXY_HPP
