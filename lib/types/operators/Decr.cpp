#include "../../../includes/types/JsAny.hpp"

JS::Any & JS::Any::operator--()
{
   try {
      std::visit(overloaded{
         // types
         [](double&hs) {
            --hs;
         },
         [this](std::string&hs) {
            value = static_cast <double>(std::stod(hs) - 1);
         },
         [this](bool&hs) {
            value = static_cast <double>(hs - 1);
         },
         [this](JS::Null&) {
            value = static_cast <double>(-1);
         },

         // default
         [](auto&) {
         }
      }, value);
   } catch (const std::invalid_argument&e) {
      value = std::numeric_limits <double>::quiet_NaN();
   }
   return(*this);
}

JS::Any&JS::Any::operator--(int)
{
   try {
      std::visit(overloaded{
         // types
         [](double&hs) {
            hs--;
         },
         [this](std::string&hs) {
            value = static_cast <double>(std::stod(hs) - 1);
         },
         [this](bool&hs) {
            value = static_cast <double>(hs - 1);
         },
         [this](JS::Null&) {
            value = static_cast <double>(-1);
         },

         // default
         [](auto&) {
         }
      }, value);
   } catch (const std::invalid_argument&e) {
      value = std::numeric_limits <double>::quiet_NaN();
   }
   return(*this);
}
