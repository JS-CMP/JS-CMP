#ifndef IS_HPP
#define IS_HPP
#include "internals/Attribute.hpp"
#include "types/Types.hpp"

namespace JS::IS {
bool Primitive(const JS::Operator& a);
bool Callable(const JS::Operator& a);
bool Callable(const std::shared_ptr<JS::InternalObject>& a);
bool Callable(const JS::Value& a);
bool AccessorDescriptor(const JS::Attribute& a); // https://262.ecma-international.org/5.1/#sec-8.10.1
bool DataDescriptor(const JS::Attribute& a);     // https://262.ecma-international.org/5.1/#sec-8.10.2
bool GenericDescriptor(const JS::Attribute& a);  // https://262.ecma-international.org/5.1/#sec-8.10.3
bool ArrayIndex(const std::u16string& key);
} // namespace JS::IS

#endif // IS_HPP
