#ifndef JSOBJECT_HPP
#define JSOBJECT_HPP

#include "Types.hpp"
#include "JsAny.hpp"

namespace JS {
    class Object {
    public:
        Object() = default;
        Object(const JS::Object&) = default;
        Object& operator=(const JS::Object&) = default;
        Object(JS::Object&&) noexcept = default;
        Object& operator=(JS::Object&&) noexcept = default;


        JS::Any& operator[](const std::string& key);
        const JS::Any& operator[](const std::string& key) const;
        JS::Any& operator[](const char* key);
        const JS::Any& operator[](const char* key) const;
        JS::Any& operator[](size_t index);
        const JS::Any& operator[](size_t index) const;
        JS::Any& operator[](int index);
        const JS::Any& operator[](int index) const;


        bool hasProperty(const std::string& key) const;
    protected:
        std::unordered_map<std::string, JS::Any> properties;
    };
}

#endif // JSOBJECT_HPP
