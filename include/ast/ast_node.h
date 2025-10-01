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
#include <string>
#include <unordered_set>
#include "../lexer/tokens/token_types.h"

namespace epddl::ast {
    class ast_node;
    using ast_node_ptr = std::shared_ptr<ast_node>;
    using string_set = std::unordered_set<std::string>;

    struct info {
        std::string m_path;
        unsigned long m_row, m_col;
        string_set m_requirements;

        void add_requirement(std::string req) {
            m_requirements.emplace(std::move(req));
        }
    };

    class ast_node {
    public:
        explicit ast_node(info info) :
                m_info{std::move(info)} {}

        [[nodiscard]] const info &get_info() const { return m_info ; }
        [[nodiscard]] const std::string &get_path() const { return m_info.m_path ; }
        [[nodiscard]] unsigned long get_row() const { return m_info.m_row ; }
        [[nodiscard]] unsigned long get_col() const { return m_info.m_col ; }
        [[nodiscard]] const string_set &get_requirements() const { return m_info.m_requirements ; }

        void add_requirement(std::string req) {
            m_info.add_requirement(std::move(req));
        }

//        void set_parent(ast_node_ptr parent) {
//            if (not m_parent)
//                m_parent = std::move(parent);
//        }

    private:
//        ast_node_ptr m_parent;
        info m_info;
    };
}

#endif //EPDDL_AST_NODE_H
