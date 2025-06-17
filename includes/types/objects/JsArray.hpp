#ifndef JSARRAY_HPP
#define JSARRAY_HPP

#include "types/objects/JsObject.hpp"

namespace JS {

/**
 * @class Array
 * @brief Represents a JavaScript-like array object in C++.
 *
 * The `Array` class represents an array object in JavaScript. It inherits from `InternalObject`
 * and provides methods for working with arrays in a JavaScript-like syntax.
 */
class Array : public JS::InternalObject {
public:
    /**
     * @name Constructors
     * These constructors create a new Array object with the given value
     */
    ///@{
    explicit Array(const std::vector<JS::Any>& data) : JS::InternalObject({}, nullptr, u"Array", true){};
    ///@}

    [[nodiscard]] std::u16string getContent() const override;
};

} // namespace JS
#endif // JSARRAY_HPP
