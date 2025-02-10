#ifndef JS_CMP_PROTOTYPEMETHODSSTRING_HPP
#define JS_CMP_PROTOTYPEMETHODSSTRING_HPP

#include "types/Types.hpp"

namespace JS::OBJ {
    class PrototypeMethods {
        public:
        /**
        * @name Methods to make prototype methods of the Object built-in
        */
        ///@{
        /** @brief Returns the prototype of the object https://262.ecma-international.org/5.1/#sec-15.2.4.2 */
        static JS::Any toString(const std::vector<JS::Any>& args);
        /** @brief Returns the locale string of it https://262.ecma-international.org/5.1/#sec-15.2.4.3 */
        static JS::Any toLocaleString(const std::vector<JS::Any>& args);
        /** @brief Returns the value of the object https://262.ecma-international.org/5.1/#sec-15.2.4.4 */
        static JS::Any valueOf(const std::vector<JS::Any>& args);
        /** @brief Returns if the object has a property https://262.ecma-international.org/5.1/#sec-15.2.4.5 */
        static JS::Any hasOwnProperty(const std::vector<JS::Any>& args);
        /** @brief Returns if the object is in the prototype chain https://262.ecma-international.org/5.1/#sec-15.2.4.6 */
        static JS::Any isPrototypeOf(const std::vector<JS::Any>& args);
        /** @brief Returns if the property is enumerable https://262.ecma-international.org/5.1/#sec-15.2.4.7 */
        static JS::Any propertyIsEnumerable(const std::vector<JS::Any>& args);
        ///@}
    };

}

#endif //JS_CMP_PROTOTYPEMETHODSSTRING_HPP
