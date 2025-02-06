#include "../../../include/parser/common/formulas_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/error-manager/epddl_exception.h"
#include "../../../include/parser/common/typed_elem_parser.h"
#include "../../../include/grammar/tokens/modalities_def.h"
#include <memory>

using namespace epddl;

ast::formula_ptr formulas_parser::parse_formula(parser_helper &parser) {
    parser.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = parser.peek_next_token();
    ast::formula_ptr f;

    if (tok->has_type<pattern_token::identifier>())          f = formulas_parser::parse_predicate_formula(parser);
    else if (tok->has_type<punctuation_token::eq>())         f = formulas_parser::parse_eq_formula(parser);
    else if (tok->has_type<connective_token::negation>())    f = formulas_parser::parse_not_formula(parser);
    else if (tok->has_type<connective_token::conjunction>()) f = formulas_parser::parse_and_formula(parser);
    else if (tok->has_type<connective_token::disjunction>()) f = formulas_parser::parse_or_formula(parser);
    else if (tok->has_type<connective_token::implication>()) f = formulas_parser::parse_imply_formula(parser);
    else if (tok->has_type<punctuation_token::lbrack>())     f = formulas_parser::parse_box_formula(parser);
    else if (tok->has_type<punctuation_token::langle>())     f = formulas_parser::parse_diamond_formula(parser);
    else if (tok->has_type<keyword_token::in>())             f = formulas_parser::parse_in_formula(parser);
    else if (tok->has_type<quantifier_token::forall>())      f = formulas_parser::parse_forall_formula(parser);
    else if (tok->has_type<quantifier_token::exists>())      f = formulas_parser::parse_exists_formula(parser);
    else                                                     throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected formula. Found: " + tok->to_string());

    parser.check_next_token<punctuation_token::rpar>();
    return f;
}

ast::formula_ptr formulas_parser::parse_predicate_formula(parser_helper &parser) {
    return std::make_unique<ast::predicate_formula>(formulas_parser::parse_predicate(parser, false));
}

ast::formula_ptr formulas_parser::parse_eq_formula(parser_helper &parser) {
    parser.check_next_token<punctuation_token::eq>();
    ast::term t1 = formulas_parser::parse_term(parser);
    ast::term t2 = formulas_parser::parse_term(parser);

    return std::make_unique<ast::eq_formula>(std::move(t1), std::move(t2));
}

ast::formula_ptr formulas_parser::parse_not_formula(parser_helper &parser) {
    parser.check_next_token<connective_token::negation>();
    ast::formula_ptr f = formulas_parser::parse_formula(parser);

    return std::make_unique<ast::not_formula>(std::move(f));
}

ast::formula_ptr formulas_parser::parse_and_formula(parser_helper &parser) {
    parser.check_next_token<connective_token::conjunction>();
    auto fs = parser.parse_list<ast::formula_ptr>([&] () { return formulas_parser::parse_formula(parser); });

    return std::make_unique<ast::and_formula>(std::move(fs));
}

ast::formula_ptr formulas_parser::parse_or_formula(parser_helper &parser) {
    parser.check_next_token<connective_token::disjunction>();
    auto fs = parser.parse_list<ast::formula_ptr>([&] () { return formulas_parser::parse_formula(parser); });

    return std::make_unique<ast::or_formula>(std::move(fs));
}

ast::formula_ptr formulas_parser::parse_imply_formula(parser_helper &parser) {
    parser.check_next_token<connective_token::implication>();
    ast::formula_ptr f1 = formulas_parser::parse_formula(parser);
    ast::formula_ptr f2 = formulas_parser::parse_formula(parser);

    return std::make_unique<ast::imply_formula>(std::move(f1), std::move(f2));
}

