#ifndef JSARRAY_HPP
#define JSARRAY_HPP

#include "Types.hpp"
#include "JsObject.hpp"

namespace JS {
    class Array : public Object {


    public:
        Array();
        Array(const JS::Array&);
        Array& operator=(const JS::Array&);
        Array(JS::Array&&) noexcept;
        Array& operator=(JS::Array&&) noexcept;

        JS::Any& operator[](size_t index);
        const JS::Any& operator[](size_t index) const;
        JS::Any& operator[](int index);
        const JS::Any& operator[](int index) const;


        void push(const JS::Any& value);
        size_t length() const;
    private:
        void init();

        std::vector<JS::Any> elements;
    };
}

#endif // JSARRAY_HPP
