//
// Created by Simon BANDIERA on 07/02/2025.
//

#ifndef JS_CMP_PROTOTYPEMETHODS_HPP
#define JS_CMP_PROTOTYPEMETHODS_HPP

#include "types/JsAny.hpp"

namespace JS::STR {
    class PrototypeMethods {
        public:
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
    };
}


#endif //JS_CMP_PROTOTYPEMETHODS_HPP
