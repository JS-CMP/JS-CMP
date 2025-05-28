#include "customOperators/CustomOperators.hpp"
#include "global/global.hpp"
#include "types/JsAny.hpp"
#include "types/objects/Types.hpp"

int main() {
    JS::Any a = JS::Any(JS::Object({{"test", JS::Any(12)}}));
    try {
        NEW(a);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
