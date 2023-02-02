#include "../include/parser.h"
#include "../include/epddl_exception.h"

#include <utility>

/*
 * TODO:
 *  1. Manage scopes
 *  2. Rework token types so that requirement_value can be considered as a type
 *  3. Use templates to define token types (e.g., 'token<ast::Ident> tok' will be an identifier)
 *
 */

parser::parser(lexer& lex) :
    m_lex{lex},
    m_current_tok{std::nullopt},
    m_lpar_count{0} {}

parser::~parser() = default;

void parser::get_next_token() {
    if (m_next_tok.has_value()) {
        m_current_tok.emplace(std::move(*m_next_tok));
        m_next_tok = std::nullopt;
    } else {
        if (m_lex.good() && !m_lex.eof())
            m_current_tok.emplace(m_lex.get_next_token());
    }

    if (std::get<punctuation_value>(m_current_tok->get_type()) == punctuation_value::lpar) {
        ++m_lpar_count;
    } else if (std::get<punctuation_value>(m_current_tok->get_type()) == punctuation_value::rpar) {
        if (m_lpar_count == m_scopes.top().first) {
            m_scopes.pop();
        }
        --m_lpar_count;
    } else if (m_lex.get_dictionary().is_scope(m_current_tok->get_type())) {
        m_scopes.emplace(m_lpar_count, m_current_tok->get_type());
    }
}

void parser::peek_next_token() {
    if (!m_next_tok.has_value() && m_lex.good() && !m_lex.eof())
        m_next_tok.emplace(m_lex.get_next_token());
}

bool parser::is_next_token(token_type type) {
    peek_next_token();
    return m_next_tok->has_type(type);
}

void parser::check_current_token(const token_type& expected_type) {
    if (!m_current_tok->has_type(expected_type)) {
        std::string type;

        // We only check for basic values, punctuation or valid keywords
        if (std::holds_alternative<basic_value>(expected_type)) {
            type = m_lex.get_dictionary().get_name(expected_type);
        } else {
            type = std::string{"'"} + m_lex.get_dictionary().to_string(expected_type) + std::string{"'"};
        }
        throw EPDDLException{std::string{""}, m_current_tok->get_row(), m_current_tok->get_col(), std::string{"Expected " + type + std::string{"."}}};
    }
}

void parser::check_next_token(const token_type& expected_type) {
    get_next_token();
    check_current_token(expected_type);
}

void parser::check_token_list(const std::list<token_type>& to_check) {
    for (const auto& it : to_check) {
        check_next_token(it);
    }
}

template<class T>
std::unique_ptr<T> parser::get_node_from_next_token(const token_type& expected_type) {
    check_next_token(expected_type);
    return std::make_unique<T>(std::move(*m_current_tok));
}

template<class T>
std::unique_ptr<T> parser::get_last_node_from_token_list(const std::list<token_type>& to_check) {
    check_token_list(to_check);
    return std::make_unique<T>(std::move(*m_current_tok));
}

template<class T>
std::list<T> parser::parse_list(std::function<T()> parse_elem) {
    std::list<T> elems;
    bool end_list = false;

    do {
        peek_next_token();

        if (m_next_tok->has_type(punctuation_value::rpar)) {
            // If we peek ')'
            end_list = true;
        } else {
            // Otherwise we parse the element and, if we are successful, we add it to the list
            // Errors concerning unexpected tokens are handled by parse_elem()
            elems.push_back(parse_elem());
        }
    } while (!end_list);

    // todo: implement empty list check
    close_par();
    return elems;
}

template<class T>
std::unique_ptr<T> parser::parse_basic(basic_value type) {
    get_next_token();

    if (m_current_tok->has_type(type)) {
        return std::make_unique<T>(std::move(*m_current_tok));
    } else {
        throw EPDDLException{std::string{""}, m_current_tok->get_row(), m_current_tok->get_col(), std::string{"Expected "} + m_lex.get_dictionary().get_name(type) + std::string{"."}};
    }
}

template<class T>
std::unique_ptr<T> parser::parse_basic_or_rpar(basic_value type) {
    peek_next_token();

    if (m_next_tok->has_type(type)) {
        get_next_token();
        return std::make_unique<T>(std::move(*m_current_tok));
    } else if (std::get<punctuation_value>(m_next_tok->get_type()) != punctuation_value::rpar) {
        throw EPDDLException{std::string{""}, m_current_tok->get_row(), m_current_tok->get_col(), std::string{"Expected "} + m_lex.get_dictionary().get_name(type) + std::string{"."}};
    }
    return {};
}

void parser::open_par() {
    check_next_token(punctuation_value::lpar);
}

