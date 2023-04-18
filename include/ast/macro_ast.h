#ifndef EPDDL_MACRO_AST_H
#define EPDDL_MACRO_AST_H

#include <cstdlib>
#include <memory>
#include <optional>
#include <string>
#include <set>
#include <list>
#include <map>
#include <utility>

#include "../lex/lex.h"
#include "ast_utils.h"
#include "../grammar/grammar.h"
#include "../map_macro.h"

using namespace epddl::utils::ast_node;

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

#define class_name(c_name) class c_name;
#define ast_class(name, _) name
#define epddl_element(ast_class, _) ast_class
    // Forward declaration of AST classes
    epddl_all_element_defs
#undef class_name

#define unique_ptr0(type) type##_ptr
#define unique_ptr(type) unique_ptr0(type)
#define class_name(c_name) using unique_ptr(c_name) = std::unique_ptr<c_name>;
    // Declaration of unique pointers for AST classes
    epddl_all_element_defs
#undef epddl_element
#undef ast_class
#undef class_name

#define type_name(name) name
#define epddl_token(t_type, t_scope, t_name, t_lexeme) token_ptr_alias(t_type, t_name)
#define variant(types...) types
#define epddl_auxiliary_type(name, types) using name = std::variant<types>;
    // Declaration of auxiliary types
    epddl_all_auxiliary_type_defs
#undef epddl_auxiliary_type
#define epddl_auxiliary_type(name, types) using unique_ptr(name) = std::unique_ptr<std::variant<types>>;
    // Declaration of auxiliary unique pointer types
    epddl_all_auxiliary_type_defs
#undef epddl_auxiliary_type
#undef variant
#undef epddl_token
#undef type_name


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
#undef epddl_token_type
#undef class_name

//#define element_name(name) name
//
//#define attribute(type, name) type##_ptr name
//#define list_attribute(type, name) std::list<type##_ptr> name
//#define element_attributes(attributes...) attributes
//
//#define init(name) m_##name{std::move(name)}
//#define element_attributes_init(attributes...) attributes
//
//#define terminal(...)
//#define token(name) const Token_ptr m_token;
//#define node(type, name) const type##_ptr m_##name;
//#define node_list(type, name) const std::list<type##_ptr> m_##name;
//#define element_syntax_tree(tree) tree
//
//#define define_epddl_element(name, attributes, init, syntax_tree) \
//    class name : public ast_node {   \
//    public:                         \
//        explicit name(attributes) : \
//            init {}                 \
//    private:                        \
//        syntax_tree                 \
//    };
//    epddl_bnf
}

//#define ast_domain_def(class_def) \
//    class_def(Domain, epddl::ast::ASTNode, \
//        class_attributes(                  \
//            attr(identifier, name))        \
//            attr(domain_item_list, items)  \
//    )

//#define attr(type, name) const type m_##name;
//#define class_attributes(attributes) private: attributes
//#define class_def(name, super, args...) class name : public super {args};
//ast_domain_def(class_def)
//#undef attr
//
//#define A(S) \
//    S(s,              \
//        I(e,          \
//            INT(i1)   \
//            INT(i2)   \
//        )             \
//        C(            \
//            CHAR(c1)  \
//            CHAR(c2)  \
//        )             \
//    )
//
//#define INT(i) i,
//#define CHAR(c) char c;
//#define I(e, x) enum e {x};
//#define C(x) x
//#define S(s, args...) struct s {args};
//    A(S)


//#define my_class(name, elems) \
//    name(coord)     \
//    elems(          \
//        elem(x, 0)  \
//        elem(y, 1)  \
//    )
//
//#define class_def(my_class) \
//    x(                      \
//        constructor_args(my_class) \
//        constructor_init(my_class) \
//        class_attributes(my_class) \
//    )
//
//#define name(n) n
//#define elems(e)
//#define x(c) \
//    class name { \
//        name  { \
//        } \
//    };
//
//class_def(my_class(name, elems))

//#define ast_node_def(name, params...) \
//    class name : public ASTNode { \
//    public:                       \
//        explicit name(params) {}  \
//    };
//
//#define AND(nodes...) nodes
//#define NODE(is_list, is_optional, is_abstract, name) node_name
//#define node_name(node_name) \
//    class node_name : public ASTNode {
// \
//                        \
//    };
//
//#undef node_name
//#undef AND
//    ast_node_def(domain)
//}

#endif //EPDDL_MACRO_AST_H
