//
// Created by Simon BANDIERA on 06/02/2025.
//

#ifndef JS_CMP_JSSTRING_HPP
#define JS_CMP_JSSTRING_HPP

#include "internals/Attribute.hpp"
#include "internals/Object.hpp"
#include "internals/PropertyProxy.hpp"
#include "utils/Convert.hpp"

namespace JS {
    class String : public JS::InternalObject {
    public:
        /**
         * @name Constructors
         * These constructors create a new String object with the given value
         */
        ///@{
        /** @brief Default constructor initializes the object with an empty map */
        String();
        explicit String(JS::Any value);
        /** @brief Constructor for properties */
        explicit String(const std::unordered_map<std::string, JS::Any>& properties);
        ///@}

        /**
         * @brief The destructor for the object defaulted
         */
        ~String() override = default;

        /**
         * @name Methods that override internal methods of the Object
         */
        ///@{
        [[nodiscard]] std::optional<JS::Attribute> getOwnProperty(const std::string& key) const final;
        ///@}
    };
}


#endif //JS_CMP_JSSTRING_HPP
