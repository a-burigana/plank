#include "parser.h"

#include <utility>

parser::parser(lexer lex, error_handler error) :
    m_lex{std::move(lex)},
    m_error{std::move(error)},
    m_good{true} {
    m_scopes.push(scope::domain);
}

parser::~parser() = default;

//token parser::get_current_token() {
//    return m_current_tok;
//}

token parser::get_next_token() {
    return std::make_unique<Token>(m_lex.get_next_token());
}

bool parser::good() const {
    return m_good;
}

token parser::check_next_token(utils::token::type expected_type, const std::string &error) {
    token tok = get_next_token();
    if (!tok->has_type(expected_type)) {
        m_error(std::move(tok), error);
        m_good = false;
        return {};
    }
    return std::move(tok);
}


ast::ASTNode parser::parse_ast_node() {
    return ast::ASTNode(scope::domain);
}

ident parser::parse_ident() {
    return {}; // std::make_unique<ast::Ident>(m_scopes.top(), std::move(m_current_tok));
}

variable parser::parse_variable() {
    return {}; // std::make_unique<ast::Variable>(m_scopes.top(), std::move(m_current_tok));
}

integer parser::parse_integer() {
    return {}; // std::make_unique<ast::Integer>(m_scopes.top(), std::move(m_current_tok));
}

type parser::parse_type() {
    return {}; // std::make_unique<ast::Type>(m_scopes.top(), std::move(m_current_tok));
}

modality parser::parse_modality() {
    return {}; // std::make_unique<ast::Modality>(m_scopes.top(), std::move(m_current_tok));
}

requirement parser::parse_requirement() {
    token tok = get_next_token();       // Eating '('
    requirement req = std::make_unique<ast::Requirement>(m_scopes.top(), std::move(tok));
    get_next_token();       // Eating ')'
    return req;
}

ast::ASTNode parser::parse_valued_requirement() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_term() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_formula() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_quantified_formula() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_modal_formula() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_predicate() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_eq_formula() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_actual_parameter() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_signature() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_simple_obs_condition() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_if_obs_condition() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_forall_obs_condition() {
    return ast::ASTNode(scope::domain);
}

domain_libraries parser::parse_domain_act_type_libs() {
    m_scopes.push(scope::domain_act_type_libs);
    token tok;
    ident_set ids;
    bool end = false;

    do {
        tok = get_next_token();
        if (!m_lex.good()) return {};

        m_good = tok->has_type(utils::token::basic::ident) ||
                 tok->has_type(utils::token::punctuation::rpar);

        if (m_good) {
            if (tok->has_type(utils::token::basic::ident)) {
                // If we eat an ident
                ident id = std::make_unique<ast::Ident>(m_scopes.top(), std::move(tok));
                ids.insert(std::move(id));
            } else if (tok->has_type(utils::token::punctuation::rpar)) {
                // If we eat ')'
                m_scopes.pop();
                end = true;
            }
        }
    } while (m_good && !end);

    if (!m_good) {
        m_error(std::move(tok), std::string{"Syntax error."});      // todo: handle error
        return {};
    }
    return std::make_unique<ast::DomainLibraries>(m_scopes.top(), std::move(ids));
}

domain_requirements parser::parse_domain_requirements() {
    m_scopes.push(scope::domain_requirements);
    token tok;
    requirement_set reqs;
    bool end = false;

    do {
        tok = get_next_token();
        if (!m_lex.good()) return {};

        m_good = std::get_if<utils::token::requirement>(&tok->get_type()) ||
                 tok->has_type(utils::token::punctuation::rpar);

        if (m_good) {
            if (std::get_if<utils::token::requirement>(&tok->get_type())) {
                // If the current token is one of the admitted requirements
                requirement req = std::make_unique<ast::Requirement>(m_scopes.top(), std::move(tok));
                reqs.insert(std::move(req));
            } else if (tok->has_type(utils::token::punctuation::rpar)) {
                // If we eat ')'
                m_scopes.pop();
                end = true;
            }
        }
    } while (m_good && !end);

    if (!m_good) {
        m_error(std::move(tok), std::string{"Syntax error."});      // todo: handle error
        return {};
    }
    return std::make_unique<ast::DomainRequirements>(m_scopes.top(), std::move(reqs));
}

