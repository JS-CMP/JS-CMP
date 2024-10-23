#include <cmath>
#include "../../includes/types/JsAny.hpp"

bool JS::Any::operator==(const JS::Any&other) const
{
   return(std::visit(overloaded{
      [](double lhs, double rhs) {
         return lhs == rhs;
      },
      [](const std::string&lhs, const std::string&rhs) {
         return lhs == rhs;
      },
      [](bool lhs, bool rhs) {
         return lhs == rhs;
      },
      [](const auto&, const auto&)->bool {
         return false;
      }
   }, value, other.value));
}

JS::Any JS::Any::operator()(std::vector <JS::Any>&args)
{
   if (!std::holds_alternative <JS::Function>(value))
   {
      throw std::runtime_error("Value is not a function");
   }
   return(std::get <JS::Function>(value)(args));
}

std::string JS::Any::toString() const
{
   return(std::visit(overloaded{
      [](double v)->std::string {
         return std::isnan(v) ? "NaN" :
         std::isinf(v) ? v < 0 ?
         "-Infinity" :
         "Infinity" :
         std::to_string(v);
      },
      [](const std::string&v)->std::string {
         return v;
      },
      [](bool v)->std::string {
         return v ? "true" : "false";
      },
      [](const JS::Function&)->std::string {
         return "[Function]";
      },
      [](const JS::Undefined&)->std::string {
         return "undefined";
      },
      [](const JS::Null&)->std::string {
         return "null";
      },
      [](const auto&)->std::string {
         return "[Object]";
      }
   }, value));
}

std::ostream&JS::operator<<(std::ostream&os, const JS::Any&any)
{
   os << any.toString();
   return(os);
}
