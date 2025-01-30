#include "../../../include/parser/problems/problem_domain_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;

ast::problem_domain_ptr problem_domain_parser::parse(epddl::parser_helper &helper) {
    helper.check_next_token<keyword_token::prob_domain>();
    auto domain_name = tokens_parser::parse_identifier(helper);

    return std::make_unique<ast::problem_domain>(std::move(domain_name));
}
