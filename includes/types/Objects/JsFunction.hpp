#ifndef JSFUNCTION_HPP
#define JSFUNCTION_HPP

#include "JsObject.hpp"

namespace JS {
    class Function : public Object {
        public:
            explicit Function(FunctionType function);

            template <typename... Args>
            JS::Any operator()(Args... args) {
                return function(args...);
            }

            [[nodiscard]] bool isCallable() const override;
        private:
            FunctionType function;
    };
}

#endif
