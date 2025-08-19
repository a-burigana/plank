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

#ifndef EPDDL_TYPES_TREE_H
#define EPDDL_TYPES_TREE_H

#include "../ast/tokens/tokens_ast.h"
#include <algorithm>
#include <deque>
#include <memory>
#include <list>

namespace epddl::type_checker {
    class types_tree;

    using types_tree_ptr = std::shared_ptr<types_tree>;
    using types_tree_list = std::list<types_tree_ptr>;

    class types_tree {
    public:
        types_tree(std::string type_name, types_tree_ptr parent, bool is_specializable = true) :
                m_type_name{std::move(type_name)},
                m_parent{std::move(parent)},
                m_is_primitive{true},
                m_is_specializable{is_specializable} {
            if (m_parent)
                m_parent->m_children.push_back(std::make_shared<types_tree>(*this));
        }

        types_tree(token_ptr token, types_tree_ptr parent) :
                m_type_name{token->get_lexeme()},
                m_token{std::move(token)},
                m_parent{std::move(parent)},
                m_is_primitive{false},
                m_is_specializable{true} {
            if (m_parent)
                m_parent->m_children.push_back(std::make_shared<types_tree>(*this));
        }

        [[nodiscard]] std::string get_type_name() const {
            return m_type_name;
        }

        [[nodiscard]] token_ptr get_token() const {
            return m_token;
        }

        [[nodiscard]] types_tree_ptr get_parent() const {
            return m_parent;
        }

        [[nodiscard]] types_tree_list get_children() const {
            return m_children;
        }

        [[nodiscard]] bool is_primitive() const {
            return m_is_primitive;
        }

        [[nodiscard]] bool is_specializable() const {
            return m_is_specializable;
        }

        [[nodiscard]] types_tree_ptr find(const std::string &type_name) {
            if (m_type_name == type_name)
                return std::make_shared<types_tree>(*this);

            auto child = m_children.begin();

            while (child != m_children.end())
                if (auto result = (*child++)->find(type_name); result)
                    return result;

            return nullptr;
        }

//        void add_child(types_tree_ptr child) {
//            m_children.push_back(std::move(child));
//        }

        [[nodiscard]] bool has_type(const types_tree &tree) const {
            return m_type_name == tree.get_type_name();
        }

        [[nodiscard]] bool has_either_type(const std::deque<types_tree> &trees) const {
            return std::any_of(trees.begin(), trees.end(), [&](const types_tree &tree) { return has_type(tree); });
        }

        [[nodiscard]] bool is_sub_type_of(const types_tree &tree) const {
            return has_type(tree) or (m_parent and is_sub_type_of(*tree.get_parent()));
        }

        [[nodiscard]] bool is_super_type_of(const types_tree &tree) const {
            return tree.is_sub_type_of(*this);
        }

    private:
        std::string m_type_name;
        token_ptr m_token;
        types_tree_ptr m_parent;
        types_tree_list m_children;
        bool m_is_primitive, m_is_specializable;
    };
}

#endif //EPDDL_TYPES_TREE_H
