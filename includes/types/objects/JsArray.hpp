#ifndef JSARRAY_HPP
#define JSARRAY_HPP

#include "JsFunction.hpp"

namespace JS {

/**
 * @class Array
 * @brief Represents a JavaScript-like array object in C++.
 *
 * The `Array` class simulates JavaScript arrays, allowing elements to be accessed
 * by index and providing methods for modifying the array. It inherits from `Object`
 * and supports shared ownership.
 */
class Array : public Object, public std::enable_shared_from_this<Array> {
public:
    /**
     * @name Constructors
     * These constructors create a new Array object.
     */
    ///@{
    /** @brief Default constructor creates an empty Array. */
    Array();
    /** @brief Copy constructor */
    Array(const JS::Array&);
    /** @brief Move constructor */
    Array(JS::Array&&) noexcept;
    /** @brief Copy assignment operator */
    Array& operator=(const JS::Array&);
    /** @brief Move assignment operator */
    Array& operator=(JS::Array&&) noexcept;
    ///@}

    /** @brief Destructor */
    ~Array() override = default;

    /**
     * @brief Accesses an element by index, expanding the array if necessary.
     * @param index Index of the element.
     * @return Reference to the `JS::Any` element at the specified index.
     */
    JS::Any operator[](size_t index) override;

    /**
     * @brief Accesses an element by a string key.
     * Used for named properties on the array object.
     * @param key String key of the element.
     * @return Reference to the `JS::Any` element associated with the key.
     */
    JS::Any operator[](const std::string& key) override;

    /**
     * @brief Adds a new element to the end of the array.
     * @param value The value to add.
     */
    void push(const JS::Any& value);

    /**
     * @brief Checks if the object is callable.
     * @return `false` as arrays are not callable.
     */
    [[nodiscard]] bool isCallable() const override;

    /**
     * @brief Initializes the array, setting up properties and methods.
     */
    void init() override;

private:
    std::shared_ptr<std::vector<JS::Any>> elements; /**< Holds the elements of the array. */
};

} // namespace JS

#endif // JSARRAY_HPP
