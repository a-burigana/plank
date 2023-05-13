cmake_minimum_required(VERSION 3.16)

project(EPDDL VERSION 1.0
    DESCRIPTION "Epistemic Planning Domain Definition Language"
    LANGUAGES C CXX)

set(
    EPDDL_SOURCES
    src/lex.cpp
    src/main.cpp
#    src/parser.cpp
)

set(
    EPDDL_HEADERS
    include/lex/lex.h
    include/lex/dictionary.h
    include/epddl_exception.h
    include/grammar/tokens/token_types_def.h
    include/grammar/grammar.h
    include/grammar/tokens/tokens_def.h
    include/grammar/tokens/requirements_def.h
    include/generators/ast/ast_classes_gen.h
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
    include/grammar/common/agent_def.h
        include/macro_utils.h
    include/grammar/domain/action_observability_conditions.h
    include/grammar/common/common_elements_def.h
    include/generators/tokens/token_types_gen.h
    include/generators/tokens/token_types_aliases_gen.h
    include/generators/ast/ast_forward_decl_gen.h
    include/generators/ast/ast_aliases_gen.h
    include/generators/ast/ast_auxiliary_types_gen.h
    include/generators/tokens/tokens_gen.h
    include/generators/ast/ast_gen.h
    include/grammar/common/parameters_def.h
    include/grammar/formulae/atomic_formula_def.h
    include/grammar/formulae/modal_formula_def.h
    include/grammar/formulae/quantified_formula_def.h
    include/grammar/common/postcondition_def.h
    include/generators/parser/parser_gen.h
        src/parser.cpp include/parser/parser.h)

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
