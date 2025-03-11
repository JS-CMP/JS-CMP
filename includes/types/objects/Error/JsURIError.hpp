#ifndef JSURIERROR_HPP
#define JSURIERROR_HPP

#include "internals/Object.hpp"

namespace JS {
    //
    // Right now the class error is duplicated for all different type of error, in the future it would be ideal
    // to find a way that even if the variables in getPrototypeProperties are static and that this function is called in constructors,
    // they are rewritten be inheritence or something.
    //

    /**
     * @class NartiveError
     * @brief Represents a JavaScript UriError in C++.
     *
     * The `UriError` class represents an UriError in C++. it inherits from `Error` and just have a different name.
     */
    class UriError : public JS::InternalObject {
    public:
        /**
         * @name Constructors
         * These constructors create a new Error with the given value
         */
        ///@{
        /** @brief Default constructor initializes the UriError */
        UriError();
        /** @brief Constructor that take a value */
        explicit UriError(const JS::Any& value);
        /** @brief Constructor for properties */
        explicit UriError(const std::unordered_map<std::string, JS::Attribute>& properties);
        ///@}

        /** @brief The destructor for the Error defaulted */
        ~UriError() override = default;

        /**
         * @name Methods to make prototype methods of the Error
        */
        ///@{
        /** @brief Returns the prototype of the boolean https://262.ecma-international.org/5.1/#sec-15.7.4.2 */
        static JS::Any toString(const JS::Any& thisArg, const JS::Any& args);
        ///@}

        /**
         * @brief Static function to create the prototype properties object for an Error type
         * @param name The name of the error type (e.g., "Error", "UriError", etc.)
         * @return A shared pointer to an InternalObject with the prototype properties
         */
        static std::shared_ptr<JS::InternalObject>& getPrototypeProperties();
    };

} // namespace JS


#endif //JSURIERROR_HPP
