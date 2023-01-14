#include "../include/parser.h"
#include "../include/epddl_exception.h"

#include <utility>

/*
 * TODO:
 *  1. Manage scopes
 *  2. Rework token types so that utils::token::requirement can be considered as a type
 *  3. Use templates to define token types (e.g., 'token<ast::Ident> tok' will be an identifier)
 *
 */

parser::parser(lexer lex) :
    m_lex{std::move(lex)},
    m_current_tok{std::nullopt} {
    m_scopes.push(scope::domain);
}

parser::~parser() = default;

void parser::get_next_token() {
    if (m_next_tok.has_value()) {
        m_current_tok.emplace(std::move(*m_next_tok));
        m_next_tok = std::nullopt;
    } else {
        if (m_lex.good() && !m_lex.eof())
            m_current_tok.emplace(m_lex.get_next_token());
    }
}

void parser::peek_next_token() {
    if (!m_next_tok.has_value() && m_lex.good() && !m_lex.eof())
        m_next_tok.emplace(m_lex.get_next_token());
}

bool parser::is_next_token(utils::token::type type) {
    peek_next_token();
    return m_next_tok->has_type(type);
}

void parser::check_current_token(utils::token::type expected_type, const std::string& error) {
    if (!m_current_tok->has_type(expected_type)) {
        throw EPDDLException{std::string{""}, m_current_tok->get_row(), m_current_tok->get_col(), error};
    }
}

void parser::check_next_token(utils::token::type expected_type, const std::string& error) {
    get_next_token();
    check_current_token(expected_type, error);
}

void parser::check_token_list(const std::list<std::pair<utils::token::type, std::string>>& to_check) {
    for (const auto& it : to_check) {
        check_next_token(it.first, it.second);
    }
}

template<class T>
std::unique_ptr<T> parser::get_node_from_next_token(utils::token::type expected_type, const std::string& error) {
    check_next_token(expected_type, error);
    return std::make_unique<T>(m_scopes.top(), std::move(*m_current_tok));
}

template<class T>
std::unique_ptr<T> parser::get_last_node_from_token_list(const std::list<std::pair<utils::token::type, std::string>>& to_check) {
    check_token_list(to_check);
    return std::make_unique<T>(m_scopes.top(), std::move(*m_current_tok));
}

template<class T>
std::list<T> parser::parse_list(std::function<T()> parse_elem) {
    std::list<T> elems;
    bool end_list = false;

    do {
        peek_next_token();

        if (m_next_tok->has_type(utils::token::punctuation::rpar)) {
            // If we peek ')'
            end_list = true;
        } else {
            // Otherwise we parse the element and, if we are successful, we add it to the list
            // Errors concerning unexpected tokens are handled by parse_elem()
            elems.push_back(parse_elem());
        }
    } while (!end_list);

    return elems;
}

ident parser::parse_ident() {
    get_next_token();

    if (m_current_tok->has_type(utils::token::basic::ident)) {
        return std::make_unique<ast::Ident>(m_scopes.top(), std::move(*m_current_tok));
    } else {
        throw EPDDLException{std::string{""}, m_current_tok->get_row(), m_current_tok->get_col(), std::string{"Expected identifier."}};
    }
}

variable parser::parse_variable() {
    get_next_token();

    if (m_current_tok->has_type(utils::token::basic::variable)) {
        return std::make_unique<ast::Variable>(m_scopes.top(), std::move(*m_current_tok));
    } else {
        throw EPDDLException{std::string{""}, m_current_tok->get_row(), m_current_tok->get_col(), std::string{"Expected identifier."}};
    }
}

integer parser::parse_integer() {
    get_next_token();

    if (m_current_tok->has_type(utils::token::basic::integer)) {
        return std::make_unique<ast::Integer>(m_scopes.top(), std::move(*m_current_tok));
    } else {
        throw EPDDLException{std::string{""}, m_current_tok->get_row(), m_current_tok->get_col(), std::string{"Expected integer."}};
    }
}

