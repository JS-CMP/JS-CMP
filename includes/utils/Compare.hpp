#ifndef COMPARE_HPP
#define COMPARE_HPP

#include "types/JsAny.hpp"
#include "types/Types.hpp"

namespace JS::COMPARE {
bool Type(const JS::Any& a, const JS::Any& b);
bool Type(const JS::Any& a, const JS::Types& b);
bool Type(const JS::Types& a, const JS::Any& b);
bool IsCallable(const JS::Any& a);
bool SameValue(const JS::Any& a, const JS::Any& b); // https://262.ecma-international.org/5.1/#sec-9.12
} // namespace JS::COMPARE

#endif // COMPARE_HPP
