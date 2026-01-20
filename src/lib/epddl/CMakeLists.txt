# MIT License
#
# Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

set(
    EPDDL_LIB_SRC
    grounder/grounder_helper.cpp
    grounder/language_grounder.cpp
    grounder/initial_state/facts_init_grounder.cpp
    grounder/initial_state/finitary_s5_theory_grounder.cpp
    grounder/initial_state/explicit_initial_state_grounder.cpp
    grounder/initial_state/initial_state_grounder.cpp
    grounder/actions/obs_conditions_grounder.cpp
    grounder/actions/actions_grounder.cpp
    grounder/actions/events_grounder.cpp
    grounder/formulas/formulas_and_lists_grounder.cpp
    lexer/lexer.cpp
    parser/domains/domain_libraries_parser.cpp
    parser/domains/predicates_decl_parser.cpp
    parser/domains/types_decl_parser.cpp
    parser/domains/domain_parser.cpp
    parser/domains/actions/action_decl_parser.cpp
    parser/domains/actions/obs_conditions_parser.cpp
    parser/domains/actions/action_signatures_parser.cpp
    parser/domains/constants_decl_parser.cpp
    parser/domains/events/event_postconditions_parser.cpp
    parser/domains/events/event_decl_parser.cpp
    parser/domains/requirements_parser.cpp
    parser/libraries/event_conditions_parser.cpp
    parser/libraries/act_type_decl_parser.cpp
    parser/libraries/act_type_library_parser.cpp
    parser/problems/init/finitary_s5_theory_parser.cpp
    parser/problems/init/facts_init_parser.cpp
    parser/problems/init/initial_state_parser.cpp
    parser/problems/init/explicit_initial_state_parser.cpp
    parser/problems/objects_parser.cpp
    parser/problems/goal_parser.cpp
    parser/problems/agents_parser.cpp
    parser/problems/problem_domain_parser.cpp
    parser/problems/agent_groups_parser.cpp
    parser/problems/problem_parser.cpp
    parser/common/formulas_parser.cpp
    parser/common/parameters_parser.cpp
    parser/common/typed_elem_parser.cpp
    parser/tokens/tokens_parser.cpp
    ast/domains/actions/obs_conditions_ast.cpp
    ast/domains/events/events_postconditions_ast.cpp
    ast/problems/init/finitary_s5_theory_ast.cpp
    ast/common/formulas_ast.cpp
    type-checker/domains/events_type_checker.cpp
    type-checker/domains/domains_type_checker.cpp
    type-checker/domains/actions_type_checker.cpp
    type-checker/libraries/act_types_type_checker.cpp
    type-checker/libraries/act_type_library_type_checker.cpp
    type-checker/problems/facts_init_type_checker.cpp
    type-checker/problems/initial_states_type_checker.cpp
    type-checker/problems/problems_type_checker.cpp
    type-checker/problems/agent_groups_type_checker.cpp
    type-checker/common/formulas_and_lists_type_checker.cpp
    type-checker/common/requirements_type_checker.cpp
    type-checker/type_checker_helper.cpp
    json-printer/planning_task_printer.cpp
    json-printer/actions_printer.cpp
    json-printer/initial_state_printer.cpp
    json-printer/facts_printer.cpp
    json-printer/language_printer.cpp
    json-printer/formulas_printer.cpp
)