ast::formula_ptr formulas_parser::parse_box_formula(parser_helper &parser) {
    parser.check_next_token<punctuation_token::lbrack>();
    ast::modality_ptr mod = formulas_parser::parse_modality(parser);
    parser.check_next_token<punctuation_token::rbrack>();
    ast::formula_ptr f = formulas_parser::parse_formula(parser);

    return std::make_unique<ast::box_formula>(std::move(mod), std::move(f));
}

ast::formula_ptr formulas_parser::parse_diamond_formula(parser_helper &parser) {
    parser.check_next_token<punctuation_token::langle>();
    ast::modality_ptr mod = formulas_parser::parse_modality(parser);
    parser.check_next_token<punctuation_token::rangle>();
    ast::formula_ptr f = formulas_parser::parse_formula(parser);

    return std::make_unique<ast::diamond_formula>(std::move(mod), std::move(f));
}

ast::formula_ptr formulas_parser::parse_such_that(parser_helper &parser) {
    parser.check_next_token<punctuation_token::such_that>();
    return formulas_parser::parse_formula(parser);
}

ast::ext_list_comprehension_ptr formulas_parser::parse_ext_list_comprehension(parser_helper &parser, ast::variable_list &&prefix) {
    ast::term_list terms;
    for (ast::variable_ptr &v : prefix) terms.emplace_back(std::move(v));

    ast::term_list terms_ = parser.parse_list<ast::term>([&]() { return formulas_parser::parse_term(parser); });
    for (ast::term &t : terms_) terms.emplace_back(std::move(t));

    return std::make_unique<ast::ext_list_comprehension>(std::move(terms));
}

ast::int_list_comprehension_ptr formulas_parser::parse_int_list_comprehension(parser_helper &parser) {
    auto params = parser.parse_list<ast::typed_variable_ptr, punctuation_token::such_that>([&] () { return typed_elem_parser::parse_typed_variable(parser); });
    auto f = parser.parse_optional<ast::formula_ptr, punctuation_token::such_that>([&] () { return formulas_parser::parse_such_that(parser); });

    return std::make_unique<ast::int_list_comprehension>(std::move(params), std::move(f));
}

