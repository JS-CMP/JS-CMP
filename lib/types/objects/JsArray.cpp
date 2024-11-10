#include <types/objects/JsArray.hpp>

namespace JS {
    Array::Array() : Object() {
        elements = std::make_shared<std::vector<JS::Any>>();
    }
    Array::Array(JS::Array&& other) noexcept : Object(std::move(other)), elements(std::move(other.elements)) {}
    Array::Array(const JS::Array& other) : Object(other), elements(other.elements) {}

    void Array::init() {
        this->operator[]("length") = JS::Any(0);
        this->operator[]("pop") = JS::Any(std::make_shared<JS::Function>(
            JS::Function([self = shared_from_this()] (const std::vector<JS::Any>& args) {
//                auto last = self->elements->back();
                self->elements->pop_back();
                std::cout << "lambda ope " << &self->properties << std::endl;
                auto& lengthProperty = self->operator[]("length");
                lengthProperty = JS::Any(static_cast<int>(self->elements->size()));
                return JS::Any(0);
            })));
    }

    JS::Any& Array::operator[](size_t index) {
        if (index >= elements->size()) {
            elements->resize(index + 1, JS::Any(JS::Undefined{}));
        }
        properties->operator[]("length") = JS::Any(static_cast<int>(elements->size()));
        return elements->operator[](index);
    }

    Array& Array::operator=(const JS::Array& other) {
        Object::operator=(other);
        elements = other.elements;
        return *this;
    }

    Array& Array::operator=(JS::Array&& other) noexcept {
        Object::operator=(std::move(other));
        elements = std::move(other.elements);
        return *this;
    }

    void Array::push(const JS::Any& value) {
        elements->push_back(value);
        properties->operator[]("length") = JS::Any(static_cast<int>(elements->size()));
    }

    bool Array::isCallable() const {
        return false;
    }
}


//JS::Any& Array::operator[](size_t index) {
//    if (index >= elements.size()) {
//        elements.resize(index + 1, JS::Any(JS::Undefined{}));
//    }
//    properties["length"] = JS::Any(static_cast<int>(elements.size()));
//    return elements[index];
//}
//
//const JS::Any& Array::operator[](size_t index) const {
//    if (index < elements.size()) {
//        return elements[index];
//    }
//    throw std::out_of_range("Array index out of bounds.");
//}
//
//JS::Any& Array::operator[](int index) {
//    return this->operator[](static_cast<size_t>(index));
//}
//
//const JS::Any& Array::operator[](int index) const {
//    return this->operator[](static_cast<size_t>(index));
//}