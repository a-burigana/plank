#include "../../../../include/parser/problems/initial_states/initial_state_parser.h"
#include "../../../../include/error-manager/epddl_exception.h"
#include "../../../../include/parser/problems/initial_states/explicit_initial_state_parser.h"
#include "../../../../include/parser/problems/initial_states/finitary_s5_theory_parser.h"

using namespace epddl;

ast::initial_state initial_state_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::init>();
    const token_ptr &tok = helper.peek_next_token();
    ast::initial_state init;

    if (tok->has_type<keyword_token::worlds>())
        init = explicit_initial_state_parser::parse(helper);
    else if (tok->has_type<punctuation_token::lpar>())
        init = finitary_s5_theory_parser::parse(helper);
    else
        throw EPDDLException{std::string{""}, tok->get_row(), tok->get_col(), std::string{"Expected initial state declaration. Found: "} + tok->to_string()};

    return init;
}
