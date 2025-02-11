#ifndef JS_CMP_STATICMETHODSSTRING_HPP
#define JS_CMP_STATICMETHODSSTRING_HPP

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


#endif //JS_CMP_STATICMETHODSSTRING_HPP
