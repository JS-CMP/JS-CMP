#ifndef DECLARATION_HPP
#define DECLARATION_HPP

// Type lists
#define FOR_EACH_CONVERSION_TYPE(B, A)                                                                                 \
    B int value A;                                                                                                     \
    B double value A;                                                                                                  \
    B bool value A;                                                                                                    \
    B unsigned int value A;                                                                                            \
    B const char* value A;                                                                                             \
    B const char16_t* value A;                                                                                         \
    B const std::string& value A;                                                                                      \
    B const std::u16string& value A;                                                                                   \
    B const Rope& value A;                                                                                             \
    B JS::Undefined value A;                                                                                           \
    B JS::Null value A;

#define L_PAREN() (
#define R_PAREN() )
#define COMMA ,

#define DECLARE_1FUNC(FUNC_HEAD, FUNC_TAIL)                                                                            \
    FOR_EACH_CONVERSION_TYPE(FUNC_HEAD L_PAREN(), R_PAREN() FUNC_TAIL)                                                 \
    FUNC_HEAD(const JS::Operator& value) FUNC_TAIL;

#define DECLARE_2FUNC(FUNC_HEAD, FUNC_TAIL)                                                                            \
    FOR_EACH_CONVERSION_TYPE(FUNC_HEAD L_PAREN(), COMMA const JS::Operator& any R_PAREN() FUNC_TAIL)

#define DECLARE_2FUNC_TWO_WAYS(FUNC_HEAD, FUNC_TAIL)                                                                   \
    FOR_EACH_CONVERSION_TYPE(FUNC_HEAD L_PAREN(), COMMA const JS::Any& any R_PAREN() FUNC_TAIL)                        \
    FOR_EACH_CONVERSION_TYPE(FUNC_HEAD L_PAREN() const JS::Any& any COMMA, R_PAREN() FUNC_TAIL)

#endif // DECLARATION_HPP