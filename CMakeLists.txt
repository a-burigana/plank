cmake_minimum_required(VERSION 3.16)

project(EPDDL VERSION 1.0
    DESCRIPTION "Epistemic Planning Domain Definition Language"
    LANGUAGES C CXX)

# BOOST
#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.74.0 REQUIRED COMPONENTS filesystem)
message(STATUS "Boost version: ${Boost_VERSION}")

include_directories(${Boost_INCLUDE_DIR})

#set(
#    EPDDL_SOURCES
#        src/lexer/lexer.cpp
#    src/main.cpp
##    src/parser.cpp
#)
#
#set(EPDDL_HEADERS
#        include/lexer/lexer.h
#        include/lexer/tokens/dictionary.h
#        include/error-manager/epddl_exception.h
#        include/lexer/tokens/definitions/token_types_def.h
#        include/lexer/tokens/definitions/tokens_def.h
#        include/lexer/tokens/definitions/requirements_def.h
#        include/lexer/tokens/token_types.h
#        include/parser/parser_helper.h
#        include/utils/traits.h
#        include/parser/parser_utils.h src/type-checker/type_checker_helper.cpp
#        include/type-checker/type_checker_helper.h src/error-manager/error_manager.cpp
#        include/error-manager/error_manager.h
#        include/lexer/tokens/token.h src/parser/domains/domain_parser.cpp
#        include/parser/domains/domain_parser.h
#        src/parser/domains/domain_libraries_parser.cpp
#        include/parser/domains/domain_libraries_parser.h
#        src/parser/tokens/tokens_parser.cpp
#        include/parser/tokens/tokens_parser.h
#        src/parser/domains/requirements_parser.cpp
#        include/parser/domains/requirements_parser.h
#        src/parser/domains/types_decl_parser.cpp
#        include/parser/domains/types_decl_parser.h
#        src/parser/domains/predicates_decl_parser.cpp
#        include/parser/domains/predicates_decl_parser.h
#        src/parser/domains/actions/action_decl_parser.cpp
#        include/parser/domains/actions/action_decl_parser.h
#        src/parser/common/typed_elem_parser.cpp
#        include/parser/common/typed_elem_parser.h
#        src/parser/common/parameters_parser.cpp
#        include/parser/common/parameters_parser.h
#        src/parser/domains/actions/action_signatures_parser.cpp
#        include/parser/domains/actions/action_signatures_parser.h
#        src/parser/domains/actions/obs_conditions_parser.cpp
#        include/parser/domains/actions/obs_conditions_parser.h
#        src/parser/common/formulas_parser.cpp
#        include/parser/common/formulas_parser.h
#        include/ast/common/formulas_ast.h
#        include/ast/ast_node.h
#        include/ast/tokens/tokens_ast.h
#        include/ast/common/typed_elem_ast.h
#        include/ast/domains/actions/action_decl_ast.h
#        include/ast/domains/actions/action_signatures_ast.h
#        include/ast/domains/actions/obs_conditions_ast.h
#        include/ast/domains/domain_libraries_ast.h
#        include/ast/domains/domain_ast.h
#        include/ast/domains/predicates_decl_ast.h
#        include/ast/common/requirements_decl_ast.h
#        include/ast/domains/types_decl_ast.h
#        src/parser/libraries/act_type_library_parser.cpp
#        include/parser/libraries/act_type_library_parser.h
#        include/ast/libraries/act_type_library_ast.h
#        include/ast/domains/events/event_postconditions_ast.h
#        include/ast/libraries/act_type_decl_ast.h
#        src/parser/libraries/act_type_decl_parser.cpp
#        include/parser/libraries/act_type_decl_parser.h
#        src/parser/domains/events/event_postconditions_parser.cpp
#        include/parser/domains/events/event_postconditions_parser.h
#        include/ast/problems/problem_ast.h
#        include/ast/problems/agents_decl_ast.h
#        include/ast/problems/objects_decl_ast.h
#        include/ast/problems/init/initial_state_decl_ast.h
#        include/ast/problems/goal_decl_ast.h
#        include/ast/problems/agent_groups_decl_ast.h
#        include/ast/problems/problem_domain_ast.h
#        src/parser/problems/agent_groups_parser.cpp
#        include/parser/problems/agent_groups_parser.h
#        src/parser/problems/agents_parser.cpp
#        include/parser/problems/agents_parser.h
#        src/parser/problems/problem_domain_parser.cpp
#        include/parser/problems/problem_domain_parser.h
#        src/parser/problems/goal_parser.cpp
#        include/parser/problems/goal_parser.h
#        src/parser/problems/init/initial_state_parser.cpp
#        include/parser/problems/init/initial_state_parser.h
#        src/parser/problems/objects_parser.cpp
#        include/parser/problems/objects_parser.h
#        src/parser/problems/problem_parser.cpp
#        include/parser/problems/problem_parser.h
#        include/ast/common/relations_ast.h
#        src/parser/common/relations_parser.cpp
#        include/parser/common/relations_parser.h
#        include/ast/problems/labels_ast.h
#        include/ast/problems/init/explicit_inititial_state_ast.h
#        src/parser/problems/init/explicit_initial_state_parser.cpp
#        include/parser/problems/init/explicit_initial_state_parser.h
#        include/lexer/tokens/definitions/modalities_def.h
#        include/type-checker/entity_kinds.h
#        include/type-checker/type.h
#        include/type-checker/context.h
#        include/ast/problems/init/static_init_ast.h
#        src/parser/problems/init/static_init_parser.cpp
#        include/parser/problems/init/static_init_parser.h
#        include/ast/domains/constants_decl_ast.h
#        src/parser/domains/constants_decl_parser.cpp
#        include/parser/domains/constants_decl_parser.h
#        include/ast/domains/events/event_decl_ast.h
#        src/parser/domains/events/event_decl_parser.cpp
#        include/parser/domains/events/event_decl_parser.h
#        src/type-checker/common/formulas_type_checker.cpp
#        include/type-checker/common/formulas_type_checker.h
#        src/type-checker/domains/events_type_checker.cpp
#        include/type-checker/domains/events_type_checker.h
#        src/type-checker/domains/actions_type_checker.cpp
#        include/type-checker/domains/actions_type_checker.h
#        src/type-checker/libraries/act_types_type_checker.cpp
#        include/type-checker/libraries/act_types_type_checker.h
#        src/type-checker/problems/initial_states_type_checker.cpp
#        include/type-checker/problems/initial_states_type_checker.h
#        src/type-checker/common/relations_type_checker.cpp
#        include/type-checker/common/relations_type_checker.h
#        src/type-checker/problems/static_init_type_checker.cpp
#        include/type-checker/problems/static_init_type_checker.h
#        src/ast/common/formulas_ast.cpp
#        src/ast/common/relations_ast.cpp
#        src/ast/domains/actions/obs_conditions_ast.cpp
#        src/ast/domains/events/events_postconditions_ast.cpp
#        src/type-checker/domains/domains_type_checker.cpp
#        include/type-checker/domains/domains_type_checker.h
#        src/type-checker/libraries/act_type_library_type_checker.cpp
#        include/type-checker/libraries/act_type_library_type_checker.h
#        src/type-checker/libraries/problems_type_checker.cpp
#        include/type-checker/problems/problems_type_checker.h
#        src/type-checker/common/requirements_type_checker.cpp
#        include/type-checker/common/requirements_type_checker.h
#        include/utils/clipp.h
#        include/parser/parse_file.h
#        include/type-checker/type_checker.h
#        src/type-checker/problems/agent_groups_type_checker.cpp
#        include/type-checker/problems/agent_groups_type_checker.h
#        src/grounder/grounder_helper.cpp
#        include/grounder/grounder_helper.h
#        include/del/formulas/formula_types.h
#        include/del/del_types.h
#        include/del/formulas/modal/box_formula.h
#        include/del/formulas/modal/diamond_formula.h)

# Collect all headers in include/**
file(GLOB_RECURSE EPDDL_HEADERS
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
        )

# Collect all sources in src/**
file(GLOB_RECURSE EPDDL_SOURCES
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        )

# EXECUTABLES
add_executable(EPDDL ${EPDDL_SOURCES} ${EPDDL_HEADERS} include/grounder/combinations_handler.h include/ast/libraries/event_conditions_ast.h src/parser/libraries/event_conditions_parser.cpp include/parser/libraries/event_conditions_parser.h include/type-checker/context/predicates_context.h include/type-checker/context/events_context.h include/type-checker/context/actions_context.h include/type-checker/context/action_types_context.h include/type-checker/context/requirements_context.h include/type-checker/context/context_types.h include/type-checker/context/types_context.h include/type-checker/context/entities_context.h include/type-checker/context/context_utils.h include/type-checker/context/scope.h)


# Compilation Features
target_compile_features(EPDDL PUBLIC cxx_std_17)
#target_compile_features(EPDDL PRIVATE cxx_std_${CMAKE_CXX_STANDARD})
#target_compile_options(EPDDL PRIVATE -Wall) #To show one error at the time

# Auto-ignore build directory
if (NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
    file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif ()
