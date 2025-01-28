/*
#ifndef EPDDL_AST_CLASSES_GEN_H
#define EPDDL_AST_CLASSES_GEN_H

#include <list>
#include <optional>

//#include "ast_aliases_gen.h"
#include "../tokens/tokens_gen.h"
#include "ast_forward_decl_gen.h"
#include "ast_variant_elements_gen.h"
#include "../../utils/generator_macros.h"
#include "../../grammar/grammar.h"

namespace epddl::ast {
    class ast_node;
    using ast_node_ptr = std::unique_ptr<ast_node>;

    class ast_node {
    public:
        explicit ast_node() :
                m_parent{} {}

        ast_node(const ast_node &) = delete;
        ast_node &operator=(const ast_node &) = delete;

        ast_node(ast_node &&) = default;
        ast_node &operator=(ast_node &&) = delete;

        virtual ~ast_node() = default;

        void set_parent(ast_node_ptr* parent) {
            if (not m_parent) {
                m_parent = parent;
            }
        }

    private:
        ast_node_ptr *m_parent;
    };

#define epddl_token_type(token_type) token_type
#define epddl_token(t_type, t_scope, t_name, t_lexeme) token_alias(t_type, t_name)

#define element_name(name) name
#define is_terminal(flag) flag

#define terminal(_)               0, null,                               null

#define node(type, name)          1, unique_ptr(type),                   name
#define list_node(type, name)     1, list_(unique_ptr(type)),            name
#define opt_node(type, name)      1, optional_(unique_ptr(type)),        name
#define opt_list_node(type, name) 1, optional_(list_(unique_ptr(type))), name

#define leaf(type, name)          1, unique_ptr(type),                   name
#define list_leaf(type, name)     1, list_(unique_ptr(type)),            name
#define opt_leaf(type, name)      1, optional_(unique_ptr(type)),        name
#define opt_list_leaf(type, name) 1, optional_(list_(unique_ptr(type))), name

#define element_bnf(params...) params

#define constructor_params(type, name) type p_##name
#define constructor_init(type, name)   m_##name{std::move(p_##name)}
#define class_attributes(type, name)   const type m_##name;

#define epddl_element(name, is_terminal, params) \
    class name : public ast_node {                             \
    public:                                                    \
        explicit name(MAP_2ARY_IF_LIST(constructor_params, params)) \
            IFN(is_terminal, :)                                \
            MAP_2ARY_IF_LIST(constructor_init, params) {}           \
                                                               \
    IFN(is_terminal, private:)                                 \
        MAP_IF(class_attributes, params)                       \
    };

// Defining the AST classes for each element of EPDDL
// See "grammar.h"
    epddl_all_element_defs

#undef epddl_element
#undef class_attributes
#undef constructor_init
#undef constructor_params
#undef element_bnf
#undef opt_list_leaf
#undef opt_leaf
#undef list_leaf
#undef leaf
#undef opt_list_node
#undef opt_node
#undef list_node
#undef node
#undef terminal
#undef is_terminal
#undef element_name
#undef epddl_token
#undef epddl_token_type
}

#endif //EPDDL_AST_CLASSES_GEN_H
*/
