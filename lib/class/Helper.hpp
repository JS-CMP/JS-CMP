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
    static double stod(const std::string& str) { return !str.empty() ? std::stod(str) : 0; }
    /** @brief Convert a Rope to an double. */
    static double stod(const Rope& rope) { // TODO make it faster without the string conversion
        return Helper::stod(rope.toString());
    }
    ///@}

    /**
     * @name Any to String
     * These functions convert an Any to a string.
     */
    ///@{
    /** @brief Convert an int to a string. */
    static std::string to_string(int value) {
        std::ostringstream strs;
        strs << value;
        return strs.str();
    }
    /** @brief Convert an double to a string. */
    static std::string to_string(double value) {
        if (std::isnan(value)) {
            return "NaN";
        }
        if (std::isinf(value)) {
            return value < 0 ? "-Infinity" : "Infinity";
        }
        std::ostringstream strs;
        strs << value;
        return strs.str();
    }
    /** @brief Convert a Rope to a string. */
    static std::string to_string(const Rope& rope) { return rope.toString(); }
    /** @brief Convert a bool to a string. */
    static std::string to_string(bool value) { return value ? "true" : "false"; }
    /** @brief Convert a Null to a string. */
    static std::string to_string(const JS::Null&) { return "null"; }
    /** @brief Convert a Undefined to a string. */
    static std::string to_string(const JS::Undefined&) { return "undefined"; }
    ///@}
};

#endif // HELPER_HPP