void parser::close_par() {
    check_next_token(punctuation_value::rpar);
}

identifier parser::parse_ident() {
    return parse_basic<ast::Identifier>(basic_value::identifier);
}

variable parser::parse_variable() {
    return parse_basic<ast::Variable>(basic_value::variable);
}

integer parser::parse_integer() {
    return parse_basic<ast::Integer>(basic_value::integer);
}

type parser::parse_type() {
    return parse_basic<ast::Type>(basic_value::identifier);
}

modality parser::parse_modality() {
    return parse_basic<ast::Modality>(basic_value::modality);
}

requirement parser::parse_requirement() {
    peek_next_token();

    if (std::holds_alternative<requirement_value>(m_next_tok->get_type())) {
        get_next_token();       // Eating requirement
        return std::make_unique<ast::Requirement>(std::move(*m_current_tok));
    } else if (std::get<punctuation_value>(m_next_tok->get_type()) == punctuation_value::lpar) {
        get_next_token();       // Eating '('
        get_next_token();       // Eating requirement

        if (std::holds_alternative<requirement_value>(m_current_tok->get_type())) {
            Token req = std::move(*m_current_tok);

            if (std::holds_alternative<requirement_value>(m_current_tok->get_type())) {
                integer val = get_node_from_next_token<ast::Integer>(basic_value::integer);
                close_par();

                return std::make_unique<ast::Requirement>(std::move(req), std::move(val));
            }
        }
    }

    if (std::get<punctuation_value>(m_next_tok->get_type()) != punctuation_value::rpar) {
        throw EPDDLException{std::string{""}, m_current_tok->get_row(), m_current_tok->get_col(), std::string{"Expected requirement."}};
    }
    return {};
}

term parser::parse_term() {
    return {};
}

formula parser::parse_formula() {
    return {};
}

quantified_formula parser::parse_quantified_formula() {
    return {};
}

modal_formula parser::parse_modal_formula() {
    return {};
}

predicate parser::parse_predicate() {
    identifier name = get_node_from_next_token<ast::Identifier>(basic_value::identifier);
    // todo: finish
    return {};
}

eq_formula parser::parse_eq_formula() {
    return {};
}

parameters parser::parse_parameters() {
    check_next_token(keyword_value::parameters);       // Eating ':parameters'

    open_par();     // Eating '('
    formal_param_list params = parse_formal_param_list();
    close_par();    // Eating ')'

    return std::make_unique<ast::Parameters>(std::move(params));
}

actual_parameter parser::parse_actual_parameter() {
    return {};
}

expression parser::parse_expression() {
    return {};
}

assignment parser::parse_assignment() {
    open_par();       // Eating '('
    variable var = get_node_from_next_token<ast::Variable>(basic_value::variable);      // Eating variable
    check_next_token(punctuation_value::gets);       // Eating '<-'
    expression expr = parse_expression();
    close_par();       // Eating ')'

    return std::make_pair<variable, expression>(std::move(var), std::move( expr));
}

signature parser::parse_signature() {
    check_next_token(keyword_value::act_type);       // Eating ':action-type'

    open_par();      // Eating '('
    identifier act_type_name = get_node_from_next_token<ast::Identifier>(basic_value::identifier);        // Eating action type name (identifier)

    std::function<assignment()> parse_elem = [this] () { return parse_assignment(); };
    assignment_list assigns = parse_list(parse_elem);
    close_par();       // Eating ')'

    return std::make_unique<ast::Signature>(std::move(act_type_name), std::move(assigns));
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
    return {};      // todo: start from here
}

std::optional<obs_cond_list> parser::parse_obs_condition_list() {
    if (!is_next_token(keyword_value::obs_conditions)) {        // Peeking ':observability-conditions'
        return std::nullopt;
    }

    get_next_token();       // Actually eating ':observability-conditions'
    std::function<obs_cond()> parse_elem = [this] () { return parse_obs_condition(); };
    return parse_list(parse_elem);
}

domain_libraries parser::parse_domain_act_type_libs() {
    std::function<identifier()> parse_elem = [this] () { return parse_basic_or_rpar<ast::Identifier>(basic_value::identifier); };
    ident_list ids = parse_list(parse_elem);

    return std::make_unique<ast::DomainLibraries>(std::move(ids));
}

domain_requirements parser::parse_domain_requirements() {
    std::function<requirement()> parse_elem = [this] () { return parse_requirement(); };
    requirement_list reqs = parse_list(parse_elem);

    return std::make_unique<ast::DomainRequirements>(std::move(reqs));
}

