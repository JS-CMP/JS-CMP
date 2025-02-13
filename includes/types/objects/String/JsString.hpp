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
        explicit String(const JS::Any& value);
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

        /**
         * @name Prototype methods of the String object built-in
         */
        ///@{
        static JS::Any toString(const std::vector<JS::Any>& args);
        static JS::Any valueOf(const std::vector<JS::Any>& args);
        static JS::Any charAt(const std::vector<JS::Any>& args);
        static JS::Any charCodeAt(const std::vector<JS::Any>& args);
        static JS::Any concat(const std::vector<JS::Any>& args);
        static JS::Any indexOf(const std::vector<JS::Any>& args);
        static JS::Any lastIndexOf(const std::vector<JS::Any>& args);
        static JS::Any localeCompare(const std::vector<JS::Any>& args);
        static JS::Any match(const std::vector<JS::Any>& args);
        static JS::Any replace(const std::vector<JS::Any>& args);
        static JS::Any search(const std::vector<JS::Any>& args);
        static JS::Any slice(const std::vector<JS::Any>& args);
        static JS::Any split(const std::vector<JS::Any>& args);
        static JS::Any substring(const std::vector<JS::Any>& args);
        static JS::Any toLowerCase(const std::vector<JS::Any>& args);
        static JS::Any toLocaleLowerCase(const std::vector<JS::Any>& args);
        static JS::Any toUpperCase(const std::vector<JS::Any>& args);
        static JS::Any toLocaleUpperCase(const std::vector<JS::Any>& args);
        static JS::Any trim(const std::vector<JS::Any>& args);
        ///@}

        /**
         * @name Static methods of the String object built-in
         */
        ///@{
        [[nodiscard]] static JS::Any fromCharCode(const std::vector<JS::Any>& args);
        ///@}

        static std::shared_ptr<JS::InternalObject> &getPrototypeProperties();
    };
}


#endif //JS_CMP_JSSTRING_HPP
