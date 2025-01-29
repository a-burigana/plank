#ifndef EPDDL_MODALITIES_DECL_PARSER_H
#define EPDDL_MODALITIES_DECL_PARSER_H

#include "../../ast/ast.h"
#include "../parser_helper.h"

namespace epddl {
    class modalities_decl_parser {
    public:
        static ast::domain_modalities_ptr parse(parser_helper &helper);
    };
}

#endif //EPDDL_MODALITIES_DECL_PARSER_H
