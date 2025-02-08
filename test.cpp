#include "globals.hpp"
#include "includes/class/Console.hpp"
#include "includes/types/JsAny.hpp"
#include "includes/types/objects/Function/JsFunctionBinded.hpp"
#include "types/objects/JsObject.hpp"

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
    JS::Any Person = JS::Any(JS::Function([](const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
        JS::Any name = args["0"];
        JS::Any age = args["1"];
        console::log(thisArg);
        JS::Any obj = JS::Any(std::make_shared<JS::Object>());
        obj["name"] = name;
        obj["age"] = age;
        return obj;
    }));
    JS::Any john = Person(JS::Any("John"), JS::Any(30));

    console::log(john["name"], john["age"]);

    JS::Any personBinded = Person["bind"](JS::Any(JS::Null{}), JS::Any("Mike"), JS::Any(40));
    JS::Any mike = personBinded();
    console::log(mike["name"], mike["age"]);
    JS::Any caller = personBinded["caller"]; // should throw
}