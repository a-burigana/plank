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

#ifndef EPDDL_SCOPE_H
#define EPDDL_SCOPE_H

#include "context_types.h"

namespace epddl::type_checker {
    class scope {
    public:
        scope() = default;

        [[nodiscard]] const type_map &get_type_map() const { return m_name_map; }

        [[nodiscard]] bool is_declared(const ast::term &term) const {
            return std::visit([&](auto &&arg) -> bool {
                return m_name_map.find(arg->get_token().get_lexeme()) != m_name_map.end();
            }, term);
        }

        [[nodiscard]] bool has_type(const ast::term &term, const either_type &type) const {
            return std::visit([&](auto &&arg) -> bool {
                const either_type &term_type_list = m_name_map.at(arg->get_token().get_lexeme());
                return type::is_compatible_with(term_type_list, type);
            }, term);
        }

        [[nodiscard]] bool has_type(const ast::term &term, const type_ptr &type) const {
            return has_type(term, either_type{type});
        }

        [[nodiscard]] either_type get_type(const ast::term &term) const {
            return std::visit([&](auto &&arg) {
                const auto &term_type_list = m_name_map.find(arg->get_token().get_lexeme());
                return term_type_list == m_name_map.end() ? either_type{} : m_name_map.at(arg->get_token().get_lexeme());
            }, term);
        }

        [[nodiscard]] std::optional<ast::term> get_term(const std::string &name) const {
            if (const auto it = m_entities_map.find(name); it != m_entities_map.end())
                return it->second;

            return std::nullopt;
        }

        void add_decl(const ast::term &term, const either_type &types) {
            std::visit([&](auto &&arg) {
                m_name_map[arg->get_token().get_lexeme()] = types;
                m_entities_map[arg->get_token().get_lexeme()] = term;
            }, term);
        }

        [[nodiscard]] const ast::term& get_decl(const std::string &name) const {
            return m_entities_map.at(name);
        }

    private:
        type_map m_name_map;
        ast_node_map<ast::term> m_entities_map;
    };
}

#endif //EPDDL_SCOPE_H
