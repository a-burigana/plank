#include "../../include/parser/main_decl_parser.h"
#include "../../include/parser/domains/domain_parser.h"
#include "../../include/parser/libraries/act_type_library_parser.h"
#include "../../include/parser/problems/problem_parser.h"
#include "../../include/error-manager/epddl_exception.h"

using namespace epddl;
using namespace epddl::parser;

ast::main_decl main_decl_parser::parse(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();         // Eating '('
    helper.check_next_token<keyword_token::define>();           // Eating 'define'
    helper.check_next_token<punctuation_token::lpar>();         // Eating '('

    const token_ptr &tok = helper.peek_next_token();

    ast::main_decl decl;

    if (tok->has_type<keyword_token::domain>())
        decl = domain_parser::parse(helper);
    else if (tok->has_type<keyword_token::library>())
        decl = act_type_library_parser::parse(helper);
    else if (tok->has_type<keyword_token::problem>())
        decl = problem_parser::parse(helper);
    else
        throw EPDDLException{std::string{""}, tok->get_row(), tok->get_col(),
                             std::string{"Expected 'domain', 'action-type-library' or 'problem'. Found : '" + tok->get_lexeme() + "'."}};

    helper.check_next_token<punctuation_token::rpar>();         // Eating ')'

    return decl;
}
