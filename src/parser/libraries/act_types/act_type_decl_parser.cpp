#include "../../../../include/parser/libraries/act_types/act_type_decl_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/common/parameters_parser.h"
#include "../../../../include/parser/libraries/act_types/act_type_events_parser.h"
#include "../../../../include/parser/libraries/act_types/act_type_designated_parser.h"
#include "../../../../include/parser/libraries/act_types/act_type_preconditions_parser.h"
#include "../../../../include/parser/libraries/act_types/act_type_effects_parser.h"

using namespace epddl;

ast::action_type_ptr act_type_decl_parser::parse(epddl::parser_helper &helper) {
    helper.check_next_token<keyword_token::action>();
    ast::identifier_ptr action_type_name = tokens_parser::parse_identifier(helper);       // Eating action-type name (identifier)

    ast::parameters_ptr params = parameters_parser::parse(helper);
    ast::ident_list events_names = act_type_events_parser::parse(helper);
    // todo: relations
    ast::ident_list designated_names = act_type_designated_parser::parse(helper);
    auto event_preconditions  = act_type_preconditions_parser::parse(helper);
    auto event_postconditions = act_type_effects_parser::parse(helper);

    return std::make_unique<ast::action_type>(std::move(action_type_name), std::move(params), std::move(events_names),
                                              std::move(designated_names), std::move(event_preconditions),
                                              std::move(event_postconditions));
}
