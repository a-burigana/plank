#ifndef EPDDL_PARSER_H
#define EPDDL_PARSER_H

#include "../lex/lex.h"
#include "../generators/ast/ast_gen.h"

namespace epddl {
    class parser {
    public:
        parser(lexer &lex);
        ~parser() = default;

    private:
        lexer &m_lex;
        std::optional<token_ptr> m_current_token;
        std::list<token_ptr> m_next_tokens;
        std::stack<std::pair<unsigned long, const token_ptr *>> m_scopes;
        unsigned long m_lpar_count;

        template<typename token_type>
        [[nodiscard]] bool has_type(const token_ptr &tok) const;

        void get_next_token();
        void peek_next_token();
        const token_ptr &get_last_peeked_token();

        template<typename token_type>
        bool is_next_token_type();

        template<typename token_type>
        void check_current_token();

        template<typename token_type>
        void check_next_token();

        template<class node_type, typename token_type>
        std::unique_ptr<node_type> get_node_from_next_token();

        template<class node_type>
        std::list<node_type> parse_list(std::function<node_type()> parse_elem, bool is_optional_list);

        #define function_name0(arg) parse_##arg
        #define function_name(arg) function_name0(arg)

        #define element_name(name) name
        #define epddl_element(name, _, __) ast::unique_ptr(name) function_name(name)();
        // Prototypes of parsing functions
        epddl_all_element_defs

        #undef epddl_element
        #undef element_name
    };
}

#endif //EPDDL_PARSER_H
