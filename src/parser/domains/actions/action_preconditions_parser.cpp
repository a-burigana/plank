#include "../../../../include/parser/domains/actions/action_preconditions_parser.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include <memory>

using namespace epddl;

ast::formula_ptr action_preconditions_parser::parse(epddl::parser_helper &parser) {
    parser.check_next_token<keyword_token::precondition>();
    return formulas_parser::parse_formula(parser);
}
