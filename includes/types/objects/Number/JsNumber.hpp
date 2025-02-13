//
// Created by Simon BANDIERA on 11/02/2025.
//

#ifndef JS_CMP_JSNUMBER_HPP
#define JS_CMP_JSNUMBER_HPP

#include "internals/Object.hpp"

namespace JS {
class Number : public JS::InternalObject {
    public:
        Number();
        explicit Number(const JS::Any& value);
        explicit Number(const std::unordered_map<std::string, JS::Attribute>& properties);

        ~Number() override = default;
    };
}


#endif //JS_CMP_JSNUMBER_HPP
