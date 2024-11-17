#ifndef JSFUNCTION_HPP
#define JSFUNCTION_HPP

#include "JsObject.hpp"


namespace JS {
    class Function : public Object {
        public:
            explicit Function(FunctionType f);
            explicit Function(Function& f);
            explicit Function(Function&& f) noexcept;
            Function& operator=(const Function& function);
            Function& operator=(Function&& f) noexcept;
            ~Function() = default;

            template <typename... Args>
            JS::Any operator()(Args... args) {
                return function(args...);
            }

            void init() override {};
            [[nodiscard]] bool isCallable() const override;
        private:
            FunctionType function;
    };
}

#endif
