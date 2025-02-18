#ifndef EPDDL_MODALITIES_DECL_PARSER_H
#define EPDDL_MODALITIES_DECL_PARSER_H

#include "../../ast/common/modalities_decl_ast.h"
#include "../parser_helper.h"

namespace epddl::parser {
    class modalities_decl_parser {
    public:
        static ast::modalities_decl_ptr parse(parser_helper &helper);
    };
}

#endif //EPDDL_MODALITIES_DECL_PARSER_H