domain_types parser::parse_domain_types() {
    std::function<type()> parse_elem = [this] () { return parse_basic_or_rpar<ast::Type>(basic_value::identifier); };
    type_list types = parse_list(parse_elem);

    return std::make_unique<ast::DomainTypes>(std::move(types));
}

formal_param parser::parse_formal_param() {
    variable var = get_node_from_next_token<ast::Variable>(basic_value::variable);
    std::optional<type> type = std::nullopt;

    peek_next_token();          // Peeking either '-' or another variable

    if (m_next_tok->has_type(punctuation_value::dash)) {
        get_next_token();       // Actually eating '-'
        type = get_node_from_next_token<ast::Type>(basic_value::identifier);
    }
    return std::make_pair(std::move(var), std::move(type));
}

formal_param_list parser::parse_formal_param_list() {
    std::function<formal_param()> parse_elem = [this] () { return parse_formal_param(); };
    return parse_list(parse_elem);
}

predicate_def parser::parse_predicate_def() {
    open_par();        // Eating '('
    identifier         name   = get_node_from_next_token<ast::Identifier>(basic_value::identifier);     // Eating predicate name (identifier)
    formal_param_list params = parse_formal_param_list();
    close_par();       // Eating ')'

    return std::make_unique<ast::PredicateDef>(std::move(name), std::move(params));
}

domain_predicates parser::parse_domain_predicates() {
    std::function<predicate_def()> parse_elem = [this] () { return parse_predicate_def(); };
    predicate_def_list preds = parse_list(parse_elem);

    return std::make_unique<ast::DomainPredicates>(std::move(preds));
}

domain_modalities parser::parse_domain_modalities() {
    std::function<modality()> parse_elem = [this] () { return parse_basic_or_rpar<ast::Modality>(basic_value::modality); };
    modality_list mods = parse_list(parse_elem);

    return std::make_unique<ast::DomainModalities>(std::move(mods));
}

action parser::parse_action() {
    identifier action_name = get_node_from_next_token<ast::Identifier>(basic_value::identifier);       // Eating action name (identifier)

    parameters                   params = parse_parameters();
    signature                    sign   = parse_signature();
    formula                      pre    = parse_formula();
    std::optional<obs_cond_list> obs    = parse_obs_condition_list();

    return std::make_unique<ast::Action>(std::move(action_name), std::move(params), std::move(sign), std::move(pre), std::move(obs));
}

domain_item parser::parse_domain_item() {
    open_par();             // Eating '('
    get_next_token();       // Eating keyword

    domain_item item;

    if (m_current_tok->has_type(keyword_value::act_type_lib)) {
        item = parse_domain_act_type_libs();
    } else if (m_current_tok->has_type(keyword_value::requirements)) {
        item = parse_domain_requirements();
    } else if (m_current_tok->has_type(keyword_value::types)) {
        item = parse_domain_types();
    } else if (m_current_tok->has_type(keyword_value::predicates)) {
        item = parse_domain_predicates();
    } else if (m_current_tok->has_type(keyword_value::modalities)) {        // todo: implement new idea on modalities
        item = parse_domain_modalities();
    } else if (m_current_tok->has_type(keyword_value::action)) {
        item = parse_action();
    } else {
        throw EPDDLException{std::string{""}, m_current_tok->get_row(), m_current_tok->get_col(), std::string{"Expected keyword."}};
    }

    close_par();        // Eating ')'
    return item;
}

domain parser::parse_domain() {
    identifier domain_name = get_last_node_from_token_list<ast::Identifier>({
        punctuation_value::lpar,   // Eating '('
        keyword_value::define,      // Eating 'define'
        punctuation_value::lpar,   // Eating '('
        keyword_value::domain,     // Eating 'domain'
        basic_value::identifier,    // Eating domain name (identifier)
    });

    close_par();   // Eating ')'

    std::function<domain_item()> parse_elem = [this] () { return parse_domain_item(); };
    domain_item_list domain_items = parse_list(parse_elem);
    // The last token read in parse_domain_item() is not used, so we check it here
//    parse_end_list();

    return std::make_unique<ast::Domain>(std::move(domain_name), std::move(domain_items));
}

action_type parser::parse_action_type() {
    return {};
}

literal parser::parse_literal() {
    return {};
}

simple_post parser::parse_simple_postcondition() {
    return {};
}

forall_post parser::parse_forall_postcondition() {
    return {};
}

event parser::parse_event() {
    return {};
}

library parser::parse_library() {
    return {};
}

agent_group parser::parse_agent_group() {
    return {};
}

epistemic_state parser::parse_epistemic_state() {
    return {};
}

init parser::parse_init() {
    return {};
}

problem parser::parse_problem() {
    return {};
}

planning_task parser::parse_epddl_planning_task() {
    return {};
}
