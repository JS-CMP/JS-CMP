#ifndef JSANY_HPP
#define JSANY_HPP

#include "../class/Rope/Rope.hpp"

#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <variant>

namespace JS {
enum Types { NUMBER, STRING, BOOL, FUNCTION, UNDEFINED, NULL_TYPE };

class Any;

using Function = std::function<JS::Any(const std::vector<JS::Any>&)>;
using Object = std::unordered_map<std::string, std::shared_ptr<JS::Any>>;
using Null = std::nullptr_t;
struct Undefined {};
using Null = std::nullptr_t;

using Value = std::variant<double, Rope, bool, JS::Function, JS::Undefined, JS::Null>;

class Any {
private:
    JS::Value value;

public:
    Any() : value(JS::Undefined{}){};
    explicit Any(int v) : value(static_cast<double>(v)){};
    explicit Any(double v) : value(v){};
    explicit Any(Rope& v) : value(v){};
    explicit Any(Rope v) : value(v){};
    explicit Any(const std::string& v) : value(Rope(v)){};
    explicit Any(const char* v) : value(Rope(v)){};
    explicit Any(bool v) : value(v){};
    explicit Any(JS::Function v) : value(v){};
    explicit Any(JS::Undefined v) : value(JS::Undefined{}){};
    explicit Any(JS::Null v) : value(JS::Null{}){};

    JS::Any operator+(const JS::Any& other) const;
    JS::Any operator+(int value) const;
    JS::Any operator+(double value) const;
    JS::Any operator+(std::string value) const;
    JS::Any operator+(bool value) const;
    JS::Any operator+(JS::Null) const;
    JS::Any operator+(JS::Undefined) const;
    friend JS::Any operator+(int value, JS::Any const & any);
    friend JS::Any operator+(double value, JS::Any const & any);
    friend JS::Any operator+(std::string value, JS::Any const & any);
    friend JS::Any operator+(bool value, JS::Any const & any);
    friend JS::Any operator+(JS::Null value, JS::Any const & any);
    friend JS::Any operator+(JS::Undefined value, JS::Any const & any);

    JS::Any operator-(const JS::Any& other) const;
    JS::Any operator-(int value) const;
    JS::Any operator-(double value) const;
    JS::Any operator-(std::string value) const;
    JS::Any operator-(bool value) const;
    JS::Any operator-(JS::Null) const;
    JS::Any operator-(JS::Undefined) const;
    friend JS::Any operator-(int value, JS::Any const & any);
    friend JS::Any operator-(double value, JS::Any const & any);
    friend JS::Any operator-(std::string value, JS::Any const & any);
    friend JS::Any operator-(bool value, JS::Any const & any);
    friend JS::Any operator-(JS::Null value, JS::Any const & any);
    friend JS::Any operator-(JS::Undefined value, JS::Any const & any);

    JS::Any operator*(const JS::Any& other) const;
    JS::Any operator*(int value) const;
    JS::Any operator*(double value) const;
    JS::Any operator*(std::string value) const;
    JS::Any operator*(bool value) const;
    JS::Any operator*(JS::Null) const;
    JS::Any operator*(JS::Undefined) const;
    friend JS::Any operator*(int value, JS::Any const & any);
    friend JS::Any operator*(double value, JS::Any const & any);
    friend JS::Any operator*(std::string value, JS::Any const & any);
    friend JS::Any operator*(bool value, JS::Any const & any);
    friend JS::Any operator*(JS::Null value, JS::Any const & any);
    friend JS::Any operator*(JS::Undefined value, JS::Any const & any);

    JS::Any operator/(const JS::Any& other) const;
    JS::Any operator/(int value) const;
    JS::Any operator/(double value) const;
    JS::Any operator/(std::string value) const;
    JS::Any operator/(bool value) const;
    JS::Any operator/(JS::Null) const;
    JS::Any operator/(JS::Undefined) const;
    friend JS::Any operator/(int value, JS::Any const & any);
    friend JS::Any operator/(double value, JS::Any const & any);
    friend JS::Any operator/(std::string value, JS::Any const & any);
    friend JS::Any operator/(bool value, JS::Any const & any);
    friend JS::Any operator/(JS::Null value, JS::Any const & any);
    friend JS::Any operator/(JS::Undefined value, JS::Any const & any);

    JS::Any operator%(const JS::Any& other) const;
    JS::Any operator%(int value) const;
    JS::Any operator%(double value) const;
    JS::Any operator%(std::string value) const;
    JS::Any operator%(bool value) const;
    JS::Any operator%(JS::Null) const;
    JS::Any operator%(JS::Undefined) const;
    friend JS::Any operator%(int value, JS::Any const & any);
    friend JS::Any operator%(double value, JS::Any const & any);
    friend JS::Any operator%(std::string value, JS::Any const & any);
    friend JS::Any operator%(bool value, JS::Any const & any);
    friend JS::Any operator%(JS::Null value, JS::Any const & any);
    friend JS::Any operator%(JS::Undefined value, JS::Any const & any);

    JS::Any& operator++(); // ++a
    const JS::Any& operator++(int);
    JS::Any& operator--();
    const JS::Any& operator--(int);

    bool operator<(const JS::Any& other) const;
    bool operator>(const JS::Any& other) const;
    bool operator==(const JS::Any& other) const;
    JS::Any operator()(std::vector<JS::Any>& args);

    [[nodiscard]] JS::Value getValue() const;
    [[nodiscard]] std::string toString() const;

    friend std::ostream& operator<<(std::ostream& os, const JS::Any& any);
};

} // namespace JS

#endif // JSANY_HPP