#ifndef JSANY_HPP
#define JSANY_HPP

#include <iostream>
#include <functional>
#include <memory>
#include <variant>
#include <limits>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

namespace JS {
    enum Types {
        NUMBER,
        STRING,
        BOOL,
        FUNCTION,
        UNDEFINED,
        NULL_TYPE
    };

    class Any;

    using Function = std::function<JS::Any(const std::vector<JS::Any>&)>;
    using Object = std::unordered_map<std::string, std::shared_ptr<JS::Any>>;
    using Null = std::nullptr_t;
    struct Undefined {};
    using Null = std::nullptr_t;


    using Value = std::variant<double, std::string, bool, JS::Function, JS::Undefined, JS::Null>;
    // value.index()
    //
    // double : 0
    // string : 1
    // bool : 2
    // function : 3
    // undefined : 4
    // null : 5

    class Any {
    private:
        JS::Value value;
    public:

        Any() : value(JS::Undefined{}) {}
        explicit Any(int v) : value(static_cast<double>(v)) {}
        explicit Any(double v) : value(v) {}
        explicit Any(const std::string& v) : value(v) {}
        explicit Any(const char* v) : value(std::string(v)) {}
        explicit Any(bool v) : value(v) {}
        explicit Any(JS::Function v) : value(v) {}
        explicit Any(JS::Undefined) : value(JS::Undefined{}) {}
        explicit Any(JS::Null) : value(JS::Null{}) {}


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
        JS::Any operator()(std::vector<JS::Any>& args);
        [[nodiscard]] std::string toString() const;

        friend std::ostream& operator<<(std::ostream& os, const JS::Any& any);
    };
}

#endif //JSANY_HPP
