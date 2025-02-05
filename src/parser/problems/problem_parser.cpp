#include "../../../include/parser/problems/problem_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/error-manager/epddl_exception.h"
#include "../../../include/parser/problems/problem_domain_parser.h"
#include "../../../include/parser/domains/requirements_parser.h"
#include "../../../include/parser/problems/objects_parser.h"
#include "../../../include/parser/problems/agents_parser.h"
#include "../../../include/parser/problems/agent_groups_parser.h"
#include "../../../include/parser/common/modalities_decl_parser.h"
#include "../../../include/parser/problems/initial_state_parser.h"
#include "../../../include/parser/problems/goal_parser.h"
#include "../../../include/parser/problems/static_predicates_decl_parser.h"

using namespace epddl;

ast::problem_ptr problem_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::problem>();                              // Eating 'problem'
    ast::identifier_ptr problem_name = tokens_parser::parse_identifier(helper);     // Eating problem name (identifier)
    helper.check_next_token<punctuation_token::rpar>();                             // Eating ')'

    ast::problem_item_list problem_items = helper.parse_list<ast::problem_item>([&] () { return problem_parser::parse_problem_item(helper); });

    return std::make_unique<ast::problem>(std::move(problem_name), std::move(problem_items));
}

ast::problem_item problem_parser::parse_problem_item(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();    // Eating '('
    const token_ptr &tok = helper.peek_next_token();       // Eating keyword

    ast::problem_item item;

    if (tok->has_type<keyword_token::prob_domain>())
        item = problem_domain_parser::parse(helper);
    else if (tok->has_type<keyword_token::requirements>())
        item = requirements_parser::parse(helper);
    else if (tok->has_type<keyword_token::objects>())
        item = objects_parser::parse(helper);
    else if (tok->has_type<keyword_token::agents>())
        item = agents_parser::parse(helper);
    else if (tok->has_type<keyword_token::agent_groups>())
        item = agent_groups_parser::parse(helper);
    else if (tok->has_type<keyword_token::static_predicates>())
        item = static_predicates_decl_parser::parse(helper);
    else if (tok->has_type<keyword_token::modalities>())
        item = modalities_decl_parser::parse(helper);
    else if (tok->has_type<keyword_token::init>())
        item = initial_state_parser::parse(helper);
    else if (tok->has_type<keyword_token::goal>())
        item = goal_parser::parse(helper);
    else
        throw EPDDLException{std::string{""}, tok->get_row(), tok->get_col(), std::string{"Expected keyword."}};

    helper.check_next_token<punctuation_token::rpar>();    // Eating ')'
    return item;
}
