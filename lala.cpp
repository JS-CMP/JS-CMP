#include "includes/class/Console.hpp"
#include "includes/types/JsAny.hpp"
#include "types/objects/Object/JsObject.hpp"
#include "types/objects/Number/JsNumber.hpp"
#include "global/global.hpp"


void displayPrototypeChain(JS::Any obj) {
    JS::Any currentObj = obj;
    JS::Any index = JS::Any(0);
    console::log("Prototype chain:");
    while (currentObj != JS::Any(JS::Null{})) {
        console::log("level", index, currentObj["toString"]());
        currentObj = Object["getPrototypeOf"](currentObj);
        index++;
    }
}


int main() {
//    console::log(Object["prototype"]);
//    JS::Any stringProps = Object["getOwnPropertyNames"](String);

    JS::Any a = JS::Any(std::make_shared<JS::Number>());
    displayPrototypeChain(a);
}