type parser::parse_type() {
    get_next_token();

    if (m_current_tok->has_type(utils::token::basic::ident)) {
        return std::make_unique<ast::Type>(m_scopes.top(), std::move(*m_current_tok));
    } else {
        throw EPDDLException{std::string{""}, m_current_tok->get_row(), m_current_tok->get_col(), std::string{"Expected identifier."}};
    }
}

modality parser::parse_modality() {
    get_next_token();

    if (m_current_tok->has_type(utils::token::basic::modality)) {
        return std::make_unique<ast::Modality>(m_scopes.top(), std::move(*m_current_tok));
    } else {
        throw EPDDLException{std::string{""}, m_current_tok->get_row(), m_current_tok->get_col(), std::string{"Expected identifier."}};
    }
}

requirement parser::parse_requirement() {
    get_next_token();

    if (std::get_if<utils::token::requirement>(&m_current_tok->get_type())) {
        return std::make_unique<ast::Requirement>(m_scopes.top(), std::move(*m_current_tok));
    } else {
        throw EPDDLException{std::string{""}, m_current_tok->get_row(), m_current_tok->get_col(), std::string{"Expected requirement."}};
    }
}

valued_requirement parser::parse_valued_requirement() {
    check_next_token(utils::token::punctuation::lpar, std::string{"Expected '('."});
    get_next_token();

    if (std::get_if<utils::token::requirement>(&m_current_tok->get_type())) {
        Token req = std::move(*m_current_tok);
        integer val = get_node_from_next_token<ast::Integer>(utils::token::basic::integer,
                                                             std::string{"Expected integer."});

        return std::make_unique<ast::ValuedRequirement>(m_scopes.top(), std::move(req), std::move(val));
    } else {
        throw EPDDLException{std::string{""}, m_current_tok->get_row(), m_current_tok->get_col(), std::string{"Expected requirement."}};
    }
}

ast::ASTNode parser::parse_term() {
    return ast::ASTNode(scope::domain);
}

formula parser::parse_formula() {
    return {};
}

ast::ASTNode parser::parse_quantified_formula() {
    return ast::ASTNode(scope::domain);
}

ast::ASTNode parser::parse_modal_formula() {
    return ast::ASTNode(scope::domain);
}

predicate parser::parse_predicate() {
    ident name = get_node_from_next_token<ast::Ident>(utils::token::basic::ident,
                                                      std::string{"Expected identifier."});
    // todo: finish
    return {};
}

ast::ASTNode parser::parse_eq_formula() {
    return ast::ASTNode(scope::domain);
}

parameters parser::parse_parameters() {
    check_next_token(utils::token::keyword::parameters, std::string{"Expected ':parameters'."});       // Eating ':parameters'
    m_scopes.push(scope::parameters);

    formal_param_list params = parse_formal_param_list();

    check_next_token(utils::token::punctuation::rpar, std::string{"Expected ')'."});       // Eating ')'
    m_scopes.pop();

    return std::make_unique<ast::Parameters>(m_scopes.top(), std::move(params));
}

ast::ASTNode parser::parse_actual_parameter() {
    return ast::ASTNode(scope::domain);
}

expression parser::parse_expression() {
    return {};
}

assignment parser::parse_assignment() {
    variable var = get_last_node_from_token_list<ast::Variable>({
        {utils::token::punctuation::lpar, std::string{"Expected '('."}},        // Eating '('
        {utils::token::basic::variable, std::string{"Expected variable."}}      // Eating variable
    });

    check_next_token(utils::token::punctuation::gets, std::string{"Expected '<-'."});       // Eating '<-'
    expression expr = parse_expression();

    check_next_token(utils::token::punctuation::rpar, std::string{"Expected ')'."});       // Eating ')'
    m_scopes.pop();

    return std::make_pair<variable, expression>(std::move(var), std::move( expr));
}