ast::list_comprehension_ptr formulas_parser::parse_list_comprehension(parser_helper &parser) {
    ast::list_comprehension_ptr set_compr;
    ast::variable_list prefix;
    bool go = true;

    // We first parse a (possibly empty) prefix of consecutive variables
    while (go)
        if (const token_ptr &tok = parser.peek_next_token(); (go = tok->has_type<pattern_token::variable>()))
            prefix.emplace_back(tokens_parser::parse_variable(parser));

    const token_ptr &tok = parser.peek_next_token();

    // Once we read the prefix, we have three options for the next token:
    if (tok->has_type<pattern_token::identifier>())         // 1. Identifier: we are in an extensional list comprehension
        set_compr = formulas_parser::parse_ext_list_comprehension(parser, std::move(prefix));
    else if (tok->has_type<punctuation_token::rpar>()) {    // 2. Right parenthesis: we are in an extensional list comprehension
        if (prefix.empty())
            throw EPDDLParserException("", tok->get_row(), tok->get_col(), "List comprehension can not declare empty lists.");

        set_compr = formulas_parser::parse_ext_list_comprehension(parser);
    } else if (tok->has_type<punctuation_token::dash>()) {  // Dash: we are in an intensional list comprehension
        if (prefix.empty())
            throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Missing variable before type specification.");

        // We read the type of the last scanned variable and we create the relative formal parameter
        parser.check_next_token<punctuation_token::dash>();
        ast::identifier_ptr last_var_type = tokens_parser::parse_identifier(parser);
        ast::formal_param last_fp = std::make_unique<ast::typed_variable>(std::move(prefix.back()), std::move(last_var_type));
        prefix.pop_back();

        // We convert variables into formal parameters
        ast::formal_param_list params;
        for (ast::variable_ptr &v : prefix) params.push_back(std::make_unique<ast::typed_variable>(std::move(v)));
        params.push_back(std::move(last_fp));
        // We finish scanning the remaining formal parameters (if any)
        auto params_ = parser.parse_list<ast::formal_param, punctuation_token::such_that>([&]() { return typed_elem_parser::parse_typed_variable(parser); });
        for (ast::formal_param &fp : params_) params.push_back(std::move(fp));

        auto f = parser.parse_optional<ast::formula_ptr, punctuation_token::such_that>([&] () { return formulas_parser::parse_such_that(parser); });
        set_compr = std::make_unique<ast::int_list_comprehension>(std::move(params), std::move(f));
/*        ast::term_list terms = parser.parse_list<ast::term, punctuation_token::dash>([&]() { return formulas_parser::parse_term(parser); });
        const token_ptr &tok_ = parser.peek_next_token();

        if (tok_->has_type<punctuation_token::rpar>())
            set_compr = std::make_unique<ast::ext_list_comprehension>(std::move(terms));
        else if (tok_->has_type<punctuation_token::dash>()) {
            ast::formal_param_list params;

            for (ast::term &t : terms) {
                std::visit([&](auto&& t_) {
                    using term_type = std::decay_t<decltype(t_)>;

                    if constexpr (std::is_same_v<term_type, ast::variable_ptr>)
                        params.push_back(std::make_unique<ast::typed_variable>(std::forward<ast::variable_ptr>(t_)));
                    else if constexpr (std::is_same_v<term_type, ast::identifier_ptr>)
                        throw EPDDLParserException("", tok_->get_row(), tok_->get_col(), "Unexpected type specification in extensional set declaration.");
                }, t);
            }

            parser.check_next_token<punctuation_token::dash>();
            ast::identifier_ptr last_var_type = tokens_parser::parse_identifier(parser);
            auto params_ = parser.parse_list<ast::formal_param>([&]() { return typed_elem_parser::parse_typed_variable(parser); });

            for (ast::formal_param &param : params_)
                params.push_back(std::move(param));
        } else
            throw EPDDLParserException("", tok_->get_row(), tok_->get_col(), "Expected term or type specification. Found: " + tok_->to_string());*/
    } else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected term. Found: " + tok->to_string());

    return set_compr;
}

ast::formula_ptr formulas_parser::parse_in_formula(parser_helper &parser) {
    parser.check_next_token<keyword_token::in>();
    auto terms = parser.parse_list<ast::term, punctuation_token::lpar>([&]() { return formulas_parser::parse_term(parser); });
    parser.check_next_token<punctuation_token::lpar>();
    ast::list_comprehension_ptr set = formulas_parser::parse_list_comprehension(parser);
    parser.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::in_formula>(std::move(terms), std::move(set));
}

ast::formula_ptr formulas_parser::parse_forall_formula(parser_helper &parser) {
    parser.check_next_token<quantifier_token::forall>();
    parser.check_next_token<punctuation_token::lpar>();
    ast::int_list_comprehension_ptr params = formulas_parser::parse_int_list_comprehension(parser);
    parser.check_next_token<punctuation_token::rpar>();
    ast::formula_ptr f = formulas_parser::parse_formula(parser);

    return std::make_unique<ast::forall_formula>(std::move(params), std::move(f));
}

ast::formula_ptr formulas_parser::parse_exists_formula(parser_helper &parser) {
    parser.check_next_token<quantifier_token::exists>();
    parser.check_next_token<punctuation_token::lpar>();
    ast::int_list_comprehension_ptr params = formulas_parser::parse_int_list_comprehension(parser);
    parser.check_next_token<punctuation_token::rpar>();
    ast::formula_ptr f = formulas_parser::parse_formula(parser);

    return std::make_unique<ast::exists_formula>(std::move(params), std::move(f));
}

ast::predicate_ptr formulas_parser::parse_predicate(parser_helper &parser, bool parse_outer_pars) {
    if (parse_outer_pars) parser.check_next_token<punctuation_token::lpar>();
    auto name = tokens_parser::parse_token<ast::identifier>(parser);
    auto terms = parser.parse_list<ast::term>([&]() { return formulas_parser::parse_term(parser); }, true);
    if (parse_outer_pars) parser.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::predicate>(std::move(name), std::move(terms));
}

