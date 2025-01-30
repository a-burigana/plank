#ifndef EPDDL_INITIAL_STATE_DECL_AST_H
#define EPDDL_INITIAL_STATE_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class initial_state_decl;
    using initial_state_decl_ptr = std::unique_ptr<initial_state_decl>;

    class initial_state_decl : public ast_node {
    public:
        explicit initial_state_decl() = default;

    private:
    };
}

#endif //EPDDL_INITIAL_STATE_DECL_AST_H