signature parser::parse_signature() {
    check_next_token(utils::token::keyword::act_type, std::string{"Expected ':action-type'."});       // Eating ':action-type'
    m_scopes.push(scope::signature);

    ident act_type_name = get_last_node_from_token_list<ast::Ident>({
        {utils::token::punctuation::lpar, std::string{"Expected '('."}},        // Eating '('
        {utils::token::basic::ident, std::string{"Expected identifier."}}        // Eating identifier
    });

    std::function<assignment()> parse_elem = [this] () { return parse_assignment(); };
    assignment_list assigns = parse_list(parse_elem);

    check_next_token(utils::token::punctuation::rpar, std::string{"Expected ')'."});       // Eating ')'
    m_scopes.pop();

    return std::make_unique<ast::Signature>(m_scopes.top(), std::move(act_type_name), std::move(assigns));
}

simple_obs_cond parser::parse_simple_obs_condition() {
    return {};
}

if_obs_cond parser::parse_if_obs_condition() {
    return {};
}

forall_obs_cond parser::parse_forall_obs_condition() {
    return {};
}

obs_cond parser::parse_obs_condition() {
    return {};
}

std::optional<obs_cond_list> parser::parse_obs_condition_list() {
    if (!is_next_token(utils::token::keyword::obs_conditions)) {        // Peeking ':observability-conditions'
        return std::nullopt;
    }

    get_next_token();       // Actually eating ':observability-conditions'

    std::function<obs_cond()> parse_elem = [this] () { return parse_obs_condition(); };
    return parse_list(parse_elem);
}

domain_libraries parser::parse_domain_act_type_libs() {
    std::function<ident()> parse_elem = [this] () { return parse_ident(); };
    ident_list ids = parse_list(parse_elem);

    return std::make_unique<ast::DomainLibraries>(m_scopes.top(), std::move(ids));
}

domain_requirements parser::parse_domain_requirements() {
    std::function<requirement()> parse_elem = [this] () { return parse_requirement(); };
    requirement_list reqs = parse_list(parse_elem);

    return std::make_unique<ast::DomainRequirements>(m_scopes.top(), std::move(reqs));
}

domain_types parser::parse_domain_types() {
    std::function<type()> parse_elem = [this] () { return parse_type(); };
    type_list types = parse_list(parse_elem);

    return std::make_unique<ast::DomainTypes>(m_scopes.top(), std::move(types));
}

formal_param parser::parse_formal_param() {
    variable var = get_node_from_next_token<ast::Variable>(utils::token::basic::variable,
                                                           std::string{"Expected variable."});
    std::optional<type> type = std::nullopt;

    peek_next_token();      // Peeking either '-' or another variable

    if (m_next_tok->has_type(utils::token::punctuation::dash)) {
        get_next_token();       // Actually eating '-'
        type = get_node_from_next_token<ast::Type>(utils::token::basic::ident,
                                                   std::string{"Expected type identifier."});
    }
    return std::make_pair(std::move(var), std::move(type));
}

formal_param_list parser::parse_formal_param_list() {
    std::function<formal_param()> parse_elem = [this] () { return parse_formal_param(); };
    return parse_list(parse_elem);
}

predicate_def parser::parse_predicate_def() {
    ident name = get_last_node_from_token_list<ast::Ident>({
        {utils::token::punctuation::lpar, std::string{"Expected '('."}},        // Eating '('
        {utils::token::basic::ident,      std::string{"Expected identifier."}}   // Eating predicate name (ident)
    });

    formal_param_list params = parse_formal_param_list();
    // The last token read in function parse_formal_param_list() is not used, so we check it here
    check_current_token(utils::token::punctuation::rpar, std::string{"Expected ')'."});

    return std::make_unique<ast::PredicateDef>(m_scopes.top(), std::move(name), std::move(params));
}

