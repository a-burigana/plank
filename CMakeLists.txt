cmake_minimum_required(VERSION 3.16)

project(EPDDL VERSION 1.0
    DESCRIPTION "Epistemic Planning Domain Definition Language"
    LANGUAGES C CXX)

set(
    EPDDL_SOURCES
#    src/ast.cpp
    src/lex.cpp
    src/main.cpp
#    src/parser.cpp
)

set(
    EPDDL_HEADERS
#    include/ast/ast.h
    include/lex/lex.h
#    include/parser/parser.h
    include/lex/lex_utils.h
#    include/ast/ast_utils.h
#    include/parser/parser_utils.h
    include/epddl_exception.h
    include/tokens/token_types.h
    include/grammar/grammar.h
    include/tokens/tokens.h
    include/grammar/requirements.h
        include/ast/macro_ast.h
    include/grammar/domain/domain_def.h
    include/grammar/domain/domain_libraries_def.h
    include/grammar/domain/domain_requirements_def.h
    include/grammar/domain/domain_types_def.h
    include/grammar/domain/domain_predicates_def.h
        include/grammar/common/typed_ident_var_def.h
    include/grammar/domain/domain_modalities_def.h
    include/grammar/domain/domain_action_def.h
        include/grammar/formulae/propositional_formula_def.h
        include/grammar/formulae/formula_def.h
        include/grammar/common/signature_def.h
        include/grammar/common/agents_def.h
        include/map_macro.h include/grammar/domain/action_observability_conditions.h include/grammar/common/common_elements_def.h)

#include_directories(include)

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
