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

#ifndef EPDDL_TYPE_H
#define EPDDL_TYPE_H

#include "../ast/tokens/tokens_ast.h"
#include <algorithm>
#include <deque>
#include <memory>
#include <list>

namespace epddl::type_checker {
    class type;

    using type_ptr = std::shared_ptr<type>;
    using type_list = std::list<type_ptr>;

    class type {
    public:
        type(std::string name, type_ptr parent, bool is_reserved = false, bool is_specializable = true) :
                m_name{std::move(name)},
                m_parent{std::move(parent)},
                m_is_reserved{is_reserved},
                m_is_specializable{is_specializable} {
            if (m_parent)
                m_parent->m_children.push_back(std::make_shared<type>(*this));
        }

        type(ast::identifier_ptr id, type_ptr parent) :
                m_name{id->get_token().get_lexeme()},
                m_id{std::move(id)},
                m_parent{std::move(parent)},
                m_is_reserved{false},
                m_is_specializable{true} {
            if (m_parent)
                m_parent->m_children.push_back(std::make_shared<type>(*this));
        }

        [[nodiscard]] std::string get_name() const {
            return m_name;
        }

        [[nodiscard]] ast::identifier_ptr get_identifier() const {
            return m_id;
        }

        [[nodiscard]] type_ptr get_parent() const {
            return m_parent;
        }

        [[nodiscard]] type_list get_children() const {
            return m_children;
        }

        [[nodiscard]] bool is_reserved() const {
            return m_is_reserved;
        }

        [[nodiscard]] bool is_specializable() const {
            return m_is_specializable;
        }

        [[nodiscard]] type_ptr find(const std::string &type_name) const {
            if (m_name == type_name)
                return std::make_shared<type>(*this);

            auto child = m_children.begin();

            while (child != m_children.end())
                if (auto result = (*child++)->find(type_name); result)
                    return result;

            return nullptr;
        }

//        void add_child(types_tree_ptr child) {
//            m_children.push_back(std::move(child));
//        }

        [[nodiscard]] bool has_type(const type_ptr &tree) const {
            return m_name == tree->get_name();
        }

        [[nodiscard]] bool has_either_type(const type_list &trees) const {
            return std::any_of(trees.begin(), trees.end(), [&](const type_ptr &tree) { return has_type(tree); });
        }

        [[nodiscard]] bool is_sub_type_of(const type_ptr &tree) const {
            return has_type(tree) or (m_parent and is_sub_type_of(tree->get_parent()));
        }

        [[nodiscard]] bool is_super_type_of(const type_ptr &tree) const {
            return tree->is_sub_type_of(std::make_shared<type>(*this));
        }

    private:
        std::string m_name;
        ast::identifier_ptr m_id;
        type_ptr m_parent;
        type_list m_children;
        bool m_is_reserved, m_is_specializable;
    };
}

#endif //EPDDL_TYPE_H
