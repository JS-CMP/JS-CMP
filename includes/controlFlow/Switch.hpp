#ifndef SWITCH_HPP
#define SWITCH_HPP

#include "types/JsAny.hpp"
#include <optional>
#include <map>

namespace JS {
struct Hash {
    std::size_t operator()(const std::optional<JS::Any>& key) const;
};

struct StrictEqual {
    bool operator()(const std::optional<JS::Any>& lhs, const std::optional<JS::Any>& rhs) const;
};

namespace SWITCH {
enum class JMP_STATE {
    CONTINUE,
    BREAK,
    RETURN,
    FALLTHROUGH,
};

using state_t = std::pair<std::optional<JS::Any>, JMP_STATE>;
}
} // namespace JS

#define SW_RETURN(value) return {  std::optional<JS::Any>(value), JS::SWITCH::JMP_STATE::RETURN };
#define SW_BREAK return { std::nullopt, JS::SWITCH::JMP_STATE::BREAK };
#define SW_CONTINUE return { std::nullopt, JS::SWITCH::JMP_STATE::CONTINUE };

#define CASE(value, scope) { std::optional<JS::Any>(value), [&]() -> JS::SWITCH::state_t { scope; return { std::nullopt, JS::SWITCH::JMP_STATE::FALLTHROUGH }; } }
#define DEFAULT(scope) { std::nullopt, [&]() -> JS::SWITCH::state_t { scope; return { std::nullopt, JS::SWITCH::JMP_STATE::FALLTHROUGH }; } }

#define SWITCH(value, ...) \
{ \
    static const std::map<std::optional<JS::Any>, std::function<JS::SWITCH::state_t()>, JS::Hash, JS::StrictEqual> switch_map = { __VA_ARGS__ }; \
    auto it = switch_map.find(std::optional<JS::Any>(value)); \
    if (it == switch_map.end()) { \
        it = switch_map.find(std::nullopt); \
    } \
    if (it != switch_map.end()) { \
        JS::SWITCH::state_t result; \
        for (; it != switch_map.end(); ++it) { \
            result = it->second(); \
            if (result.second != JS::SWITCH::JMP_STATE::FALLTHROUGH) { \
                break; \
            } \
        } \
        switch (result.second) { \
            case JS::SWITCH::JMP_STATE::CONTINUE: \
                continue; \
            case JS::SWITCH::JMP_STATE::RETURN: \
                return result.first.value(); \
            default: \
        } \
    } \
}

#endif //SWITCH_HPP