domain_types parser::parse_domain_types() {
    m_scopes.push(scope::domain_types);

    return {};
}

domain_predicates parser::parse_domain_predicates() {
    m_scopes.push(scope::domain_predicates);

    return {};
}

domain_modalities parser::parse_domain_modalities() {
    m_scopes.push(scope::domain_modalities);

    return {};
}

action parser::parse_action() {
    m_scopes.push(scope::action);

    return {};
}

domain_item parser::parse_domain_item() {
    token tok = get_next_token();

    if (tok->has_type(utils::token::keyword::act_type_lib)) {
        return parse_domain_act_type_libs();
    } else if (tok->has_type(utils::token::keyword::requirements)) {
        return parse_domain_requirements();
    } else if (tok->has_type(utils::token::keyword::types)) {
        return parse_domain_requirements();
    } else if (tok->has_type(utils::token::keyword::predicates)) {
        return parse_domain_types();
    } else if (tok->has_type(utils::token::keyword::modalities)) {
        return parse_domain_predicates();
    } else if (tok->has_type(utils::token::keyword::action)) {
        return parse_domain_modalities();
    } else {
        m_error(std::move(tok), std::string{"Syntax error."});      // todo: handle error
        m_good = false;
        return {};
    }
}

domain parser::parse_domain() {
    // Eating '('
    check_next_token(utils::token::punctuation::lpar, std::string{"Expected '('."});
    if (!good()) return nullptr;

    // Eating 'define'
    check_next_token(utils::token::keyword::define, std::string{"Expected 'define'."});
    if (!good()) return nullptr;
    m_scopes.push(scope::domain);

    // Eating '('
    check_next_token(utils::token::punctuation::lpar, std::string{"Expected '('."});
    if (!good()) return nullptr;

    // Eating 'domain'
    check_next_token(utils::token::keyword::domain, std::string{"Expected 'domain'."});
    if (!good()) return nullptr;
    m_scopes.push(scope::domain_name);

    // Eating domain name (ident)
    token tok = check_next_token(utils::token::basic::ident, std::string{"Expected identifier."});
    if (!good()) return nullptr;

    ident domain_name = std::make_unique<ast::Ident>(m_scopes.top(), std::move(tok));

    // Eating ')'
    check_next_token(utils::token::basic::ident, std::string{"Expected ')'."});
    if (!good()) return nullptr;
    m_scopes.pop();

    domain_item_set domain_items;
    bool end = false;

    do {
        // Eating either '(' or ')'
        tok = get_next_token();
        if (!good()) return nullptr;

        m_good = tok->has_type(utils::token::punctuation::lpar) ||
                 tok->has_type(utils::token::punctuation::rpar);

        if (m_good) {
            if (tok->has_type(utils::token::punctuation::rpar)) {
                // If we eat ')'
                m_scopes.pop();
                end = true;
            } else if (tok->has_type(utils::token::punctuation::lpar)) {
                // If we eat '('
                domain_items.insert(parse_domain_item());
            }
        }
    } while (m_good && !end);

    if (!m_good) {
        m_error(std::move(tok), std::string{"Syntax error."});      // todo: handle error
        return {};
    }
    return std::make_unique<ast::Domain>(m_scopes.top(), std::move(domain_name), std::move(domain_items));
}

ast::ASTNode parser::parse_action_type() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_literal() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_simple_postcondition() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_forall_postcondition() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_event() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_library() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_agent_group() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_epistemic_state() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_init() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_problem() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_epddl_planning_task() {
    return ast::ASTNode(scope::domain);
}
