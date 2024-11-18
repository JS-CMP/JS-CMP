#include "src/Builder.hpp"
#include "src/Options.hpp"

int main(int argc, char** argv, char** env) {
    Options options(argc, argv, env);
    try {
        options.parse();
    } catch (const std::runtime_error& e) {
        std::cerr << "JS_CMP: " << e.what() << std::endl;
        options.printUsage();
        exit(1);
    }
    try {
        Builder builder(options);
        builder.build();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    return (0);
}

//#include "includes/class/Console.hpp"
//#include "includes/types/JsAny.hpp"
//#include "includes/types/Objects/JsArray.hpp"
//
// int main() {
//    JS::Any array = JS::Any(JS::Array());
//    array[0] = JS::Any("va");
//    array[1] = JS::Any("ca");
//    array[2] = JS::Any("salut");
//    console::log(array[0]);
//    console::log(array[1]);
//    console::log(array[2]);
//    array["pop"](1, 2, "salt");
//}
