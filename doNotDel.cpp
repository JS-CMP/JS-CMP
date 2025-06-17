#include "includes/types/JsAny.hpp"
#include "includes/types/objects/Error/JsReferenceError.hpp"
#include "includes/types/objects/JsObject.hpp"
#include "includes/internals/Attribute.hpp"
#include "includes/global/global.hpp"

int main() {
    JS::Any a = JS::Any(std::make_shared<JS::Number>(JS::Any(1)));

    JS::Any test = JS::Any(std::make_shared<JS::Object>());
    test[u"yee"] = JS::Any(1);
    test[u"ouais ouais"] = JS::Any(JS::Object({
        {u"age", JS::Any(18)},
        {u"name", JS::Any(u"John")},
        {u"address", JS::Any(JS::Object({
            {u"city", JS::Any(u"New York")},
            {u"street", JS::Any(u"Wall Street")}
        }))}
    }));
    test[u"forEach"] = JS::Any(std::make_shared<JS::Function>(JS::Function(
    [&](const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
        JS::Any item = args["0"];
        JS::Any index = args["1"];
        JS::Any array = args["2"];
        std::cout << "forEach: item = " << item << ", index = " << index << ", array = " << array << std::endl;
        return JS::Any();
    })));

    throw test;


//    auto internal = std::get<std::shared_ptr<JS::InternalObject>>(test.value);
//    std::cout << internal->getContent() << std::endl;
//    try {
//        throw JS::ReferenceError(JS::Any("yeye"));
//    } catch (const std::exception& e) {
//        std::cout << e.what() << std::endl;
//    }
}