cmake_minimum_required(VERSION 3.16)

project(EPDDL VERSION 1.0
    DESCRIPTION "Epistemic Planning Domain Definition Language"
    LANGUAGES C CXX)

set(
    EPDDL_SOURCES
        src/lexer/lexer.cpp
    src/main.cpp
#    src/parser.cpp
)

set(EPDDL_HEADERS
        include/lexer/lexer.h
        include/lexer/dictionary.h
        include/error-manager/epddl_exception.h
        include/grammar/tokens/token_types_def.h
        include/grammar/tokens/tokens_def.h
        include/grammar/tokens/requirements_def.h
        include/generators/tokens/token_types_gen.h
        src/parser/parser_helper.cpp
        include/parser/parser_helper.h
        include/utils/traits.h
        include/parser/parser_utils.h src/type-checker/type_checker.cpp
        include/type-checker/type_checker.h src/error-manager/error_manager.cpp
        include/error-manager/error_manager.h
        include/ast/ast.h
        src/lexer/token.cpp
        include/lexer/token.h src/parser/domains/domain_parser.cpp
        include/parser/domains/domain_parser.h
        src/parser/domains/act_type_libraries_parser.cpp
        include/parser/domains/act_type_libraries_parser.h
        src/parser/tokens/tokens_parser.cpp
        include/parser/tokens/tokens_parser.h
        src/parser/domains/requirements_parser.cpp include/parser/domains/requirements_parser.h src/parser/domains/types_decl_parser.cpp include/parser/domains/types_decl_parser.h src/parser/domains/predicates_decl_parser.cpp include/parser/domains/predicates_decl_parser.h src/parser/domains/actions/action_decl_parser.cpp include/parser/domains/actions/action_decl_parser.h src/parser/common/typed_elem_parser.cpp include/parser/common/typed_elem_parser.h src/parser/common/parameters_parser.cpp include/parser/common/parameters_parser.h src/parser/domains/actions/action_signatures_parser.cpp include/parser/domains/actions/action_signatures_parser.h src/parser/domains/actions/action_preconditions_parser.cpp include/parser/domains/actions/action_preconditions_parser.h src/parser/domains/actions/obs_conditions_parser.cpp include/parser/domains/actions/obs_conditions_parser.h src/parser/domains/actions/expressions_parser.cpp include/parser/domains/actions/expressions_parser.h src/parser/common/formulas_parser.cpp include/parser/common/formulas_parser.h src/parser/common/postconditions_parser.cpp include/parser/common/postconditions_parser.h src/parser/common/modalities_decl_parser.cpp include/parser/common/modalities_decl_parser.h include/ast/common/formulas_ast.h include/ast/ast_node.h include/ast/tokens/tokens_ast.h include/ast/common/modalities_decl_ast.h include/ast/common/parameters_ast.h include/ast/common/postconditions_ast.h include/ast/common/typed_elem_ast.h include/ast/domains/actions/action_decl_ast.h include/ast/domains/actions/action_preconditions_ast.h include/ast/domains/actions/action_signatures_ast.h include/ast/domains/actions/expressions_ast.h include/ast/domains/actions/obs_conditions_ast.h include/ast/domains/act_type_libraries_ast.h include/ast/domains/domain_ast.h include/ast/domains/predicates_decl_ast.h include/ast/domains/requirements_ast.h include/ast/domains/types_decl_ast.h)

# EXECUTABLES
add_executable(EPDDL ${EPDDL_SOURCES} ${EPDDL_HEADERS})


# Compilation Features
target_compile_features(EPDDL PUBLIC cxx_std_17)
#target_compile_features(EPDDL PRIVATE cxx_std_${CMAKE_CXX_STANDARD})
#target_compile_options(EPDDL PRIVATE -Wall) #To show one error at the time

# Auto-ignore build directory
if (NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
    file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif ()
