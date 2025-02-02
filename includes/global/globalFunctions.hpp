#ifndef JS_CMP_GLOBALFUNCTIONS_HPP
#define JS_CMP_GLOBALFUNCTIONS_HPP

#include "../types/Types.hpp"

JS::Any isNaN(const std::vector<JS::Any>& args);
JS::Any parseInt(const std::vector<JS::Any>& args);
JS::Any global_typeof(const std::vector<JS::Any>& args);
JS::Any isFinite(const std::vector<JS::Any>& args);
JS::Any global_void(const std::vector<JS::Any>& args);

#endif // JS_CMP_GLOBALFUNCTIONS_HPP
