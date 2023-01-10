#include "parser.h"

#include <utility>

parser::parser(lexer lex, error_handler error) :
    m_lex{std::move(lex)},
    m_current_tok{std::nullopt},
    m_error{std::move(error)},
    m_good{true} {
    m_scopes.push(scope::domain);
}

parser::~parser() = default;

//token parser::get_current_token() {
//    return m_current_tok;
//}

void parser::get_next_token() {
    m_current_tok.emplace(m_lex.get_next_token());
}

bool parser::good() const {
    return m_good;
}

void parser::check_current_token(utils::token::type expected_type, const std::string &error) {
    if (!m_current_tok->has_type(expected_type)) {
        m_error(*m_current_tok, error);
        m_good = false;
    }
}

void parser::check_next_token(utils::token::type expected_type, const std::string &error) {
    get_next_token();
    check_current_token(expected_type, error);
}

ast::ASTNode parser::parse_ast_node() {
    return ast::ASTNode(scope::domain);
}

ident parser::parse_ident() {
    get_next_token();
    m_good = m_current_tok->has_type(utils::token::basic::ident);

    if (m_good) {
        return std::make_unique<ast::Ident>(m_scopes.top(), std::move(*m_current_tok));
    } else {
        m_error(*m_current_tok, std::string{"Expected identifier."});
        return {};
    }
}

variable parser::parse_variable() {
    return {}; // std::make_unique<ast::Variable>(m_scopes.top(), std::move(m_current_tok));
}

integer parser::parse_integer() {
    return {}; // std::make_unique<ast::Integer>(m_scopes.top(), std::move(m_current_tok));
}

type parser::parse_type() {
    get_next_token();
    m_good = m_current_tok->has_type(utils::token::basic::ident);

    if (m_good) {
        return std::make_unique<ast::Type>(m_scopes.top(), std::move(*m_current_tok));
    } else {
        m_error(*m_current_tok, std::string{"Expected identifier."});
        return {};
    }
}

modality parser::parse_modality() {
    return {}; // std::make_unique<ast::Modality>(m_scopes.top(), std::move(m_current_tok));
}

