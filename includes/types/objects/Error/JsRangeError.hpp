#ifndef JSRANGEERROR_HPP
#define JSRANGEERROR_HPP

#include "internals/Object.hpp"

namespace JS {
    //
    // Right now the class error is duplicated for all different type of error, in the future it would be ideal
    // to find a way that even if the variables in getPrototypeProperties are static and that this function is called in constructors,
    // they are rewritten be inheritence or something.
    //

    /**
     * @class NartiveError
     * @brief Represents a JavaScript NativeError in C++.
     *
     * The `NativeError` class represents an NativeError in C++. it inherits from `Error` and just have a different name.
     */
    class RangeError : public JS::InternalObject {
    public:
        /**
         * @name Constructors
         * These constructors create a new Error with the given value
         */
        ///@{
        /** @brief Default constructor initializes the RangeError */
        RangeError();
        /** @brief Constructor that take a value */
        explicit RangeError(const JS::Any& value);
        /** @brief Constructor for properties */
        explicit RangeError(const std::unordered_map<std::string, JS::Attribute>& properties);
        ///@}

        /** @brief The destructor for the Error defaulted */
        ~RangeError() override = default;

        /**
         * @name Methods to make prototype methods of the Error
        */
        ///@{
        /** @brief Returns the prototype of the boolean https://262.ecma-international.org/5.1/#sec-15.7.4.2 */
        static JS::Any toString(const JS::Any& thisArg, const JS::Any& args);
        ///@}

        /**
         * @brief Static function to create the prototype properties object for an Error type
         * @param name The name of the error type (e.g., "Error", "RangeError", etc.)
         * @return A shared pointer to an InternalObject with the prototype properties
         */
        static std::shared_ptr<JS::InternalObject>& getPrototypeProperties();
    };

} // namespace JS


#endif //JSRANGEERROR_HPP
