// MIT License
//
// Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
