#ifndef JS_CMP_JSBOOLEAN_HPP
#define JS_CMP_JSBOOLEAN_HPP

#include "internals/Object.hpp"

namespace JS {
    class Boolean : public JS::InternalObject {
        public:
        Boolean();
        explicit Boolean(const JS::Any& value);

        ~Boolean() override = default;

        static JS::Any toString(const std::vector<JS::Any>& args);
        static JS::Any valueOf(const std::vector<JS::Any>& args);

        static std::shared_ptr<JS::InternalObject> &getPrototypeProperties();
    };
}


#endif //JS_CMP_JSBOOLEAN_HPP
