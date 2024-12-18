#ifndef COMPARE_HPP
#define COMPARE_HPP

#include "types/JsAny.hpp"
#include "types/Types.hpp"

namespace JS::COMPARE {
bool Type(const JS::Any& a, const JS::Any& b);
bool Type(const JS::Any& a, const JS::Types& b);
bool Type(const JS::Types& a, const JS::Any& b);
bool IsCallable(const JS::Any& a);
} // namespace JS::COMPARE

#endif // COMPARE_HPP