requirement parser::parse_requirement() {
    get_next_token();
    m_good = std::get_if<utils::token::requirement>(&m_current_tok->get_type());

    if (m_good) {
        return std::make_unique<ast::Requirement>(m_scopes.top(), std::move(*m_current_tok));
    } else {
        m_error(*m_current_tok, std::string{"Expected requirement."});
        return {};
    }
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

predicate parser::parse_predicate() {
    check_next_token(utils::token::basic::ident, std::string{"Expected identifier."});
    ident name = std::make_unique<ast::Ident>(m_scopes.top(), std::move(*m_current_tok));

    return {};
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

template<class T>
std::list<T> parser::parse_list(std::function<T()> parse_elem) {
    std::list<T> elems;
    bool end = false;

    do {
        get_next_token();     // todo: ma questo deve davvero andare qui?

        if (m_current_tok->has_type(utils::token::punctuation::rpar)) {
            // If we eat ')'
            m_scopes.pop();
            end = true;
        } else {
            // Otherwise we parse the element and, if we are successful, we add it to the list
            // Errors concerning unexpected tokens are handled by parse_elem()
            elems.push_back(parse_elem());
        }
    } while (!end);     // m_good &&

//    if (!m_good) {
//        m_error(std::move(tok), std::move(error_msg));
//        return {};
//    }
    return std::move(elems);
}

domain_libraries parser::parse_domain_act_type_libs() {
    m_scopes.push(scope::domain_act_type_libs);

    std::function<ident()> parse_elem = [this] () { return parse_ident(); };
    ident_list ids = parse_list(parse_elem);

    return std::make_unique<ast::DomainLibraries>(m_scopes.top(), std::move(ids));
}

domain_requirements parser::parse_domain_requirements() {
    m_scopes.push(scope::domain_requirements);

    std::function<requirement ()> parse_elem = [this] () { return parse_requirement(); };
    requirement_list reqs = parse_list(parse_elem);

    return std::make_unique<ast::DomainRequirements>(m_scopes.top(), std::move(reqs));
}

domain_types parser::parse_domain_types() {
    m_scopes.push(scope::domain_types);

    std::function<type()> parse_elem = [this] () { return parse_type(); };
    type_list types = parse_list(parse_elem);

    return std::make_unique<ast::DomainTypes>(m_scopes.top(), std::move(types));
}

std::optional<formal_param_list> parser::parse_formal_param_list() {
    get_next_token();   // Reading the first variable
    
    if (!m_current_tok->has_type(utils::token::basic::variable)) {
        return std::nullopt;
    }

    formal_param_list params;
    
    while (!m_current_tok->has_type(utils::token::basic::variable)) {
        variable var = std::make_unique<ast::Variable>(m_scopes.top(), std::move(*m_current_tok));
        std::optional<type> type = std::nullopt;

        get_next_token();       // Reading either '-' or another variable

        if (m_current_tok->has_type(utils::token::punctuation::dash)) {
            get_next_token();       // Reading the type of the variable

            check_next_token(utils::token::basic::ident, std::string{"Expected type identifier."});
            type = std::make_unique<ast::Type>(m_scopes.top(), std::move(*m_current_tok));

            get_next_token();       // Moving to the next variable
        }

        formal_param param = std::make_pair(std::move(var), std::move(type));
        params.push_back(std::move(param));
    }

    return std::move(params);
}

predicate_def parser::parse_predicate_def() {
    check_next_token(utils::token::punctuation::lpar, std::string{"Expected '('."});
    if (!good()) return {};
    
    check_next_token(utils::token::basic::ident, std::string{"Expected identifier."});
    if (!good()) return {};
    
    ident name = std::make_unique<ast::Ident>(m_scopes.top(), std::move(*m_current_tok));
    std::optional<formal_param_list> params = parse_formal_param_list();

    // The last token read in function parse_formal_param_list() is not used, so we check it here
    check_current_token(utils::token::punctuation::rpar, std::string{"Expected ')'."});
    if (!good()) return {};

    return std::make_unique<ast::PredicateDef>(m_scopes.top(), std::move(name), std::move(params));
}

domain_predicates parser::parse_domain_predicates() {
    m_scopes.push(scope::domain_predicates);

    std::function<predicate_def()> parse_elem = [this] () { return parse_predicate_def(); };
    predicate_def_list preds = parse_list(parse_elem);

    return std::make_unique<ast::DomainPredicates>(m_scopes.top(), std::move(preds));
}

domain_modalities parser::parse_domain_modalities() {
    m_scopes.push(scope::domain_modalities);

    std::function<modality()> parse_elem = [this] () { return parse_modality(); };
    modality_list mods = parse_list(parse_elem);

    return std::make_unique<ast::DomainModalities>(m_scopes.top(), std::move(mods));
}

action parser::parse_action() {
    m_scopes.push(scope::action);

    return {};
}

domain_item parser::parse_domain_item() {
    get_next_token();

    if (m_current_tok->has_type(utils::token::keyword::act_type_lib)) {
        return parse_domain_act_type_libs();
    } else if (m_current_tok->has_type(utils::token::keyword::requirements)) {
        return parse_domain_requirements();
    } else if (m_current_tok->has_type(utils::token::keyword::types)) {
        return parse_domain_requirements();
    } else if (m_current_tok->has_type(utils::token::keyword::predicates)) {
        return parse_domain_types();
    } else if (m_current_tok->has_type(utils::token::keyword::modalities)) {
        return parse_domain_predicates();
    } else if (m_current_tok->has_type(utils::token::keyword::action)) {
        return parse_domain_modalities();
    } else {
        m_error(*m_current_tok, std::string{"Syntax error."});      // todo: handle error
        m_good = false;
        return {};
    }
}

domain parser::parse_domain() {
    // Eating '('
    check_next_token(utils::token::punctuation::lpar, std::string{"Expected '('."});
    if (!good()) return {};

    // Eating 'define'
    check_next_token(utils::token::keyword::define, std::string{"Expected 'define'."});
    if (!good()) return {};
    m_scopes.push(scope::domain);

    // Eating '('
    check_next_token(utils::token::punctuation::lpar, std::string{"Expected '('."});
    if (!good()) return {};

    // Eating 'domain'
    check_next_token(utils::token::keyword::domain, std::string{"Expected 'domain'."});
    if (!good()) return {};
    m_scopes.push(scope::domain_name);

    // Eating domain name (ident)
    check_next_token(utils::token::basic::ident, std::string{"Expected identifier."});
    if (!good()) return {};

    ident domain_name = std::make_unique<ast::Ident>(m_scopes.top(), std::move(*m_current_tok));

    // Eating ')'
    check_next_token(utils::token::basic::ident, std::string{"Expected ')'."});
    if (!good()) return {};
    m_scopes.pop();

    domain_item_list domain_items;
    bool end = false;

    do {
        // Eating either '(' or ')'
        get_next_token();
        if (!good()) return {};

        m_good = m_current_tok->has_type(utils::token::punctuation::lpar) ||
                 m_current_tok->has_type(utils::token::punctuation::rpar);

        if (m_good) {
            if (m_current_tok->has_type(utils::token::punctuation::rpar)) {
                // If we eat ')'
                m_scopes.pop();
                end = true;
            } else if (m_current_tok->has_type(utils::token::punctuation::lpar)) {
                // If we eat '('
                domain_items.push_back(parse_domain_item());
            }
        }
    } while (m_good && !end);

    if (!m_good) {
        m_error(*m_current_tok, std::string{"Syntax error."});      // todo: handle error
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
