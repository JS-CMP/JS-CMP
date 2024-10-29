/*
** EPITECH PROJECT, 2023
** JS-CMP
** File description:
** test.cpp
*/

#include "includes/class/Console.hpp"
#include "includes/types/JsAny.hpp"
#include "includes/types/JsObject.hpp"
#include "includes/types/JsArray.hpp"

int main()
{
    JS::Any Object = JS::Any(JS::Object());
    JS::Any Array = JS::Any(JS::Array());

    Object["test"] = JS::Any(42);
    console::log(Object["test"]);
    Array[0] = JS::Any(42);
    console::log(Array[0]);
    // Can be remove if we use variadic templates
    std::vector<JS::Any> args;
    Array["pop"](args);
    console::log(Array[0]);

    return 0;
}