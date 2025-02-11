//
// Created by Simon BANDIERA on 11/02/2025.
//

#ifndef JS_CMP_JSBOOLEAN_HPP
#define JS_CMP_JSBOOLEAN_HPP

#include "internals/Object.hpp"

namespace JS {
    class Boolean : public JS::InternalObject {
        public:
        Boolean();
        explicit Boolean(const JS::Any& value);

        ~Boolean() override = default;
    };
}


#endif //JS_CMP_JSBOOLEAN_HPP
