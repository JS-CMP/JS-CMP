#include "../../../includes/types/JsAny.hpp"

JS::Any JS::Any::operator*(const JS::Any &other) const
{
    // TODO: change with infinite precision the stol
    try {
        return std::visit(overloaded{
            // types
            [](double lhs, double rhs) {
                return JS::Any(lhs * rhs);
            },
            [](const std::string &lhs, const std::string &rhs) {
                return JS::Any(std::stod(lhs) * std::stod(rhs));
            },
            [](bool lhs, bool rhs) {
                return JS::Any(lhs * rhs);
            },
            [](JS::Null &lhs, JS::Null &rhs) {
                return JS::Any(0);
            },

            // double
            [](double lhs, const std::string &rhs) {
                return JS::Any(lhs * std::stod(rhs));
            },
            [](double lhs, bool rhs) {
                return JS::Any(lhs * rhs);
            },
            [](double lhs, JS::Null rhs) {
                return JS::Any(0);
            },

            // string
            [](const std::string &lhs, double rhs) {
                return JS::Any(std::stod(lhs) * rhs);
            },
            [](const std::string &lhs, bool rhs) {
                return JS::Any(std::stod(lhs) * rhs);
            },
            [](const std::string &lhs, JS::Null rhs) {
                return JS::Any(std::stod(lhs) * 0);
            },

            // bool
            [](bool lhs, double rhs) {
                return JS::Any(lhs * rhs);
            },
            [](bool lhs, const std::string &rhs) {
                return JS::Any(lhs * std::stod(rhs));
            },
            [](bool lhs, JS::Null rhs) {
                return JS::Any(0);
            },

            // null
            [](JS::Null lhs, double rhs) {
                return JS::Any(0);
            },
            [](JS::Null lhs, const std::string &rhs) {
                return JS::Any(0 * std::stod(rhs));
            },
            [](JS::Null lhs, bool rhs) {
                return JS::Any(0);
            },

            // default
            [](const auto &, const auto &)->JS::Any {
                throw std::runtime_error("Invalid types for multiplication");
            }
        }, value, other.value);
    } catch (std::invalid_argument &e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}
