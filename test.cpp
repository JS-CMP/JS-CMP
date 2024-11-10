/*
** EPITECH PROJECT, 2023
** JS-CMP
** File description:
** test.cpp
*/

#include "includes/class/Console.hpp"
#include "includes/types/JsAny.hpp"
#include "includes/types/objects/JsArray.hpp"
#include "includes/types/JsTest.hpp"

int main()
{
//    auto a = std::make_shared<JS::Array>();
//    JS::Any array(a);
//    std::cout << "iciii " << &a->properties << std::endl;
//    std::cout << "aaa" << &a << std::endl;
//    array[0] = JS::Any("va");
//    array[1] = JS::Any("ca");
//    array[2] = JS::Any("salut");
//    std::cout << array[0] << array[1] << array[2] << std::endl;
//    std::cout << array["length"] << std::endl;
//    array["pop"](1, 2, "yo");
//    std::cout << array[0] << array[1] << array[2] << std::endl;
//    std::cout << array["length"] << std::endl;
//    return 0;

//    JS::Test test(std::make_shared<JS::Array>());
//    test[0] = JS::Any("va");
//    test[1] = JS::Any(1);
//    test[2] = JS::Any("ca");
//    test[3] = JS::Any(2);
//    std::cout << test[0] << test[1] << test[2] << test[3] << std::endl;
//    std::cout << test["length"]() << std::endl;
//    test["pop"](1, 2, "yo");
//    std::cout << test[0] << test[1] << test[2] << test[3] << std::endl;
//    std::cout << test["length"]() << std::endl;


//    // works
    std::shared_ptr<JS::Object> obj = std::make_shared<JS::Array>();
    obj->init();
    obj->operator[](0) = JS::Any("va");
    obj->operator[](1) = JS::Any(1);
    obj->operator[](2) = JS::Any("ca");
    obj->operator[](3) = JS::Any(2);
    std::cout << obj->operator[]("length") << std::endl;
    obj->operator[]("pop")(1, 2, "yo");
    std::cout << obj->operator[]("length") << std::endl;
    std::cout << obj->operator[](0) << obj->operator[](1) << obj->operator[](2) << obj->operator[](3) << std::endl;

    // works
//    std::shared_ptr<JS::Array> arr = std::make_shared<JS::Array>();
//    arr->init();
//    arr->push(JS::Any("va"));
//    arr->push(JS::Any(1));
//    arr->push(JS::Any("ca"));
//    arr->push(JS::Any(2));
//    arr->operator[]("pop")();
//    std::cout << arr->operator[](0) << arr->operator[](1) << arr->operator[](2) << arr->operator[](3) << std::endl;
}

//JS::Function func = JS::Function([](const std::vector<JS::Any> &args) -> JS::Any {
//    return JS::Any(42);
//});
//std::shared_ptr<JS::Object> obj = std::make_shared<JS::Function>(func);
//std::cout << obj->isCallable() << std::endl;
//std::shared_ptr<JS::Function> recast = std::dynamic_pointer_cast<JS::Function>(obj);
//if (recast) {
//std::cout << "Successfully casted back to JS::Function" << std::endl;
//} else {
//std::cout << "Failed to cast back to JS::Function" << std::endl;
//}