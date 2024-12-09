#ifndef COMPARE_HPP
#define COMPARE_HPP

#include "types/JsAny.hpp"
#include "types/Types.hpp"
#include "types/Attribute.hpp"

namespace JS::COMPARE {


bool Type(const JS::Any& a, const JS::Any& b);
bool Type(const JS::Any& a, const JS::Types& b);
bool Type(const JS::Types& a, const JS::Any& b);
bool IsPrimitive(const JS::Any& a);
bool IsCallable(const JS::Any& a); // https://262.ecma-international.org/5.1/#sec-9.11
bool IsAccessorDescriptor(const JS::Attribute& a); // https://262.ecma-international.org/5.1/#sec-8.10.1
bool IsDataDescriptor(const JS::Attribute& a); // https://262.ecma-international.org/5.1/#sec-8.10.2
bool IsGenericDescriptor(const JS::Attribute& a); // https://262.ecma-international.org/5.1/#sec-8.10.3
bool SameValue(const JS::Any& a, const JS::Any& b); // https://262.ecma-international.org/5.1/#sec-9.12
} // namespace JS::COMPARE

#endif // COMPARE_HPP
