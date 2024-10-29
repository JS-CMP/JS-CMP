#ifndef JSANY_HPP
#define JSANY_HPP

#include <iostream>
#include <functional>
#include <memory>
#include <variant>
#include <limits>
#include "Types.hpp"

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

namespace JS {
    class Any {
    private:
        JS::Value value;
    public:
        Any();
        explicit Any(int v);
        explicit Any(double v);
        explicit Any(const std::string& v);
        explicit Any(const char* v);
        explicit Any(bool v);
        explicit Any(JS::Function v);
        explicit Any(JS::Undefined v);
        explicit Any(JS::Null v);
        explicit Any(const JS::Object& v);


        JS::Any operator+(const JS::Any& other) const;
        JS::Any operator-(const JS::Any& other) const;
        JS::Any operator*(const JS::Any& other) const;
        JS::Any operator/(const JS::Any& other) const;
        JS::Any &operator++();
        JS::Any &operator++(int);
        JS::Any &operator--();
        JS::Any &operator--(int);
        bool operator<(const JS::Any &other) const;
        bool operator>(const JS::Any& other) const;
        bool operator==(const JS::Any& other) const;

        JS::Any& operator[](const std::string& key);
        const JS::Any& operator[](const std::string& key) const;
        JS::Any& operator[](const char* key);
        const JS::Any& operator[](const char* key) const;
        JS::Any& operator[](size_t index);
        const JS::Any& operator[](size_t index) const;
        JS::Any& operator[](int index);
        const JS::Any& operator[](int index) const;

        JS::Any operator()(std::vector<JS::Any>& args);
        [[nodiscard]] std::string toString() const;

        friend std::ostream& operator<<(std::ostream& os, const JS::Any& any);
    };
}

#endif //JSANY_HPP
