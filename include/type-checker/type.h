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
#include "../error-manager/epddl_exception.h"
#include <algorithm>
#include <deque>
#include <memory>
#include <list>

namespace epddl::type_checker {
    class type;

    using type_ptr         = std::shared_ptr<type>;
    using either_type      = std::list<type_ptr>;
    using either_type_list = std::list<either_type>;

    class type {
    public:
        type(std::string name, type_ptr parent, bool is_reserved = false, bool is_specializable = true) :
                m_name{std::move(name)},
                m_parent{std::move(parent)},
                m_is_reserved{is_reserved},
                m_is_specializable{is_specializable} {}

        type(ast::identifier_ptr id, type_ptr parent) :
                m_name{id->get_token().get_lexeme()},
                m_id{std::move(id)},
                m_parent{std::move(parent)},
                m_is_reserved{false},
                m_is_specializable{true} {}

        type(const type&) = delete;
        type& operator=(const type&) = delete;

        [[nodiscard]] std::string get_name() const {
            return m_name;
        }

        [[nodiscard]] ast::identifier_ptr get_identifier() const {
            return m_id;
        }

        [[nodiscard]] type_ptr get_parent() const {
            return m_parent;
        }

        [[nodiscard]] either_type get_children() const {
            return m_children;
        }

        [[nodiscard]] bool is_reserved() const {
            return m_is_reserved;
        }

        [[nodiscard]] bool is_specializable() const {
            return m_is_specializable;
        }

        void add_child(type_ptr child) {
            m_children.push_back(std::move(child));
        }

//        void add_child(types_tree_ptr child) {
//            m_children.push_back(std::move(child));
//        }

        [[nodiscard]] bool has_type(const type_ptr &tree) const {
            return m_name == tree->get_name();
        }

        [[nodiscard]] bool has_either_type(const either_type &trees) const {
            return std::any_of(trees.begin(), trees.end(), [&](const type_ptr &tree) { return has_type(tree); });
        }

        [[nodiscard]] bool is_compatible_with(const type_ptr &tree) const {
            return has_type(tree) or (m_parent and m_parent->is_compatible_with(tree));
        }

    private:
        std::string m_name;
        ast::identifier_ptr m_id;
        type_ptr m_parent;
        either_type m_children;
        bool m_is_reserved, m_is_specializable;
    };

    class type_utils {
    public:
        [[nodiscard]] static type_ptr find(const type_ptr &type, const std::string &type_name) {
            if (type->get_name() == type_name)
                return type;

            for (const type_ptr &child : type->get_children())
                if (auto result = type_utils::find(child, type_name); result)
                    return result;

            return nullptr;
        }

        [[nodiscard]] static type_ptr find(const type_ptr &type, const ast::identifier_ptr &id) {
            return type_utils::find(type, id->get_token().get_lexeme());

//            if (type_ptr result = find(type->get_token().get_lexeme()); result)
//                return result;
//
//            throw EPDDLException{std::string{""},
//                                 type->get_token().get_row(),
//                                 type->get_token().get_col(),
//                                 std::string{"Use of undeclared type '" + type->get_token().get_lexeme() + "'."}};
        }
    };
}

#endif //EPDDL_TYPE_H
