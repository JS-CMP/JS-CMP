#ifndef CONVERT_HPP
#define CONVERT_HPP

#include "types/JsAny.hpp"
#include "internals/Attribute.hpp"

namespace JS::CONVERT {

JS::Any ToPrimitive(const JS::Any& any);

bool ToBoolean(int value);
bool ToBoolean(double value);
bool ToBoolean(const std::string& value);
bool ToBoolean(const Rope& value);
bool ToBoolean(const JS::Undefined& value);
bool ToBoolean(const JS::Null& value);
bool ToBoolean(const JS::Any& any);

double ToNumber(int value);
double ToNumber(double value);
double ToNumber(const std::string& value);
double ToNumber(const Rope& value);
double ToNumber(const JS::Undefined& value);
double ToNumber(const JS::Null& value);
double ToNumber(const JS::Any& any);

int ToInteger(int value);
int ToInteger(double value);
int ToInteger(const std::string& value);
int ToInteger(const Rope& value);
int ToInteger(const JS::Undefined& value);
int ToInteger(const JS::Null& value);
int ToInteger(const JS::Any& any);

std::string ToString(int value);
std::string ToString(double value);
std::string ToString(const std::string& value);
std::string ToString(const Rope& value);
std::string ToString(const JS::Undefined& value);
std::string ToString(const JS::Null& value);
std::string ToString(const JS::Any& any);

JS::Any ToObject(const JS::Any& any);

JS::Any FromPropertyDescriptor(const JS::Attribute& desc);
JS::Any FromPropertyDescriptor(const JS::DataDescriptor& desc);
JS::Any FromPropertyDescriptor(const JS::AccessorDescriptor& desc);

JS::Attribute ToPropertyDescriptor(const JS::Any& desc);

} // namespace JS::CONVERT

#endif // CONVERT_HPP