ast::literal_ptr formulas_parser::parse_literal(parser_helper &parser) {
    parser.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = parser.peek_next_token();
    ast::predicate_ptr predicate;
    bool is_positive = false;

    if (tok->has_type<pattern_token::identifier>()) {
        auto name = tokens_parser::parse_token<ast::identifier>(parser);
        auto terms = parser.parse_list<ast::term>([&]() { return formulas_parser::parse_term(parser); }, true);
        parser.check_next_token<punctuation_token::rpar>();

        predicate = std::make_unique<ast::predicate>(std::move(name), std::move(terms));
        is_positive = true;
    } else if (tok->has_type<connective_token::negation>()) {
        parser.check_next_token<connective_token::negation>();
        predicate = std::move(formulas_parser::parse_predicate(parser));
    } else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected literal. Found: " + tok->to_string());

    return std::make_unique<ast::literal>(is_positive, std::move(predicate));
}

ast::term formulas_parser::parse_term(parser_helper &parser) {
    const token_ptr &tok = parser.peek_next_token();
    ast::term term;

    if (tok->has_type<pattern_token::identifier>())    term = std::move(tokens_parser::parse_token<ast::identifier>(parser));
    else if (tok->has_type<pattern_token::variable>()) term = std::move(tokens_parser::parse_token<ast::variable>(parser));
    else throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected term. Found: " + tok->to_string());

    return term;
}

ast::modality_ptr formulas_parser::parse_modality(parser_helper &parser) {
    #define epddl_token_type(token_type) token_type
    #define epddl_token(t_type, t_scope, t_name, t_lexeme) t_type::t_name
    #define all_modalities(modalities...) auto modality_name = parser.parse_optional<ast::modality_name_ptr, modalities>([&] () { return tokens_parser::parse_modality_name(parser); });
    epddl_all_modalities
    #undef all_modalities
    #undef epddl_token_type
    #undef epddl_token

    ast::modality_index_ptr modality_index = formulas_parser::parse_modality_index(parser);
    return std::make_unique<ast::modality>(std::move(modality_name), std::move(modality_index));
}

ast::modality_index_ptr formulas_parser::parse_modality_index(parser_helper &parser) {
    const token_ptr &tok = parser.peek_next_token();
    ast::modality_index_ptr modality_index;

    if (tok->has_type<pattern_token::identifier>() or tok->has_type<pattern_token::variable>())
        modality_index = formulas_parser::parse_single_modality(parser);
    else if (tok->has_type<agent_group_token::all>()) {
        parser.check_next_token<agent_group_token::all>();
        modality_index = agent_group_token::all{};
    } else if (tok->has_type<punctuation_token::lpar>())
        modality_index = formulas_parser::parse_group_modality(parser);
    else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected modality. Found: " + tok->to_string());

    return modality_index;
}

ast::single_modality_index_ptr formulas_parser::parse_single_modality(parser_helper &parser) {
    const token_ptr &tok = parser.peek_next_token();
    ast::single_modality_index_ptr modality_index;

    if (tok->has_type<pattern_token::identifier>())
        modality_index = tokens_parser::parse_token<ast::identifier>(parser);
    else if (tok->has_type<pattern_token::variable>())
        modality_index = tokens_parser::parse_token<ast::variable>(parser);

    return modality_index;
}

ast::group_modality_index_ptr formulas_parser::parse_group_modality(parser_helper &parser) {
    parser.check_next_token<punctuation_token::lpar>();
    auto mods = parser.parse_list<ast::single_modality_index_ptr>([&] () { return formulas_parser::parse_term(parser); });
    parser.check_next_token<punctuation_token::rpar>();

    return mods;
}
