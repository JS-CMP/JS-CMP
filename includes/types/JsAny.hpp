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
    class Any;

    using Function = std::function<JS::Any(const std::vector<JS::Any>&)>;
    using Object = std::unordered_map<std::string, std::shared_ptr<JS::Any>>;
    using Null = std::nullptr_t;
    struct Undefined {};
    using Null = std::nullptr_t;


    using Value = std::variant<double, std::string, bool, JS::Function, JS::Undefined, JS::Null>;

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
        explicit Any(JS::Undefined v) : value(JS::Undefined{}) {}
        explicit Any(JS::Null v) : value(JS::Null{}) {}


        JS::Any operator+(const JS::Any& other) const;
        JS::Any operator-(const JS::Any& other) const;
        JS::Any operator*(const JS::Any& other) const;
        JS::Any operator/(const JS::Any& other) const;
        JS::Any &operator++();
        const JS::Any &operator++(int);
        JS::Any &operator--();
        const JS::Any &operator--(int);
        inline bool operator<(const JS::Any &other) const
        {
            try {
                return std::visit(overloaded{
                    // types
                    [](double lhs, double rhs) {
                        return lhs < rhs;
                    },
                    [](const std::string &lhs, const std::string &rhs) {
                        return lhs.compare(rhs) < 0;
                    },
                    [this, other](JS::Function &lhs, JS::Function &rhs) {
                        return this->toString().compare(other.toString()) < 0;
                    },
                    [](bool lhs, bool rhs) {
                        return lhs < rhs;
                    },

                    // double
                    [](double lhs, const std::string &rhs) {
                        return lhs < std::stod(rhs);
                    },
                    [](double lhs, bool rhs) {
                        return static_cast<long long int>(lhs) < rhs;
                    },
                    [](double lhs, JS::Null rhs) {
                        return static_cast<long long int>(lhs) < 0;
                    },

                    // string
                    [](const std::string &lhs, double rhs) {
                        return std::stod(lhs) < rhs;
                    },
                    [](const std::string &lhs, bool rhs) {
                        return static_cast<long long int>(std::stod(lhs)) < rhs;
                    },
                    [other](const std::string &lhs, JS::Function &rhs) {
                        return lhs.compare(other.toString()) < 0;
                    },

                    // bool
                    [](bool lhs, double rhs) {
                        return lhs < static_cast<long long int>(rhs);
                    },
                    [](bool lhs, const std::string &rhs) {
                        return lhs < static_cast<long long int>(std::stod(rhs));
                    },

                    // function

                    // undefined

                    // null
                    [](JS::Null lhs, double rhs) {
                        return 0.0 < rhs;
                    },
                    [](JS::Null lhs, const std::string &rhs) {
                        return 0.0 < std::stod(rhs);
                    },
                    [](JS::Null lhs, bool rhs) {
                        return false < rhs;
                    },
                    // default
                    [](const auto &, const auto &) {return false;}
                }, value, other.value);
            } catch (std::invalid_argument &e) {
                return false;
            }
        }
        bool operator>(const JS::Any& other) const;
        bool operator==(const JS::Any& other) const;
        JS::Any operator()(std::vector<JS::Any>& args);
        [[nodiscard]] std::string toString() const;

        friend std::ostream& operator<<(std::ostream& os, const JS::Any& any);
    };
}

#endif //JSANY_HPP
