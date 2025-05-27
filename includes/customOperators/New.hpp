#ifndef NEW_HPP
#define NEW_HPP

#include "internals/Arguments.hpp"
#include "types/JsAny.hpp"

#define NEW(obj, ...) obj.constructor(JS::Arguments::CreateArgumentsObject(std::vector<JS::Any>{__VA_ARGS__}))


#endif //NEW_HPP
