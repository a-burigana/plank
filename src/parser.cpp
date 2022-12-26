#include "parser.h"

#include <utility>

parser::parser(lexer lex, error_handler error) :
    m_lex{std::move(lex)},
    m_error{std::move(error)},
    m_good{true} {}

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

void parser::check_next_token(token::type expected_type, const std::string &error) {
    token& tok = get_next_token();
    if (tok.get_type() != expected_type) {
        m_error(tok, error);
        m_good = false;
    }
}


ASTNode parser::parse_ast_node() {
    return ASTNode();
}

ident parser::parse_ident() {
    return std::make_unique<Ident>(std::move(m_current_tok));
}

variable parser::parse_variable() {
    return std::make_unique<Variable>(std::move(m_current_tok));
}

integer parser::parse_integer() {
    return std::make_unique<Integer>(std::move(m_current_tok));
}

type parser::parse_type() {
    return std::make_unique<Type>(std::move(m_current_tok));
}

modality parser::parse_modality() {
    return std::make_unique<Modality>(std::move(m_current_tok));
}

requirement parser::parse_requirement() {
    get_next_token();       // Eating '('
    requirement req = std::make_unique<Requirement>(std::move(m_current_tok));
    get_next_token();       // Eating ')'
    return req;
}

ASTNode parser::parse_valued_requirement() {
    return ASTNode();
}

ASTNode parser::parse_term() {
    return ASTNode();
}

ASTNode parser::parse_formula() {
    return ASTNode();
}

ASTNode parser::parse_quantified_formula() {
    return ASTNode();
}

ASTNode parser::parse_modal_formula() {
    return ASTNode();
}

ASTNode parser::parse_predicate() {
    return ASTNode();
}

ASTNode parser::parse_eq_formula() {
    return ASTNode();
}

ASTNode parser::parse_actual_parameter() {
    return ASTNode();
}

ASTNode parser::parse_signature() {
    return ASTNode();
}

ASTNode parser::parse_simple_obs_condition() {
    return ASTNode();
}

ASTNode parser::parse_if_obs_condition() {
    return ASTNode();
}

ASTNode parser::parse_forall_obs_condition() {
    return ASTNode();
}

ASTNode parser::parse_action() {
    return ASTNode();
}

domain_item parser::parse_domain_item() {

}

domain parser::parse_domain() {
    // Eating '('
    check_next_token(token::type::_LPAR, std::string{"Expected '('."});
    if (!good()) return nullptr;

    // Eating 'define'
    check_next_token(token::type::_EPDDL_DEF, std::string{"Expected 'define'."});
    if (!good()) return nullptr;

    // Eating '('
    check_next_token(token::type::_LPAR, std::string{"Expected '('."});
    if (!good()) return nullptr;

    // Eating 'domain'
    check_next_token(token::type::_EPDDL_DOM, std::string{"Expected 'domain'."});
    if (!good()) return nullptr;

    // Eating domain name (ident)
    check_next_token(token::type::_IDENT, std::string{"Expected identifier."});
    if (!good()) return nullptr;

    ident domain_name = std::make_unique<Ident>(Ident{get_current_token()});

    // Eating ')'
    check_next_token(token::type::_IDENT, std::string{"Expected ')'."});
    if (!good()) return nullptr;

    domain_item_set domain_items;
    get_next_token();

    while (m_current_tok.get_type() == token::type::_LPAR) {
        domain_items.insert(parse_domain_item());
    }

    // Eating ')'
    check_next_token(token::type::_IDENT, std::string{"Expected ')'."});
    if (!good()) return nullptr;

    return std::make_unique<Domain>(std::move(domain_name), std::move(domain_items));
}

ASTNode parser::parse_action_type() {
    return ASTNode();
}

ASTNode parser::parse_literal() {
    return ASTNode();
}

ASTNode parser::parse_simple_postcondition() {
    return ASTNode();
}

ASTNode parser::parse_forall_postcondition() {
    return ASTNode();
}

ASTNode parser::parse_event() {
    return ASTNode();
}

ASTNode parser::parse_library() {
    return ASTNode();
}

ASTNode parser::parse_agent_group() {
    return ASTNode();
}

ASTNode parser::parse_epistemic_state() {
    return ASTNode();
}

ASTNode parser::parse_init() {
    return ASTNode();
}

ASTNode parser::parse_problem() {
    return ASTNode();
}

ASTNode parser::parse_epddl_planning_task() {
    return ASTNode();
}
