#ifndef JS_CMP_GLOBALFUNCTIONS_HPP
#define JS_CMP_GLOBALFUNCTIONS_HPP

#include "../types/Types.hpp"

bool global_isNaN(const JS::Any& number);
JS::Any global_parseInt(const JS::Any& inputStringAny, const JS::Any& radixAny);
std::string global_typeof(const JS::Any& any);
bool global_isFinite(const JS::Any& number);
JS::Undefined global_void(const JS::Any& args);

#endif //JS_CMP_GLOBALFUNCTIONS_HPP
