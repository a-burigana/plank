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
    template<typename token_type>
    using typed_elem_ptr        = std::unique_ptr<ast::typed_elem<token_type>>;
    template<typename token_type>
    using typed_elem_list       = std::list<typed_elem_ptr<token_type>>;

    using typed_identifier_ptr  = typed_elem_ptr<identifier>;
    using typed_variable_ptr    = typed_elem_ptr<variable>;
    using typed_identifier_list = std::list<typed_identifier_ptr>;
    using typed_variable_list   = std::list<typed_variable_ptr>;

    using formal_param          = typed_variable_ptr;
    using formal_param_list     = std::list<formal_param>;

    template<typename token_type>
    class typed_elem : public ast_node {
    public:
        explicit typed_elem(identifier_ptr id, std::optional<identifier_ptr> type = std::nullopt) :
                m_id{std::move(id)},
                m_type{std::move(type)} {}

    private:
        const identifier_ptr m_id;
        const std::optional<identifier_ptr> m_type;
    };
}

#endif //EPDDL_TYPED_ELEM_AST_H
