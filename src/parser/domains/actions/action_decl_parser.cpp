#include "../../../../include/parser/domains/actions/action_decl_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/common/parameters_parser.h"
#include "../../../../include/parser/domains/actions/action_signatures_parser.h"
#include "../../../../include/parser/domains/actions/action_preconditions_parser.h"
#include "../../../../include/parser/domains/actions/obs_conditions_parser.h"

using namespace epddl;

ast::action_ptr action_decl_parser::parse(epddl::parser_helper &parser) {
    parser.check_next_token<keyword_token::action>();
    ast::identifier_ptr action_name = tokens_parser::parse_identifier(parser);       // Eating action name (identifier)

    ast::parameters_ptr params = parameters_parser::parse(parser);
    ast::action_signature_ptr sign = action_signatures_parser::parse(parser);
    ast::formula_ptr pre = action_preconditions_parser::parse(parser);
    auto obs_conditions = parser.parse_optional<keyword_token::obs_conditions, ast::obs_cond>([&] () { return obs_conditions_parser::parse_action_obs_cond(parser); });

    return std::make_unique<ast::action>(std::move(action_name), std::move(params), std::move(sign), std::move(pre), std::move(obs_conditions));
}
