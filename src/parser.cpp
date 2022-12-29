#include "parser.h"

#include <utility>

parser::parser(lexer lex, error_handler error) :
    m_lex{std::move(lex)},
    m_error{std::move(error)},
    m_good{true} {
    m_scopes.push(scope::define);
}

parser::~parser() = default;

token parser::get_current_token() {
    return m_current_tok;
}

token& parser::get_next_token() {
    return m_current_tok = m_lex.get_next_token();
}

bool parser::good() const {
    return m_good;
}

void parser::check_next_token(utils::token::type expected_type, const std::string &error) {
    token& tok = get_next_token();
    if (tok.get_type() != expected_type) {
        m_error(tok, error);
        m_good = false;
    }
}


ast::ASTNode parser::parse_ast_node() {
    return ast::ASTNode(scope::define);
}

ident parser::parse_ident() {
    return std::make_unique<ast::Ident>(m_scopes.top(), std::move(m_current_tok));
}

variable parser::parse_variable() {
    return std::make_unique<ast::Variable>(m_scopes.top(), std::move(m_current_tok));
}

integer parser::parse_integer() {
    return std::make_unique<ast::Integer>(m_scopes.top(), std::move(m_current_tok));
}

type parser::parse_type() {
    return std::make_unique<ast::Type>(m_scopes.top(), std::move(m_current_tok));
}

modality parser::parse_modality() {
    return std::make_unique<ast::Modality>(m_scopes.top(), std::move(m_current_tok));
}

requirement parser::parse_requirement() {
    get_next_token();       // Eating '('
    requirement req = std::make_unique<ast::Requirement>(m_scopes.top(), std::move(m_current_tok));
    get_next_token();       // Eating ')'
    return req;
}

ast::ASTNode parser::parse_valued_requirement() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_term() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_formula() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_quantified_formula() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_modal_formula() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_predicate() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_eq_formula() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_actual_parameter() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_signature() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_simple_obs_condition() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_if_obs_condition() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_forall_obs_condition() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_action() {
    return ast::ASTNode(scope::define);
}

domain_item parser::parse_domain_item() {
    // todo: implement
    return {};
}

domain parser::parse_domain() {
    // Eating '('
    check_next_token(utils::token::punctuation::lpar, std::string{"Expected '('."});
    if (!good()) return nullptr;

    // Eating 'define'
    check_next_token(utils::token::scope::define, std::string{"Expected 'define'."});
    if (!good()) return nullptr;

    // Eating '('
    check_next_token(utils::token::punctuation::lpar, std::string{"Expected '('."});
    if (!good()) return nullptr;

    // Eating 'domain'
    check_next_token(utils::token::scope::domain, std::string{"Expected 'domain'."});
    if (!good()) return nullptr;

    // Eating domain name (ident)
    check_next_token(utils::token::basic::ident, std::string{"Expected identifier."});
    if (!good()) return nullptr;

    ident domain_name = std::make_unique<ast::Ident>(m_scopes.top(), std::move(m_current_tok));

    // Eating ')'
    check_next_token(utils::token::basic::ident, std::string{"Expected ')'."});
    if (!good()) return nullptr;

    domain_item_set domain_items;
    get_next_token();

    while (std::holds_alternative<utils::token::punctuation>(m_current_tok.get_type()) &&
            std::get<utils::token::punctuation>(m_current_tok.get_type()) == utils::token::punctuation::lpar) {
        domain_items.insert(parse_domain_item());
    }

    // Eating ')'
    check_next_token(utils::token::basic::ident, std::string{"Expected ')'."});
    if (!good()) return nullptr;

    return std::make_unique<ast::Domain>(m_scopes.top(), std::move(domain_name), std::move(domain_items));
}

ast::ASTNode parser::parse_action_type() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_literal() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_simple_postcondition() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_forall_postcondition() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_event() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_library() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_agent_group() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_epistemic_state() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_init() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_problem() {
    return ast::ASTNode(scope::define);
}

ast::ASTNode parser::parse_epddl_planning_task() {
    return ast::ASTNode(scope::define);
}
