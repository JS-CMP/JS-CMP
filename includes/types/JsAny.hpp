#ifndef JSANY_HPP
#define JSANY_HPP

#include "Types.hpp"
#include "./objects/JsObject.hpp"

namespace JS {
class Any {
public:
    Any() : value(JS::Undefined{}){};
    explicit Any(int v) : value(static_cast<double>(v)){};
    explicit Any(double v) : value(v){};
    explicit Any(Rope& v) : value(v){};
    explicit Any(Rope v) : value(v){};
    explicit Any(const std::string& v) : value(Rope(v)){};
    explicit Any(const char* v) : value(Rope(v)){};
    explicit Any(bool v) : value(v){};
    explicit Any(JS::Undefined v) : value(JS::Undefined{}){};
    explicit Any(JS::Null v) : value(JS::Null{}){};
    explicit Any(std::shared_ptr<JS::Object> v);
    explicit Any(const JS::Object& v);

    Any(const JS::Any& v);
    Any(const JS::Any&& v) noexcept;
    JS::Any& operator=(const JS::Any& other);
    JS::Any& operator=(JS::Any&& other) noexcept;

    JS::Any operator+(const JS::Any& other) const;
    JS::Any operator-(const JS::Any& other) const;
    JS::Any operator*(const JS::Any& other) const;
    JS::Any operator/(const JS::Any& other) const;
    JS::Any& operator++();
    const JS::Any& operator++(int);
    JS::Any& operator--();
    const JS::Any& operator--(int);
    bool operator<(const JS::Any& other) const;
    bool operator>(const JS::Any& other) const;
    bool operator==(const JS::Any& other) const;

    JS::Any& operator[](const std::string& key) const;
    JS::Any& operator[](size_t index) const;

    [[nodiscard]] std::string toString() const;

    friend std::ostream& operator<<(std::ostream& os, const JS::Any& any);

    template <typename... Args>
    JS::Any operator()(Args&&... args) {
        std::vector<JS::Any> arguments = { JS::Any(std::forward<Args>(args))... };
        return helper(arguments);
    }
private:
    JS::Value value;
    JS::Any helper(std::vector<JS::Any>& args) const;
};

} // namespace JS

#endif // JSANY_HPP