#include "../../../include/parser/common/modalities_decl_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;

ast::modalities_decl_ptr modalities_decl_parser::parse(epddl::parser_helper &helper) {
    helper.check_next_token<keyword_token::modalities>();
    auto mods = helper.parse_list<ast::modality_name_ptr>([&] () { return tokens_parser::parse_modality_name(helper); });

    return std::make_unique<ast::modalities_decl>(std::move(mods));
}
