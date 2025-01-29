#ifndef EPDDL_AST_NODE_H
#define EPDDL_AST_NODE_H

#include <memory>

namespace epddl::ast {
    class ast_node;
    using ast_node_ptr = std::unique_ptr<ast_node>;

    class ast_node {
    public:
        explicit ast_node() :
                m_parent{} {}

        ast_node(const ast_node&) = delete;
        ast_node& operator=(const ast_node&) = delete;

        ast_node(ast_node&&) = default;
        ast_node& operator=(ast_node&&) = default;

        virtual ~ast_node() = default;

        void set_parent(ast_node_ptr parent) {
            if (!m_parent) {
                m_parent = std::move(parent);
            }
        }

    private:
        ast_node_ptr m_parent;
    };
}

#endif //EPDDL_AST_NODE_H
