#ifndef JS_CMP_GLOBALFUNCTIONS_HPP
#define JS_CMP_GLOBALFUNCTIONS_HPP

#include "../types/Types.hpp"

namespace JS::GLOBAL {
JS::Any isNaN(const std::vector<JS::Any>& args);
JS::Any parseInt(const std::vector<JS::Any>& args);
JS::Any parseFloat(const std::vector<JS::Any>& args);
JS::Any isFinite(const std::vector<JS::Any>& args);
JS::Any global_typeof(const std::vector<JS::Any>& args);
} // namespace JS::GLOBAL

#endif // JS_CMP_GLOBALFUNCTIONS_HPP
