#include "src/Builder.hpp"
#include "src/Options.hpp"

int main(int argc, char** argv, char** env) {
    Options options(argc, argv, env);
    try {
        options.parse();
    } catch (const std::runtime_error& e) {
        std::cerr << "JS_CMP: " << e.what() << '\n';
        options.printUsage();
        exit(1);
    }
    try {
        Builder builder(options);
        builder.build();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        exit(1);
    }
    return (0);
}