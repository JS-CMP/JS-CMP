#ifndef JS_CMP_GLOBALFUNCTIONS_HPP
#define JS_CMP_GLOBALFUNCTIONS_HPP

#include "../types/Types.hpp"

namespace JS::GLOBAL {
JS::Any isNaN(const JS::Any &thisArgs, const JS::Any &args);
JS::Any parseInt(const JS::Any &thisArgs, const JS::Any &args);
JS::Any parseFloat(const JS::Any &thisArgs, const JS::Any &args);
JS::Any isFinite(const JS::Any &thisArgs, const JS::Any &args);
JS::Any encodeURI(const JS::Any &thisArgs, const JS::Any &args);
JS::Any decodeURI(const JS::Any &thisArgs, const JS::Any &args);
JS::Any encodeURIComponent(const JS::Any &thisArgs, const JS::Any &args);
JS::Any decodeURIComponent(const JS::Any &thisArgs, const JS::Any &args);
} // namespace JS::GLOBAL

#endif // JS_CMP_GLOBALFUNCTIONS_HPP
