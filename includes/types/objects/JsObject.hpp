#ifndef JSOBJECT_HPP
#define JSOBJECT_HPP

#include "../Types.hpp"
#include "../JsAny.hpp"

namespace JS {
class Object {
    public:
        Object() = default;
        Object(const JS::Object& other);
        Object& operator=(const JS::Object& other);
        Object(JS::Object&& other) noexcept;
        Object& operator=(JS::Object&& other) noexcept;
        virtual ~Object() = default;

        virtual JS::Any& operator[](const std::string& key);
        virtual JS::Any& operator[](size_t index);
        virtual void init() {};

        [[nodiscard]] virtual bool isCallable() const;
        [[nodiscard]] bool hasProperty(const std::string& key) const;
        void setProperty(const std::string& key, const JS::Any& value);
    protected:
        std::shared_ptr<std::unordered_map<std::string, JS::Any>> properties =
            std::make_shared<std::unordered_map<std::string, JS::Any>>();
    };
}

#endif // JSOBJECT_HPP
