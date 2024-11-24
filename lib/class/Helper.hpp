/*
** EPITECH PROJECT, 2023
** js_cmp
** File description:
** Helper.hpp
*/                                                                                                                     \
#ifndef HELPER_HPP
#define HELPER_HPP

#include <cmath>
#include <string>
#include "../../includes/types/JsAny.hpp"

class Helper {
public:
    static double stod(const std::string &str) {
        return !str.empty() ? std::stod(str) : 0;
    }
    static double stod(const Rope &rope) { // TODO make it faster without the string conversion
        return Helper::stod(rope.toString());
    }

};

#endif // HELPER_HPP
