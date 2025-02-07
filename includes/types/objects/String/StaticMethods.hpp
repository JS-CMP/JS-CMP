//
// Created by Simon BANDIERA on 07/02/2025.
//

#ifndef JS_CMP_STATICMETHODS_HPP
#define JS_CMP_STATICMETHODS_HPP

#include "types/JsAny.hpp"

namespace JS::STR {
    class StaticMethods {
    public:
        /**
         * @name Static methods of the String object built-in
         */
        ///@{
        [[nodiscard]] static JS::Any fromCharCode(const std::vector<JS::Any>& args);
        ///@}
    };
}

#endif //JS_CMP_STATICMETHODS_HPP
