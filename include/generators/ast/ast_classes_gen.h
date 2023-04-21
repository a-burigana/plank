#ifndef EPDDL_AST_CLASSES_GEN_H
#define EPDDL_AST_CLASSES_GEN_H

#include <list>
#include <optional>

#include "../../map_macro.h"

namespace epddl::ast {
    class ast_node;
    using ast_node_ptr = std::unique_ptr<ast_node>;

    class ast_node {
    public:
        explicit ast_node() :
                m_parent{} {}

        ast_node(const ast_node &) = delete;
        ast_node(ast_node &&) = default;

        ast_node &operator=(const ast_node &) = delete;
        ast_node &operator=(ast_node &&) = delete;

        virtual ~ast_node() = default;

        void set_parent(ast_node_ptr parent) {
            if (!m_parent) {
                m_parent = std::move(parent);
            }
        }

    private:
        ast_node_ptr m_parent;
    };

#define epddl_token_type(token_type) token_type
#define class_name(c_name) c_name
#define epddl_token(t_type, t_scope, t_name, t_lexeme) token_alias(t_type, t_name)

#define param(type, name) unique_ptr(type), name
#define list_param(type, name) std::list<unique_ptr(type)>, name
#define opt_param(type, name) std::optional<unique_ptr(type)>, name
#define opt_list_param(type, name) std::optional<std::list<unique_ptr(type)>>, name
#define class_params(params...) params

#define constructor_params(type, name) type p_##name
#define constructor_init(type, name) m_##name{std::move(p_##name)}
#define class_attributes(type, name) const type m_##name;

#define ast_class(name, params) \
    class name : public ast_node {                            \
    public:                                                   \
        explicit name(MAP_LIST(constructor_params, params)) : \
            MAP_LIST(constructor_init, params) {}             \
                                                              \
    private:                                                  \
        MAP(class_attributes, params)                         \
    };

#define parse_element(_)
#define epddl_element(ast_class, _) ast_class
// Defining the AST classes for each element of EPDDL
// See "grammar.h"
    epddl_all_element_defs

#undef epddl_element
#undef parse_element
#undef ast_class
#undef class_attributes
#undef constructor_init
#undef constructor_params
#undef class_params
#undef opt_list_param
#undef opt_param
#undef list_param
#undef param
#undef epddl_token
#undef class_name
#undef epddl_token_type
}

#endif //EPDDL_AST_CLASSES_GEN_H
