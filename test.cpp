#include "includes/class/Console.hpp"
#include "includes/types/JsAny.hpp"
#include "types/objects/JsObject.hpp"

int main() {
    JS::Any Object1(std::make_shared<JS::Object>());
    Object1["key1"] = JS::Any(std::make_shared<JS::Object>());
    Object1["key1"]["key2"] = JS::Any(1);
    JS::Any Object2 = Object1["key1"];
    JS::Any Object3 = Object2["key2"];
   	Object1["seal"](Object1);
    console::log(Object1["isSealed"](Object1));
    console::log(Object3, Object2["key2"]);
    console::log("B3");

}