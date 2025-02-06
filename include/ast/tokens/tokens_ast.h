#ifndef EPDDL_TOKENS_AST_H
#define EPDDL_TOKENS_AST_H

#include "../../ast/ast_node.h"
#include "../../generators/tokens/token_types_gen.h"
#include "../../lexer/token.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class identifier;
    class variable;
    class modality_name;
    class integer;
    class requirement;

    using identifier_ptr    = std::unique_ptr<ast::identifier>;
    using variable_ptr      = std::unique_ptr<ast::variable>;
    using modality_name_ptr = std::unique_ptr<ast::modality_name>;
    using integer_ptr       = std::unique_ptr<ast::integer>;
    using requirement_ptr   = std::unique_ptr<ast::requirement>;

    using identifier_list   = std::list<identifier_ptr>;
    using variable_list     = std::list<variable_ptr>;

    class identifier : public ast_node {
    public:
        using token_type = pattern_token::identifier;

        explicit identifier(token_ptr tok) :
                m_token{std::move(tok)} {}

        [[nodiscard]] const token& get_token() const { return *m_token; }

    private:
        const token_ptr m_token;
    };

    class variable : public identifier {
    public:
        using token_type = pattern_token::variable;

        explicit variable(token_ptr var) :
                identifier{std::move(var)} {}
    };

    class modality_name : public ast_node {
    public:
        using token_type = modality_token::modality;

        explicit modality_name(token_ptr tok) :
                m_token{std::move(tok)} {}

        [[nodiscard]] const token& get_token() const { return *m_token; }

    private:
        const token_ptr m_token;
    };

    class integer : public ast_node {
    public:
        using token_type = pattern_token::integer;

        explicit integer(token_ptr val) :
                m_token{std::move(val)} {}

        [[nodiscard]] std::string get_val() const { return m_token->get_lexeme(); }

    private:
        const token_ptr m_token;
    };

    class requirement : public ast_node {
    public:
        using token_type = pattern_token::requirement;

        explicit requirement(token_ptr req, std::optional<integer_ptr> val = std::nullopt) :
                m_req{std::move(req)},
                m_val{std::move(val)} {}

    private:
        const token_ptr m_req;
        const std::optional<integer_ptr> m_val;
    };
}

#endif //EPDDL_TOKENS_AST_H
