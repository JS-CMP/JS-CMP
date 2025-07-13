#ifndef CONVERT_HPP
#define CONVERT_HPP

#include "internals/Attribute.hpp"
#include "types/Types.hpp"
#include "utils/Declaration.hpp"

namespace JS::CONVERT {

JS::Any ToPrimitive(const JS::Operator& any, const JS::Types& hint = JS::NUMBER);

DECLARE_1FUNC(bool ToBoolean, );

DECLARE_1FUNC(double ToNumber, );

DECLARE_1FUNC(int ToInteger, );

DECLARE_1FUNC(uint32_t ToUint32, );

DECLARE_1FUNC(uint16_t ToUint16, );

DECLARE_1FUNC(int16_t ToInt16, );

DECLARE_1FUNC(int32_t ToInt32, );

DECLARE_1FUNC(std::u16string ToString, );

std::u16string ToString(JS::Value value);

DECLARE_1FUNC(Rope ToRope, );

std::string ToUtf8(char16_t ch);
std::string ToUtf8(const std::u16string& value);

std::u16string ToUtf16(char ch);
std::u16string ToUtf16(const std::string& value);


std::shared_ptr<JS::InternalObject> ToObject(const JS::Operator& any);

JS::Any FromPropertyDescriptor(const JS::Attribute& desc);
JS::Any FromPropertyDescriptor(const JS::DataDescriptor& desc);
JS::Any FromPropertyDescriptor(const JS::AccessorDescriptor& desc);

JS::Attribute ToPropertyDescriptor(const JS::Any& desc);

std::u16string Stringify(const JS::Any& any);
std::u16string ObjectToString(std::shared_ptr<const JS::InternalObject> internalObject);
std::u16string ArrayToString(std::shared_ptr<const JS::InternalObject> internalObject);
std::u16string FunctionToString(std::shared_ptr<const JS::InternalObject> internalObject);
} // namespace JS::CONVERT

std::ostream& operator<<(std::ostream& os, const std::u16string& str);

#endif // CONVERT_HPP
