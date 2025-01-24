#include "../../includes/global/globalFunctions.hpp"
#include "../../includes/types/JsAny.hpp"

std::string global_typeof(const JS::Any& any) {
    switch (any.getValue().index()) {
        case JS::NUMBER:
            return "number";
        case JS::STRING:
            return "string";
        case JS::BOOL:
            return "boolean";
        case JS::UNDEFINED:
            return "undefined";
        case JS::NULL_TYPE:
            return "object";
        default:
            return "object";
    }
}
