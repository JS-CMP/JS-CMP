#ifndef DECLARATION_HPP
#define DECLARATION_HPP

// Type lists
#define FOR_EACH_CONVERSION_TYPE(B, A) \
B int value A; \
B double value A; \
B bool value A; \
B unsigned int value A; \
B const char* value A; \
B const char16_t* value  A; \
B const std::string& value A; \
B const std::u16string& value A; \
B const Rope& value A; \
B JS::Undefined value A; \
B JS::Null value A; \

#define L_BRACKET() (
#define R_BRACKET() )
#define COMMA ,

#define DECLARE_1FUNC(BEFORE, AFTER) \
  FOR_EACH_CONVERSION_TYPE(BEFORE L_BRACKET(), R_BRACKET() AFTER) \
  BEFORE (const JS::Any& value) AFTER; \

#define DECLARE_1FUNC_TEMPLATE(BEFORE, AFTER) \
  FOR_EACH_CONVERSION_TYPE(BEFORE L_BRACKET(), COMMA const JS::Any& value R_BRACKET() AFTER) \
  BEFORE (const JS::Any& value) AFTER; \

#define DECLARE_2FUNC(BEFORE, AFTER) \
  FOR_EACH_CONVERSION_TYPE(BEFORE  L_BRACKET(), COMMA const JS::Any& any R_BRACKET() AFTER)

#define DECLARE_2FUNC_TWO_WAYS(BEFORE, AFTER) \
  FOR_EACH_CONVERSION_TYPE(BEFORE L_BRACKET(), COMMA const JS::Any& any R_BRACKET() AFTER) \
  FOR_EACH_CONVERSION_TYPE(BEFORE L_BRACKET()const JS::Any& any COMMA,  R_BRACKET()  AFTER)

#endif //DECLARATION_HPP