#ifndef PROPERTIESPROXY_HPP
#define PROPERTIESPROXY_HPP
#include "types/Types.hpp"

namespace JS {
class PropertyProxy {
public:
    PropertyProxy(JS::InternalObject& obj, std::string key) : obj_(obj), key_(std::move(key)) {}

    // Setter
    PropertyProxy& operator=(const JS::Any& value);

    // Getter
    operator JS::Any(); // must implicitly convert to JS::Any

    operator JS::Any() const; // must implicitly convert to JS::Any

    PropertyProxy operator[](const std::string& key);

private:
    JS::InternalObject& obj_;
    std::string key_;
};
std::ostream& operator<<(std::ostream& os, const PropertyProxy& proxy);
}
#endif // PROPERTIESPROXY_HPP