set(
    EPDDL_LIB_HEADERS
    ../../../include/lib/epddl/grounder/relations/relations_grounder.h
    ../../../include/lib/epddl/grounder/combinations_handler.h
    ../../../include/lib/epddl/grounder/variables_assignment.h
    ../../../include/lib/epddl/grounder/language_grounder.h
    ../../../include/lib/epddl/grounder/initial_state/explicit_initial_state_grounder.h
    ../../../include/lib/epddl/grounder/initial_state/initial_state_grounder.h
    ../../../include/lib/epddl/grounder/initial_state/facts_init_grounder.h
    ../../../include/lib/epddl/grounder/initial_state/finitary_s5_theory_grounder.h
    ../../../include/lib/epddl/grounder/grounder_info.h
    ../../../include/lib/epddl/grounder/actions/obs_conditions_grounder.h
    ../../../include/lib/epddl/grounder/actions/events_grounder.h
    ../../../include/lib/epddl/grounder/actions/actions_grounder.h
    ../../../include/lib/epddl/grounder/grounder_helper.h
    ../../../include/lib/epddl/grounder/formulas/formulas_and_lists_grounder.h
    ../../../include/lib/epddl/lexer/lexer.h
    ../../../include/lib/epddl/lexer/tokens/dictionary.h
    ../../../include/lib/epddl/lexer/tokens/token.h
    ../../../include/lib/epddl/lexer/tokens/definitions/requirements_def.h
    ../../../include/lib/epddl/lexer/tokens/definitions/modalities_def.h
    ../../../include/lib/epddl/lexer/tokens/definitions/token_types_def.h
    ../../../include/lib/epddl/lexer/tokens/definitions/tokens_def.h
    ../../../include/lib/epddl/lexer/tokens/token_types.h
    ../../../include/lib/epddl/error-manager/error_manager.h
    ../../../include/lib/epddl/error-manager/exit_code.h
    ../../../include/lib/epddl/error-manager/epddl_exception.h
    ../../../include/lib/epddl/utils/traits.h
    ../../../include/lib/epddl/parser/parser_utils.h
    ../../../include/lib/epddl/parser/domains/requirements_parser.h
    ../../../include/lib/epddl/parser/domains/predicates_decl_parser.h
    ../../../include/lib/epddl/parser/domains/domain_libraries_parser.h
    ../../../include/lib/epddl/parser/domains/constants_decl_parser.h
    ../../../include/lib/epddl/parser/domains/types_decl_parser.h
    ../../../include/lib/epddl/parser/domains/domain_parser.h
    ../../../include/lib/epddl/parser/domains/actions/obs_conditions_parser.h
    ../../../include/lib/epddl/parser/domains/actions/action_signatures_parser.h
    ../../../include/lib/epddl/parser/domains/actions/action_decl_parser.h
    ../../../include/lib/epddl/parser/domains/events/event_decl_parser.h
    ../../../include/lib/epddl/parser/domains/events/event_postconditions_parser.h
    ../../../include/lib/epddl/parser/file_parser.h
    ../../../include/lib/epddl/parser/libraries/act_type_library_parser.h
    ../../../include/lib/epddl/parser/libraries/act_type_decl_parser.h
    ../../../include/lib/epddl/parser/libraries/event_conditions_parser.h
    ../../../include/lib/epddl/parser/problems/init/facts_init_parser.h
    ../../../include/lib/epddl/parser/problems/init/finitary_s5_theory_parser.h
    ../../../include/lib/epddl/parser/problems/init/initial_state_parser.h
    ../../../include/lib/epddl/parser/problems/init/explicit_initial_state_parser.h
    ../../../include/lib/epddl/parser/problems/agent_groups_parser.h
    ../../../include/lib/epddl/parser/problems/objects_parser.h
    ../../../include/lib/epddl/parser/problems/agents_parser.h
    ../../../include/lib/epddl/parser/problems/problem_domain_parser.h
    ../../../include/lib/epddl/parser/problems/goal_parser.h
    ../../../include/lib/epddl/parser/problems/problem_parser.h
    ../../../include/lib/epddl/parser/common/typed_elem_parser.h
    ../../../include/lib/epddl/parser/common/formulas_parser.h
    ../../../include/lib/epddl/parser/common/relations_parser.h
    ../../../include/lib/epddl/parser/common/parameters_parser.h
    ../../../include/lib/epddl/parser/parser_helper.h
    ../../../include/lib/epddl/parser/tokens/tokens_parser.h
    ../../../include/lib/epddl/ast/ast_node.h
    ../../../include/lib/epddl/ast/domains/domain_ast.h
    ../../../include/lib/epddl/ast/domains/constants_decl_ast.h
    ../../../include/lib/epddl/ast/domains/domain_libraries_ast.h
    ../../../include/lib/epddl/ast/domains/predicates_decl_ast.h
    ../../../include/lib/epddl/ast/domains/types_decl_ast.h
    ../../../include/lib/epddl/ast/domains/actions/action_signatures_ast.h
    ../../../include/lib/epddl/ast/domains/actions/obs_conditions_ast.h
    ../../../include/lib/epddl/ast/domains/actions/action_decl_ast.h
    ../../../include/lib/epddl/ast/domains/events/event_decl_ast.h
    ../../../include/lib/epddl/ast/domains/events/event_postconditions_ast.h
    ../../../include/lib/epddl/ast/libraries/act_type_library_ast.h
    ../../../include/lib/epddl/ast/libraries/event_conditions_ast.h
    ../../../include/lib/epddl/ast/libraries/act_type_decl_ast.h
    ../../../include/lib/epddl/ast/problems/init/explicit_initial_state_ast.h
    ../../../include/lib/epddl/ast/problems/init/initial_state_decl_ast.h
    ../../../include/lib/epddl/ast/problems/init/finitary_s5_theory_ast.h
    ../../../include/lib/epddl/ast/problems/init/facts_init_ast.h
    ../../../include/lib/epddl/ast/problems/labels_ast.h
    ../../../include/lib/epddl/ast/problems/agent_groups_decl_ast.h
    ../../../include/lib/epddl/ast/problems/objects_decl_ast.h
    ../../../include/lib/epddl/ast/problems/goal_decl_ast.h
    ../../../include/lib/epddl/ast/problems/agents_decl_ast.h
    ../../../include/lib/epddl/ast/problems/problem_ast.h
    ../../../include/lib/epddl/ast/problems/problem_domain_ast.h
    ../../../include/lib/epddl/ast/common/formulas_ast.h
    ../../../include/lib/epddl/ast/common/relations_ast.h
    ../../../include/lib/epddl/ast/common/typed_elem_ast.h
    ../../../include/lib/epddl/ast/common/requirements_decl_ast.h
    ../../../include/lib/epddl/ast/common/agent_groups_ast.h
    ../../../include/lib/epddl/ast/common/terms_ast.h
    ../../../include/lib/epddl/ast/planning_specification.h
    ../../../include/lib/epddl/ast/tokens/tokens_ast.h
    ../../../include/lib/epddl/type-checker/type.h
    ../../../include/lib/epddl/type-checker/domains/actions_type_checker.h
    ../../../include/lib/epddl/type-checker/domains/domains_type_checker.h
    ../../../include/lib/epddl/type-checker/domains/events_type_checker.h
    ../../../include/lib/epddl/type-checker/context/events_context.h
    ../../../include/lib/epddl/type-checker/context/entities_context.h
    ../../../include/lib/epddl/type-checker/context/components_names_context.h
    ../../../include/lib/epddl/type-checker/context/context.h
    ../../../include/lib/epddl/type-checker/context/requirements_context.h
    ../../../include/lib/epddl/type-checker/context/predicates_context.h
    ../../../include/lib/epddl/type-checker/context/actions_context.h
    ../../../include/lib/epddl/type-checker/context/action_types_context.h
    ../../../include/lib/epddl/type-checker/context/context_utils.h
    ../../../include/lib/epddl/type-checker/context/scope.h
    ../../../include/lib/epddl/type-checker/context/context_types.h
    ../../../include/lib/epddl/type-checker/context/types_context.h
    ../../../include/lib/epddl/type-checker/type_checker.h
    ../../../include/lib/epddl/type-checker/type_checker_helper.h
    ../../../include/lib/epddl/type-checker/libraries/act_type_library_type_checker.h
    ../../../include/lib/epddl/type-checker/libraries/act_types_type_checker.h
    ../../../include/lib/epddl/type-checker/problems/agent_groups_type_checker.h
    ../../../include/lib/epddl/type-checker/problems/problems_type_checker.h
    ../../../include/lib/epddl/type-checker/problems/facts_init_type_checker.h
    ../../../include/lib/epddl/type-checker/problems/initial_states_type_checker.h
    ../../../include/lib/epddl/type-checker/common/formulas_and_lists_type_checker.h
    ../../../include/lib/epddl/type-checker/common/relations_type_checker.h
    ../../../include/lib/epddl/type-checker/common/requirements_type_checker.h
    ../../../include/lib/epddl/json-printer/formulas_printer.h
    ../../../include/lib/epddl/json-printer/planning_task_printer.h
    ../../../include/lib/epddl/json-printer/language_printer.h
    ../../../include/lib/epddl/json-printer/initial_state_printer.h
    ../../../include/lib/epddl/json-printer/facts_printer.h
    ../../../include/lib/epddl/json-printer/actions_printer.h
)

# EPDDL library
add_library(epddl_lib ${EPDDL_LIB_SRC} ${EPDDL_LIB_HEADERS})
target_compile_features(epddl_lib PUBLIC cxx_std_17)

target_include_directories(epddl_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(epddl_lib PRIVATE ../../../include/lib/epddl ../../../include/lib/del)

#target_enable_warnings(epddl_lib)
target_code_coverage(epddl_lib)
add_sanitizers(epddl_lib)
