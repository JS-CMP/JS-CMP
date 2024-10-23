#include "../../../includes/types/JsAny.hpp"

bool JS::Any::operator>(const JS::Any&other) const
{
   return(std::visit(overloaded{
      // types
      [](double lhs, double rhs) {
         return lhs > rhs;
      },
      [](const std::string&lhs, const std::string&rhs) {
         return lhs.compare(rhs) > 0;
      },
      [](bool lhs, bool rhs) {
         return lhs > rhs;
      },
      [this, other](JS::Function&lhs, JS::Function&rhs) {
         return this->toString().compare(other.toString()) > 0;
      },

      // double
      [](double lhs, const std::string&rhs) {
         return lhs > std::stod(rhs);
      },
      [](double lhs, bool rhs) {
         return static_cast <long long int>(lhs) > rhs;
      },
      [](double lhs, JS::Null rhs) {
         return static_cast <long long int>(lhs) > 0;
      },

      // string
      [](const std::string&lhs, double rhs) {
         return std::stod(lhs) > rhs;
      },
      [](const std::string&lhs, bool rhs) {
         return static_cast <long long int>(std::stod(lhs)) > rhs;
      },
      [other](const std::string&lhs, JS::Function&rhs) {
         return lhs.compare(other.toString()) > 0;
      },

      // bool
      [](bool lhs, double rhs) {
         return lhs > static_cast <long long int>(rhs);
      },
      [](bool lhs, const std::string&rhs) {
         return lhs > static_cast <long long int>(std::stod(rhs));
      },

      // function

      // undefined

      // null
      [](JS::Null lhs, double rhs) {
         return 0.0 > rhs;
      },
      [](JS::Null lhs, const std::string&rhs) {
         return 0.0 > std::stod(rhs);
      },
      [](JS::Null lhs, bool rhs) {
         return false < rhs;
      },

      // default
      [](const auto&, const auto&) {
         return false;
      }
   }, value, other.value));
}
