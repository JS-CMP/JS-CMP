#ifndef JSARRAY_HPP
#define JSARRAY_HPP

#include "JsFunction.hpp"

namespace JS {
    class Array : public Object {
    public:
        Array();
        Array(const JS::Array&);
        Array(JS::Array&&) noexcept;
        ~Array() = default;

        Array& operator=(const JS::Array&);
        Array& operator=(JS::Array&&) noexcept;
        JS::Any& operator[](size_t index);

        void push(const JS::Any& value);
        size_t length() const;
        bool isCallable() const override;
    private:
        std::vector<JS::Any> elements;
    };
}

#endif // JSARRAY_HPP



//JS::Any& operator[](size_t index);
//const JS::Any& operator[](size_t index) const;
//JS::Any& operator[](int index);
//const JS::Any& operator[](int index) const;