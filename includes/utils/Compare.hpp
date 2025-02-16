#ifndef COMPARE_HPP
#define COMPARE_HPP

#include "internals/Attribute.hpp"
#include "types/Types.hpp"

namespace JS::COMPARE {
bool Type(const JS::Any& a, const JS::Any& b);
bool Type(const JS::Any& a, const JS::Types& b);
bool Type(const JS::Types& a, const JS::Any& b);

bool SameValue(const double& a, const double& b);
bool SameValue(const Rope& a, const Rope& b);
bool SameValue(const bool& a, const bool& b);
bool SameValue(const JS::Undefined& a, const JS::Undefined& b);
bool SameValue(const JS::Null& a, const JS::Null& b);
bool SameValue(const JS::Any& a, const JS::Any& b); // https://262.ecma-international.org/5.1/#sec-9.12

bool SameValue(const JS::Attribute& a, const JS::Attribute& b);

void CheckObjectCoercible(const JS::Any& a); // https://262.ecma-international.org/5.1/#sec-9.10
} // namespace JS::COMPARE

#endif // COMPARE_HPP
