/*
** EPITECH PROJECT, 2023
** js_cmp
** File description:
** Helper.hpp
*/
#ifndef HELPER_HPP
#define HELPER_HPP

#include "../../includes/types/JsAny.hpp"

#include <cmath>
#include <sstream>
#include <string>

/**
 * @class Helper
 * @brief A class that provides helper functions for converting between types.
 *
 * This class provides static methods for converting between different types, such as strings and numbers.
 * It is used to convert values between different types when performing operations on them.
 */
class Helper {
public:
    /**
     * @name String to Number
     * These functions convert a string to a number, if the string is empty, it returns 0.
     */
    ///@{
    /** @brief Convert a string to an double. */
    inline static double stod(const std::string& str) { return !str.empty() ? std::stod(str) : 0; }
    /** @brief Convert a Rope to an double. */
    inline static double stod(const Rope& rope) { // TODO make it faster without the string conversion
        return Helper::stod(rope.toString());
    }
    ///@}

    /**
     * @name Any to String
     * These functions convert an Any to a string.
     */
    ///@{
    /** @brief Convert an int to a string. */
    inline static std::string to_string(int value) {
        return static_cast<std::ostringstream>((std::ostringstream() << value)).str();
    }
    /** @brief Convert an double to a string. */
    inline static std::string to_string(double value) {
        return std::isnan(value)   ? "NaN"
               : std::isinf(value) ? value < 0 ? "-Infinity" : "Infinity"
                                   : static_cast<std::ostringstream>((std::ostringstream() << value)).str();
    }
    /** @brief Convert a Rope to a string. */
    inline static std::string to_string(const Rope& rope) { return rope.toString(); }
    /** @brief Convert a bool to a string. */
    inline static std::string to_string(bool value) { return value ? "true" : "false"; }
    /** @brief Convert a Null to a string. */
    inline static std::string to_string(const JS::Null&) { return "null"; }
    /** @brief Convert a Undefined to a string. */
    inline static std::string to_string(const JS::Undefined&) { return "undefined"; }
    /** @brief Check if Any is undefined */
    inline static bool isUndefined(const JS::Any& any) { return any.getValue().index() == JS::UNDEFINED; }
    /** @brief Check if Any is null */
    inline static bool isNull(const JS::Any& any) { return any.getValue().index() == JS::NULL_TYPE; }
    /** @brief Check if Any is nan */
    inline static bool isNaN(const JS::Any& any) {
        return any.getValue().index() == JS::NUMBER && std::isnan(std::get<double>(any.getValue()));
    }
    /** @brief return the typeof the value in Any */
    inline static std::string type_of(const JS::Any& any) {
        switch (any.getValue().index()) {
            case JS::NUMBER: return "number";
            case JS::STRING: return "string";
            case JS::BOOL: return "boolean";
            case JS::UNDEFINED: return "undefined";
            case JS::NULL_TYPE: return "object";
            case JS::OBJECT: return "object";
            default: return "undefined";
        }
    }
    /** @brief Check if Any is negative */
    inline static bool signbit(const JS::Any& x) {
        return x.getValue().index() == JS::NUMBER && std::signbit(std::get<double>(x.getValue()));
    }
    /** @brief Check if x and y are the same number */
    inline static bool sameValueNumber(const JS::Any& x, const JS::Any& y) {
        if (isNaN(x) && isNaN(y)) return true;
        if (std::signbit(std::get<double>(x.getValue())) != std::signbit(std::get<double>(y.getValue()))) return false;
        if (x == y) return true;
        return false;
    }
    /** @brief Check if x is a number */
    inline static bool isNumber(const JS::Any &x) { return x.getValue().index() == JS::NUMBER; }
    /** @brief Check if x is an object */
    inline static bool isObject(const JS::Any &x) { return x.getValue().index() == JS::OBJECT; }
    /** @brief Check if x is an array */
    inline static bool isArray(const JS::Any &x) { return false; }
    /** @brief Check if x is not nan */
    inline static bool NumberIsNaN(const JS::Any &x) { return isNaN(x); }
    /** @brief Check if x and y are the same non-number */
    inline static bool sameValueNonNumber(const JS::Any& x, const JS::Any& y) {
        // TODO: add throw if x and y not same type
        if (isUndefined(x) || isNull(x)) return true;
        // TODO: bigint
        return x.strictEq(y); // does not respect https://tc39.es/ecma262/#sec-identity
    }
    /** @brief Check if x and y are the same */
    inline static bool sameValue(const JS::Any& x, const JS::Any& y) {
        if (type_of(x) != type_of(y)) return false;
        if (x.getValue().index() == JS::NUMBER)
            return sameValueNumber(x, y);
        return sameValueNonNumber(x, y);
    }
    /** @brief Check if x and y are the same */
    inline static bool ObjectIs(const JS::Any& x, const JS::Any& y) {
        return sameValue(x, y);
    }
    ///@}
};

#endif // HELPER_HPP
