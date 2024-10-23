#include "../../../includes/types/JsAny.hpp"

JS::Any JS::Any::operator/(const JS::Any&other) const
{
   try {
      return(std::visit(overloaded{
         // types
         [](double lhs, double rhs) {
            return JS::Any(lhs / rhs);
         },
         [](const std::string&lhs, const std::string&rhs) {
            return JS::Any(std::stod(lhs) / std::stod(rhs));
         },
         [](bool lhs, bool rhs) {
            return JS::Any(static_cast <double>(lhs) / static_cast <double>(rhs));
         },

         // double
         [](double lhs, const std::string&rhs) {
            return JS::Any(lhs / std::stod(rhs));
         },
         [](double lhs, bool rhs) {
            return JS::Any(lhs / rhs);
         },

         // string
         [](const std::string&lhs, double rhs) {
            return JS::Any(std::stod(lhs) / rhs);
         },
         [](const std::string&lhs, bool rhs) {
            return JS::Any(std::stod(lhs) / rhs);
         },

         // bool
         [](bool lhs, double rhs) {
            return JS::Any(lhs / rhs);
         },
         [](bool lhs, const std::string&rhs) {
            return JS::Any(lhs / std::stod(rhs));
         },

         // null
         [](JS::Null lhs, double rhs) {
            return JS::Any(0);
         },
         [](JS::Null lhs, const std::string&rhs) {
            return JS::Any(0);
         },
         [](JS::Null lhs, bool rhs) {
            return JS::Any(0);
         },

         // default
         [](const auto&, const auto&) {
            return JS::Any(std::numeric_limits <double>::quiet_NaN());
         }
      }, value, other.value));
   } catch (std::invalid_argument&e) {
      return(JS::Any(std::numeric_limits <double>::quiet_NaN()));
   }
}
