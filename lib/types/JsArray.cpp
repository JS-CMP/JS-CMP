#include "../../includes/types/JsArray.hpp"

namespace JS {

    Array::Array() {
        properties["length"] = JS::Any(0); // Initialize length property
        properties["pop"] = JS::Any([this](const std::vector<JS::Any>& args) -> JS::Any {
            if (elements.empty()) {
                return JS::Any(JS::Undefined{});
            }
            // Store the last element to return it
            JS::Any lastElement = elements.back();
            elements.pop_back(); // Remove the last element
            properties["length"] = JS::Any(static_cast<int>(elements.size())); // Update length
            return lastElement; // Return the removed element
        });
    }

    Array::Array(const JS::Array& other) : Object(other), elements(other.elements) {}
    Array& Array::operator=(const JS::Array& other) {
        Object::operator=(other);
        elements = other.elements;
        return *this;
    }

    Array::Array(JS::Array&& other) noexcept : Object(std::move(other)), elements(std::move(other.elements)) {}

    Array& Array::operator=(JS::Array&& other) noexcept {
        Object::operator=(std::move(other));
        elements = std::move(other.elements);
        return *this;
    }

    JS::Any& Array::operator[](size_t index) {
        if (index >= elements.size()) {
            elements.resize(index + 1, JS::Any(JS::Undefined{}));
        }
        properties["length"] = JS::Any(static_cast<int>(elements.size()));
        return elements[index];
    }

    const JS::Any& Array::operator[](size_t index) const {
        if (index < elements.size()) {
            return elements[index];
        }
        throw std::out_of_range("Array index out of bounds.");
    }

    JS::Any& Array::operator[](int index) {
        return this->operator[](static_cast<size_t>(index));
    }

    const JS::Any& Array::operator[](int index) const {
        return this->operator[](static_cast<size_t>(index));
    }

    void Array::push(const JS::Any& value) {
        elements.push_back(value);
        properties["length"] = JS::Any(static_cast<int>(elements.size()));
    }
}
