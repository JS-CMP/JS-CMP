#include "includes/class/Console.hpp"
#include "includes/types/JsAny.hpp"
#include "includes/types/objects/JsObject.hpp"

int main() {
    JS::Any a(std::make_shared<JS::Object>());
    console::log(a);
    JS::Any v = a();

    console::log(v);
}