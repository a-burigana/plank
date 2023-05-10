#ifndef EPDDL_PARSER_H
#define EPDDL_PARSER_H

#include "../lex/lex.h"
#include "../generators/ast/ast_gen.h"

using namespace epddl;

class parser {
public:
    parser(lexer& lex);
    ~parser() = default;

private:
    lexer& m_lex;
    std::optional<token_ptr> m_current_token;
    std::list<token_ptr> m_next_tokens;
    std::stack<std::pair<unsigned long, const token_ptr*>> m_scopes;
    unsigned long m_lpar_count;

    template<typename token_type>
    [[nodiscard]] bool has_type(const token_ptr &tok) const;
//    template<typename token_type>
//    [[nodiscard]] bool is_scope_token() const;

//    template<typename token_type>
    void get_next_token();
    void peek_next_token();

    const token_ptr& get_last_peeked_token();

    template<typename token_type>
    bool is_next_token_type();
    template<typename token_type>
    void check_current_token();
    template<typename token_type>
    void check_next_token();
    template<class ast_node, typename token_type>
    std::unique_ptr<ast_node> get_node_from_next_token();
};


#endif //EPDDL_PARSER_H
