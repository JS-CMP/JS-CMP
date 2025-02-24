#ifndef PROPERTIESPROXY_HPP
#define PROPERTIESPROXY_HPP
#include "internals/Arguments.hpp"
#include "types/JsAny.hpp"
#include "types/Types.hpp"

namespace JS {
class PropertyProxy {
public:
    PropertyProxy(const std::shared_ptr<JS::InternalObject> obj, std::string key) : obj_(obj), key_(std::move(key)) {}

    // Setter
    PropertyProxy& operator=(const JS::Any& value);

    // Getter
    operator JS::Any(); // must implicitly convert to JS::Any

    operator JS::Any() const; // must implicitly convert to JS::Any

    PropertyProxy operator[](const std::string& key) const;

    // Overload operator() to cast to JS::Any and call operator()
    template <typename... Args>
    JS::Any operator()(Args&&... args) {
        return call(JS::Arguments::CreateArgumentsObject(std::vector<JS::Any>{args...}));
    }
    JS::Any call(const JS::Any& args) const;

    JS::Value getValue() const;

    bool operator==(const PropertyProxy& property_proxy) const;
    JS::Any operator!() const;

private:
    std::shared_ptr<JS::InternalObject> obj_;
    std::string key_;
};
std::ostream& operator<<(std::ostream& os, const PropertyProxy& proxy);
} // namespace JS
#endif // PROPERTIESPROXY_HPP
