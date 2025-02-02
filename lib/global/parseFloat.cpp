#include "types/JsAny.hpp"

#include <iostream>

namespace JS::GLOBAL {
JS::Any parseFloat(const std::vector<JS::Any>& args) {
    throw std::runtime_error("parseFloat not implemented");
}
} // namespace JS::GLOBAL