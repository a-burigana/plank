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
#include <deque>
#include <iostream>
#include <memory>
#include <list>
#include <string>
#include <unordered_map>

namespace epddl::type_checker {
    class type;

    using type_ptr         = std::shared_ptr<type>;
    using type_id          = unsigned long;
    using either_type      = std::list<type_id>;
    using either_type_list = std::list<either_type>;
    using type_names_map   = std::unordered_map<std::string, type_ptr>;

    class type {
    public:
        explicit type(std::string name, std::string parent = "", bool is_reserved = false, bool is_specializable = true) :
                m_name{std::move(name)},
                m_parent{std::move(parent)},
                m_is_reserved{is_reserved},
                m_is_specializable{is_specializable},
                m_row{0},
                m_col{0} {}

        explicit type(const ast::identifier_ptr &id, std::string parent = "") :
                m_name{id->get_token().get_lexeme()},
                m_row{id->get_token().get_row()},
                m_col{id->get_token().get_col()},
                m_parent{std::move(parent)},
                m_is_reserved{false},
                m_is_specializable{true} {}

        type(const type&) = default;
        type& operator=(const type&) = default;

        type(type&&) = default;
        type& operator=(type&&) = default;

        [[nodiscard]] std::string get_name() const {
            return m_name;
        }

        [[nodiscard]] auto get_position() const {
            return std::pair{m_row, m_col};
        }

        [[nodiscard]] std::string get_parent() const {
            return m_parent;
        }

        [[nodiscard]] auto get_children() const {
            return m_children;
        }

        [[nodiscard]] bool is_reserved() const {
            return m_is_reserved;
        }

        [[nodiscard]] bool is_specializable() const {
            return m_is_specializable;
        }

        void add_child(const std::string &child) {
            m_children.push_back(child);
        }

        [[nodiscard]] bool has_type(const type_ptr &tree) const {
            return m_name == tree->get_name();
        }

        bool operator==(const type &rhs) const {
            return get_name() == rhs.get_name();
        }

        bool operator!=(const type &rhs) const {
            return !(rhs == *this);
        }

    private:
        std::string m_name, m_parent;
        std::list<std::string> m_children;
        unsigned long m_row, m_col;
        bool m_is_reserved, m_is_specializable;
    };
}

#endif //EPDDL_TYPE_H
