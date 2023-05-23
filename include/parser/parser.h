#ifndef EPDDL_PARSER_H
#define EPDDL_PARSER_H

#include <memory>
#include <vector>
#include "../lex/lex.h"
#include "../generators/ast/ast_gen.h"

namespace epddl {
    class parser {
    public:
        parser(lexer &lex);
        ~parser() = default;

        ast::domain_ptr parse();

    private:
        lexer &m_lex;
        std::optional<token_ptr> m_current_token, m_end_list_token;
        std::vector<token_ptr> m_next_tokens;
        unsigned int m_cursor_token_index;
        bool m_choice_point, m_first_choice_point_rule;

        std::stack<std::pair<unsigned long, const token_ptr*>> m_scopes;
        unsigned long m_lpar_count;

        template<typename token_type>
        [[nodiscard]] bool has_type(token_ptr &tok) const;

        void peek_next_token();
        token_ptr& get_last_peeked_token();
        token_ptr& get_cursor_token();

        template<typename token_type>
        bool is_next_token_type();

        template<typename token_type>
        bool check_next_peeked_token();

        void get_next_token();
        void update_scopes(const token_ptr& token);

        template<typename token_type>
        void check_current_token();

        template<typename token_type>
        void check_next_token();

        template<typename token_type>
        std::unique_ptr<token<token_type>> get_leaf_from_next_token(bool is_optional = false);

        bool is_end_list();

        template<class node_type>
        std::list<node_type> parse_list(std::function<node_type()> parse_elem, bool is_optional_list);

        template<class variant_node_type, class node_type>
        std::pair<bool, std::unique_ptr<variant_node_type>> parse_variant_node(std::function<std::unique_ptr<node_type>()> parse_elem);

        template<class variant_leaf_type, typename token_type>
        std::pair<bool, std::unique_ptr<variant_leaf_type>> parse_variant_leaf();

        #define decl_parse_node_function0(arg) parse_##arg(bool is_optional)
        #define decl_parse_node_function(arg) decl_parse_node_function0(arg)

        #define decl_parse_node_function_opt0(arg) parse_##arg(bool is_optional = false)
        #define decl_parse_node_function_opt(arg) decl_parse_node_function_opt0(arg)

        #define call_parse_node_function0(arg) parse_##arg()
        #define call_parse_node_function(arg) call_parse_node_function0(arg)

        #define call_parse_node_function_opt0(arg) parse_##arg(true)
        #define call_parse_node_function_opt(arg) call_parse_node_function_opt0(arg)

        #define element_name(name) name
        #define epddl_element(name, _, __) ast::unique_ptr(name) decl_parse_node_function_opt(name);
        // Prototypes of parsing functions
        epddl_all_element_defs
        #undef epddl_element

        #define epddl_variant_element(name, _) ast::unique_ptr(name) decl_parse_node_function_opt(name);
        // Prototypes of parsing functions
        epddl_all_variant_element_defs
        #undef epddl_variant_element
        #undef element_name
    };
}

#endif //EPDDL_PARSER_H
