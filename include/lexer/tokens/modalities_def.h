#ifndef EPDDL_MODALITIES_DEF_H
#define EPDDL_MODALITIES_DEF_H

#include "tokens_def.h"

#define epddl_modality_keywords \
    epddl_mod_keyword("C.")     \
    epddl_mod_keyword("Kw.")

#define epddl_all_modalities \
    all_modalities(          \
        epddl_tok_ck,        \
        epddl_tok_kw,        \
        epddl_tok_modality   \
    )                        \

#endif //EPDDL_MODALITIES_DEF_H
