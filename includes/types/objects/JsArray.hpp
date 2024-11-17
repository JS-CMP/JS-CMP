#ifndef JSARRAY_HPP
#define JSARRAY_HPP

#include "JsFunction.hpp"

namespace JS {
    class Array : public Object, public std::enable_shared_from_this<Array> {
    public:
        Array();
        Array(const JS::Array&);
        Array(JS::Array&&) noexcept;
        Array& operator=(const JS::Array&);
        Array& operator=(JS::Array&&) noexcept;

        ~Array() override = default;

        JS::Any& operator[](size_t index) override;
        JS::Any& operator[](const std::string& key) override;

        void push(const JS::Any& value);
        [[nodiscard]] bool isCallable() const override;
        void init() override;
    private:
        std::shared_ptr<std::vector<JS::Any>> elements;
    };
}

#endif // JSARRAY_HPP



//JS::Any& operator[](size_t index);
//const JS::Any& operator[](size_t index) const;
//JS::Any& operator[](int index);
//const JS::Any& operator[](int index) const;