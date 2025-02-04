#ifndef EPDDL_OBS_CONDITIONS_PARSER_H
#define EPDDL_OBS_CONDITIONS_PARSER_H

#include "../../../ast/domains/actions/obs_conditions_ast.h"
#include "../../parser_helper.h"

namespace epddl {
    class obs_conditions_parser {
    public:
        static ast::obs_cond parse_action_obs_cond(parser_helper &parser);

        static ast::obs_cond parse_obs_cond(parser_helper &parser);

        static ast::single_obs_cond parse_single_obs_cond(parser_helper &parser, bool parse_outer_pars = true);
//        static ast::simple_obs_cond parse_simple_obs_cond(parser_helper &parser);
        static ast::obs_cond_list parse_obs_cond_list(parser_helper &parser);

        static ast::always_obs_cond_ptr parse_always_obs_cond(parser_helper &parser, bool parse_outer_pars = true);
        static ast::if_then_else_obs_cond_ptr parse_if_then_else_obs_cond(parser_helper &parser, bool parse_outer_pars = true);
        static ast::if_obs_cond_ptr parse_if_obs_cond(parser_helper &parser);
        static ast::else_if_obs_cond_ptr parse_else_if_obs_cond(parser_helper &parser);
        static ast::else_obs_cond_ptr parse_else_obs_cond(parser_helper &parser);
        static ast::forall_obs_cond_ptr parse_forall_obs_cond(parser_helper &parser, bool parse_outer_pars = true);
        static ast::default_obs_cond_ptr parse_default_obs_cond(parser_helper &parser, bool parse_outer_pars = true);

        static ast::observing_agent parse_observing_agent(parser_helper &parser);
    };
}

#endif //EPDDL_OBS_CONDITIONS_PARSER_H