domain_predicates parser::parse_domain_predicates() {
    std::function<predicate_def()> parse_elem = [this] () { return parse_predicate_def(); };
    predicate_def_list preds = parse_list(parse_elem);

    return std::make_unique<ast::DomainPredicates>(m_scopes.top(), std::move(preds));
}

domain_modalities parser::parse_domain_modalities() {
    std::function<modality()> parse_elem = [this] () { return parse_modality(); };
    modality_list mods = parse_list(parse_elem);

    return std::make_unique<ast::DomainModalities>(m_scopes.top(), std::move(mods));
}

action parser::parse_action() {
    ident action_name = get_node_from_next_token<ast::Ident>(utils::token::basic::ident,
                                                             std::string{"Expected identifier."});       // Eating domain name (ident)
    parameters params = parse_parameters();
    signature sign = parse_signature();
    formula pre = parse_formula();
    std::optional<obs_cond_list> obs = parse_obs_condition_list();

    return std::make_unique<ast::Action>(m_scopes.top(), std::move(action_name),
                                         std::move(params), std::move(sign),
                                         std::move(pre), std::move(obs));
}

domain_item parser::parse_domain_item() {
    if (!is_next_token(utils::token::punctuation::lpar)) {      // Peeking '('
        return {};
    }

    get_next_token();       // Actually eating '('
    get_next_token();       // Eating keyword

    domain_item item;
    if (m_current_tok->has_type(utils::token::keyword::act_type_lib)) {
        m_scopes.push(scope::domain_act_type_libs);
        item = parse_domain_act_type_libs();
    } else if (m_current_tok->has_type(utils::token::keyword::requirements)) {
        m_scopes.push(scope::domain_requirements);
        item = parse_domain_requirements();
    } else if (m_current_tok->has_type(utils::token::keyword::types)) {
        m_scopes.push(scope::domain_types);
        item = parse_domain_types();
    } else if (m_current_tok->has_type(utils::token::keyword::predicates)) {
        m_scopes.push(scope::domain_predicates);
        item = parse_domain_predicates();
    } else if (m_current_tok->has_type(utils::token::keyword::modalities)) {
        m_scopes.push(scope::domain_modalities);
        item = parse_domain_modalities();
    } else if (m_current_tok->has_type(utils::token::keyword::action)) {
        m_scopes.push(scope::action);
        item = parse_action();
    } else {
        throw EPDDLException{std::string{""}, m_current_tok->get_row(), m_current_tok->get_col(), std::string{"Syntax error."}};
    }

    // The last token read in the above functions is not used, so we check it here
    check_current_token(utils::token::punctuation::rpar, std::string{"Expected ')'."});
    m_scopes.pop();

    return item;
}

domain parser::parse_domain() {
    ident domain_name = get_last_node_from_token_list<ast::Ident>({
                                                                          {utils::token::punctuation::lpar, std::string{
                                                                                  "Expected '('."}},      // Eating '('
                                                                          {utils::token::keyword::define,   std::string{
                                                                                  "Expected 'define'."}},      // Eating 'define'
                                                                          {utils::token::punctuation::lpar, std::string{
                                                                                  "Expected '('."}},      // Eating '('
                                                                          {utils::token::keyword::domain,   std::string{
                                                                                  "Expected 'domain'."}},      // Eating 'domain'
                                                                          {utils::token::basic::ident,      std::string{
                                                                                  "Expected identifier."}}       // Eating domain name (ident)
                                                                  });

    // Eating ')'
    check_next_token(utils::token::punctuation::rpar, std::string{"Expected ')'."});
    m_scopes.pop();

    std::function<domain_item()> parse_elem = [this] () { return parse_domain_item(); };
    domain_item_list domain_items = parse_list(parse_elem);
//    domain_item_list domain_items = parse_list(static_cast<std::function<domain_item()>>([this] () { return parse_domain_item(); }));

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
