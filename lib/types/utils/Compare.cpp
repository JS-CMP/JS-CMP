#include <types/objects/JsObject.hpp>
#include <utils/Compare.hpp>

namespace JS::COMPARE {
bool Type(const JS::Any& a, const JS::Any& b) { return a.getValue().index() == b.getValue().index(); }

bool Type(const JS::Any& a, const JS::Types& b) { return a.getValue().index() == b; }

bool Type(const JS::Types& a, const JS::Any& b) { return a == b.getValue().index(); }

bool IsCallable(const JS::Any& a) {
    if (Type(a, JS::OBJECT)) {
        return std::get<std::shared_ptr<JS::Object>>(a.getValue())->isCallable();
    } else {
        return false;
    }
}
} // namespace JS::COMPARE