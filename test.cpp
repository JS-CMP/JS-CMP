#include "types/JsAny.hpp"
#include "global/global.hpp"
#include "types/JsAny.hpp"
#include "types/objects/Types.hpp"

JS::Any log(const JS::Any &title, const JS::Any &value) {
    console["log"](JS::Any("\n--------------------\n"));
    std::cout << JS::Any("Title: ");
    console["log"](JS::Any("Title: ") + title);
    console["log"](title + JS::Any(" : ") + value);
    console["log"](JS::Any("\n--------------------\n"));
    return JS::Any(1);

}

int main() {
    JS::Any arr = JS::Any(JS::Array({JS::Any(1), JS::Any(2), JS::Any(3), JS::Any(4), JS::Any(5)}));

    JS::Any forEachResult = JS::Any(JS::Array());
    arr["forEach"](JS::Any(std::make_shared<JS::Function>(JS::Function([&](const JS::Any &thisArg,const JS::Any& args) -> JS::Any {
        JS::Any item = args["0"];
        JS::Any index = args["1"];
        JS::Any array = args["2"];
        std::cout << "forEach: item = " << item << ", index = " << index << ", array = " << array << std::endl;
        forEachResult["push"](item * JS::Any(2));
        return JS::Any();
    }))));
    log(JS::Any("forEach"), forEachResult);

    JS::Any mapResult = arr["map"](JS::Any(std::make_shared<JS::Function>(JS::Function([&](const JS::Any &thisArg,const JS::Any& args) -> JS::Any {
        JS::Any item = args["0"];
        return item + JS::Any(1);
    }))));
    log(JS::Any("map"), mapResult);

    JS::Any filterResult = arr["filter"](JS::Any(std::make_shared<JS::Function>(JS::Function([&](const JS::Any &thisArg,const JS::Any& args) -> JS::Any {
        JS::Any item = args["0"];
        return item % JS::Any(2) == JS::Any(0);
    }))));

    JS::Any reduceResult = arr["reduce"](JS::Any(std::make_shared<JS::Function>(JS::Function([&](const JS::Any &thisArg,const JS::Any& args) -> JS::Any {
        JS::Any acc = args["0"];
        JS::Any item = args["1"];
        return acc + item;
    }))), JS::Any(0));
    log(JS::Any("reduce"), reduceResult);

    JS::Any reduceRightResult = arr["reduceRight"](JS::Any(std::make_shared<JS::Function>(JS::Function([&](const JS::Any &thisArg,const JS::Any& args) -> JS::Any {
        JS::Any acc = args["0"];
        JS::Any item = args["1"];
        return acc - item;
    }))), JS::Any(0));
    log(JS::Any("reduceRight"), reduceRightResult);

    JS::Any everyResult = arr["every"](JS::Any(std::make_shared<JS::Function>(JS::Function([&](const JS::Any &thisArg,const JS::Any& args) -> JS::Any {
        JS::Any item = args["0"];
        return item > JS::Any(0);
    }))));
    log(JS::Any("every"), everyResult);

    JS::Any someResult = arr["some"](JS::Any(std::make_shared<JS::Function>(JS::Function([&](const JS::Any &thisArg,const JS::Any& args) -> JS::Any {
        JS::Any item = args["0"];
        return item > JS::Any(3);
    }))));
    log(JS::Any("some"), someResult);

    JS::Any indexOfResult = arr["indexOf"](JS::Any(3));
    log(JS::Any("indexOf"), indexOfResult);

    JS::Any arr2 = JS::Any(JS::Array({JS::Any(1), JS::Any(2), JS::Any(3), JS::Any(2), JS::Any(1)}));
    JS::Any lastIndexOfResult = arr2["lastIndexOf"](JS::Any(2));
    log(JS::Any("lastIndexOf"), lastIndexOfResult);

    log(JS::Any("isArray"), Array["isArray"](arr));

    JS::Any concatResult = arr["concat"](JS::Any(JS::Array({JS::Any(6), JS::Any(7)})));
    log(JS::Any("concat"), concatResult);

    JS::Any joinResult = arr["join"](JS::Any(u"-"));
    log(JS::Any("join"), joinResult);

    JS::Any sliceResult = arr["slice"](JS::Any(1), JS::Any(3));
    log(JS::Any("slice"), sliceResult);

    JS::Any spliceArr = arr["slice"]();
    log(JS::Any("splice"), spliceArr["splice"](JS::Any(2), JS::Any(1), JS::Any(99)));

    JS::Any reverseArr = arr["slice"]()["reverse"]();
    log(JS::Any("reverse"), reverseArr);

    JS::Any sortArr = JS::Any(JS::Array({JS::Any(3), JS::Any(1), JS::Any(4), JS::Any(2)}))["sort"]();
    log(JS::Any("sort"), sortArr);

    JS::Any pushArr = arr["slice"]();
    pushArr["push"](JS::Any(6));
    log(JS::Any("push"), pushArr);

    JS::Any popArr = arr["slice"]();
    popArr["pop"]();
    log(JS::Any("pop"), popArr);

    JS::Any shiftArr = arr["slice"]();
    shiftArr["shift"]();
    log(JS::Any("shift"), shiftArr);

    JS::Any unshiftArr = arr["slice"]();
    unshiftArr["unshift"](JS::Any(0));
    log(JS::Any("unshift"), unshiftArr);
    return 0;
}