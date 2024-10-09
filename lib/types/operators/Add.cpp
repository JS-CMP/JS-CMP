#include "../../../includes/types/JsAny.hpp"

JS::Any JS::Any::operator+(const JS::Any &other) const
{
    return std::visit(overloaded{
        // types
        [](double lhs, double rhs) {
            return JS::Any(lhs + rhs);
        },
        [](const std::string &lhs, const std::string &rhs) {
            return JS::Any(lhs + rhs);
        },
        [](bool lhs, bool rhs) {
            return JS::Any(lhs + rhs);
        },
        [this, other](JS::Function &lhs, JS::Function &rhs) {
            return JS::Any(this->toString() + other.toString());
        },
        [](JS::Undefined &lhs, JS::Undefined &rhs) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        },
        [](JS::Null &lhs, JS::Null &rhs) {
            return JS::Any(0);
        },

        // double
        [this](double lhs, const std::string &rhs) {
            return JS::Any(this->toString() + rhs);
        },
        [](double lhs, bool rhs) {
            return JS::Any(lhs + rhs);
        },
        [this, other](double lhs, JS::Function &rhs) {
            return JS::Any(this->toString() + other.toString());
        },
        [](double lhs, JS::Undefined rhs) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        },
        [](double lhs, JS::Null rhs) {
            return JS::Any(lhs);
        },

        // string
        [other](const std::string &lhs, double rhs) {
            return JS::Any(lhs + other.toString());
        },
        [other](const std::string &lhs, bool rhs) {
            return JS::Any(lhs + other.toString());
        },
        [other](const std::string &lhs, JS::Function &rhs) {
            return JS::Any(lhs + other.toString());
        },
        [other](const std::string &lhs, JS::Undefined rhs) {
            return JS::Any(lhs + other.toString());
        },
        [other](const std::string &lhs, JS::Null rhs) {
            return JS::Any(lhs + other.toString());
        },

        // bool
        [](bool lhs, double rhs) {
            return JS::Any(lhs + rhs);
        },
        [this](bool lhs, const std::string &rhs) {
            return JS::Any(this->toString() + rhs);
        },
        [this, other](bool lhs, JS::Function &rhs) {
            return JS::Any(this->toString() + other.toString());
        },
        [this, other](bool lhs, JS::Undefined rhs) {
            return JS::Any(this->toString() + other.toString());
        },
        [](bool lhs, JS::Null rhs) {return JS::Any(static_cast<double>(lhs));},

        // function
        [this, other](JS::Function &lhs, double rhs) {
            return JS::Any(this->toString() + other.toString());
        },
        [this](JS::Function &lhs, const std::string &rhs) {
            return JS::Any(this->toString() + rhs);
        },
        [this, other](JS::Function &lhs, bool rhs) {
            return JS::Any(this->toString() + other.toString());
        },
        [this, other](JS::Function &lhs, JS::Undefined rhs) {
            return JS::Any(this->toString() + other.toString());
        },
        [this, other](JS::Function &lhs, JS::Null rhs) {
            return JS::Any(this->toString() + other.toString());
        },

        // undefined
        [](JS::Undefined lhs, double rhs) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        },
        [this](JS::Undefined lhs, const std::string &rhs) {
            return JS::Any(this->toString() + rhs);
        },
        [](JS::Undefined lhs, bool rhs) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        },
        [this, other](JS::Undefined lhs, JS::Function &rhs) {
            return JS::Any(this->toString() + other.toString());
        },
        [](JS::Undefined lhs, JS::Null rhs) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        },

        // null
        [](JS::Null lhs, double rhs) {
            return JS::Any(rhs);
        },
        [this](JS::Null lhs, const std::string &rhs) {
            return JS::Any(this->toString() + rhs);
        },
        [](JS::Null lhs, bool rhs) {
            return JS::Any(static_cast<double>(rhs));
        },
        [this, other](JS::Null lhs, JS::Function &rhs) {
            return JS::Any(this->toString() + other.toString());
        },
        [](JS::Null lhs, JS::Undefined rhs) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        },

        // default
        [](const auto &, const auto &) {return JS::Any();}
    }, value, other.value);
}