#ifndef TRYCATCHFINALLY_HPP
#define TRYCATCHFINALLY_HPP

enum TCF_JMP_STATE {
    RETURN,
    BREAK,
    CONTINUE,
    THROW,
};

#define TCF_RETURN(val)                                                                                                \
    __tcf_value = (val);                                                                                               \
    __tcf_state = RETURN;                                                                                              \
    goto finally;
#define TCF_BREAK                                                                                                      \
    __tcf_state = BREAK;                                                                                               \
    goto finally;
#define TCF_CONTINUE                                                                                                   \
    __tcf_state = CONTINUE;                                                                                            \
    goto finally;
#define TCF_THROW(val)                                                                                                 \
    __tcf_value = (val);                                                                                               \
    __tcf_state = THROW;                                                                                               \
    goto finally;

#define TCF(tryBlock, catchVar, catchBlock, finallyBlock)                                                              \
    {                                                                                                                  \
        std::optional<JS::Any> __tcf_value;                                                                            \
        std::optional<TCF_JMP_STATE> __tcf_state;                                                                      \
        try {                                                                                                          \
            tryBlock                                                                                                   \
        } catch (std::exception & catchVar) { /* TODO change to catch JS::Any */                                       \
            catchBlock                                                                                                 \
        } finally : finallyBlock if (__tcf_state.has_value()) {                                                        \
            switch (__tcf_state.value()) {                                                                             \
                case RETURN:                                                                                           \
                    return __tcf_value.value();                                                                        \
                case BREAK:                                                                                            \
                    break;                                                                                             \
                case CONTINUE:                                                                                         \
                    continue;                                                                                          \
                case THROW:                                                                                            \
                    throw __tcf_value.value();                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }
#endif // TRYCATCHFINALLY_HPP
