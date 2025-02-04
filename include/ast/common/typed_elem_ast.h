#ifndef EPDDL_TYPED_ELEM_AST_H
#define EPDDL_TYPED_ELEM_AST_H

#include "../../ast/ast_node.h"
#include "../tokens/tokens_ast.h"
#include <list>
#include <memory>
#include <optional>

namespace epddl::ast {
    template<typename token_type>
    class typed_elem;

    using typed_identifier      = typed_elem<identifier>;
    using typed_variable        = typed_elem<variable>;

    using typed_identifier_ptr  = std::unique_ptr<typed_identifier>;
    using typed_variable_ptr    = std::unique_ptr<typed_variable>;
    using typed_identifier_list = std::list<typed_identifier_ptr>;
    using typed_variable_list   = std::list<typed_variable_ptr>;

    using formal_param          = typed_variable_ptr;
    using formal_param_list     = std::list<formal_param>;

    template<typename token_type>
    class typed_elem : public ast_node {
    public:
        using token_type_ptr = std::unique_ptr<token_type>;

        explicit typed_elem(token_type_ptr id, std::optional<identifier_ptr> type = std::nullopt) :
                m_id{std::move(id)},
                m_type{std::move(type)} {}

    private:
        const token_type_ptr m_id;
        const std::optional<identifier_ptr> m_type;
    };
}

#endif //EPDDL_TYPED_ELEM_AST_H
