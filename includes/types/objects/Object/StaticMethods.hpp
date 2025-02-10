#ifndef JS_CMP_STATICMETHODSOBJECTS_HPP
#define JS_CMP_STATICMETHODSOBJECTS_HPP

#include "types/JsAny.hpp"

namespace JS::OBJ {
    class StaticMethods {
    public:
        /**
         * @name Methods to make static methods of the Object built-in
         */
        ///@{
        /** @brief Returns the prototype of the object https://262.ecma-international.org/5.1/#sec-15.2.3.1 */
        static JS::Any getPrototypeOf(const std::vector<JS::Any>& args);
        /** @brief Returns a property descriptor of the object https://262.ecma-international.org/5.1/#sec-15.2.3.2 */
        static JS::Any getOwnPropertyDescriptor(const std::vector<JS::Any>& args);
        /** @brief Returns the property names of the object https://262.ecma-international.org/5.1/#sec-15.2.3.3 */
        static JS::Any getOwnPropertyNames(const std::vector<JS::Any>& args);
        /** @brief Creates a new object with the given prototype https://262.ecma-international.org/5.1/#sec-15.2.3.4 */
        static JS::Any create(const std::vector<JS::Any>& args);
        /** @brief Defines a property on the object https://262.ecma-international.org/5.1/#sec-15.2.3.5 */
        static JS::Any defineProperty(const std::vector<JS::Any>& args);
        /** @brief Defines multiple properties on the object https://262.ecma-international.org/5.1/#sec-15.2.3.6 */
        static JS::Any defineProperties(const std::vector<JS::Any>& args);
        /** @brief Seals the object https://262.ecma-international.org/5.1/#sec-15.2.3.7 */
        static JS::Any seal(const std::vector<JS::Any>& args);
        /** @brief Freezes the object https://262.ecma-international.org/5.1/#sec-15.2.3.8 */
        static JS::Any freeze(const std::vector<JS::Any>& args);
        /** @brief Prevents extensions on the object https://262.ecma-international.org/5.1/#sec-15.2.3.9 */
        static JS::Any preventExtensions(const std::vector<JS::Any>& args);
        /** @brief Checks if the object is sealed https://262.ecma-international.org/5.1/#sec-15.2.3.10 */
        static JS::Any isSealed(const std::vector<JS::Any>& args);
        /** @brief Checks if the object is frozen https://262.ecma-international.org/5.1/#sec-15.2.3.11 */
        static JS::Any isFrozen(const std::vector<JS::Any>& args);
        /** @brief Checks if the object is extensible https://262.ecma-international.org/5.1/#sec-15.2.3.12 */
        static JS::Any isExtensible(const std::vector<JS::Any>& args);
        /** @brief Returns the keys of the object https://262.ecma-international.org/5.1/#sec-15.2.3.13 */
        static JS::Any keys(const std::vector<JS::Any>& args);
        ///@}
    };
}

#endif //JS_CMP_STATICMETHODSOBJECTS_HPP
