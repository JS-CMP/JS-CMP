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

class Helper {
public:
    static double stod(const std::string& str) { return !str.empty() ? std::stod(str) : 0; }
    static double stod(const Rope& rope) { // TODO make it faster without the string conversion
        return Helper::stod(rope.toString());
    }

    static std::string to_string(int value) {
        std::ostringstream strs;
        strs << value;
        return strs.str();
    }
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
    static std::string to_string(const Rope& rope) { return rope.toString(); }
    static std::string to_string(bool value) { return value ? "true" : "false"; }
    static std::string to_string(const JS::Null&) { return "null"; }
    static std::string to_string(const JS::Undefined&) { return "undefined"; }
};

#endif // HELPER_HPP
