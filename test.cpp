#include "includes/class/Console.hpp"
#include "includes/types/JsAny.hpp"
#include "types/objects/JsObject.hpp"
#include "globals.hpp"

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
    JS::Any Person = JS::Any(JS::Object({
        {"age", JS::Any(18)},
        {"name", JS::Any("John")},
        {"address", JS::Any(JS::Object({
            {"city", JS::Any("New York")},
            {"street", JS::Any("Wall Street")}
        }))}
    }));

    JS::Any age = Person["age"];
    JS::Any name = Person["name"];

    console::log("-----------------Object-----------------");
    console::log("Person age:", age, "name:", name);
    console::log("Address city:", Person["address"]["city"], "street:", Person["address"]["street"]);

    console::log("\n-----------------Object Freeze-----------------");

    Object["freeze"](Person);

    console::log("Is Person frozen:", Object["isFrozen"](Person));

    Person["age"] = JS::Any(2);

    console::log("Person age not updated:", Person["age"]);

    Object["defineProperty"](Person, JS::Any("data"), JS::Any(JS::Object({
        {"value", JS::Any("Data")},
        {"writable", JS::Any(true)},
        {"enumerable", JS::Any(true)},
        {"configurable", JS::Any(true)}
    })));

    console::log("Person data does not exist: ", Person["hasOwnProperty"](JS::Any("data")));

    console::log("\n-----------------Object Address is not Freeze-----------------");
    Person["address"]["city"] = JS::Any("Los Angeles");

    console::log("Person city updated:", Person["address"]["city"]);

    console::log("\n-----------------Object HasOwnProperty-----------------");
    console::log("Person age exists:", Person["hasOwnProperty"](JS::Any("age")));
    console::log("Person city exists:", Person["address"]["hasOwnProperty"](JS::Any("city")));



    console::log("\n-----------------Object PropertyIsEnumerable-----------------");
    console::log("Person age is enumerable:", Person["propertyIsEnumerable"](JS::Any("age")));

    console::log("\n-----------------Object isExtensible-----------------");
    console::log("Person is not extensible because it is freeze:", Object["isExtensible"](Person));
    console::log("Person address is extensible:", Object["isExtensible"](Person["address"]));

    console::log("\n-----------------Object isPrototypeOf-----------------");
    console::log("Person prototype is prototype of Person:", Object["getPrototypeOf"](Person)["isPrototypeOf"](Person));
    console::log("Person prototype is prototype of Person address:", Object["getPrototypeOf"](Person)["isPrototypeOf"](Person["address"]));

    console::log("\n-----------------Object Prototype Chains-----------------");
    displayPrototypeChain(Person);
    displayPrototypeChain(Person["address"]);
}