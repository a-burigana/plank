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

#ifndef PLANK_SCOPE_H
#define PLANK_SCOPE_H

#include "context_types.h"
#include "types_context.h"

namespace epddl::type_checker {
    class scope {
    public:
        scope() = default;

        explicit scope(size_t ent_offset, size_t var_offset) :
                m_entities_offset{ent_offset},
                m_variables_offset{var_offset},
                m_entities_no{ent_offset},
                m_variables_no{var_offset} {}

        [[nodiscard]] const type_map &get_type_map() const {
            return m_type_map;
        }

        [[nodiscard]] bool is_declared(const ast::term &term) const {
            return std::visit([&](auto &&arg) -> bool {
                return is_declared(arg->get_token().get_lexeme());
            }, term);
        }

        [[nodiscard]] bool is_declared(const std::string &name) const {
            return m_type_map.find(name) != m_type_map.end();
        }

        [[nodiscard]] bool has_type(const types_context &types_context, const ast::term &term,
                                    const either_type &type) const {
            return std::visit([&](auto &&arg) -> bool {
                const either_type &term_type_list = m_type_map.at(arg->get_token().get_lexeme());
                return types_context.is_compatible_with(term_type_list, type);
            }, term);
        }

        [[nodiscard]] bool has_type(const types_context &types_context,
                                    const ast::term &term, const type_ptr &type) const {
            return has_type(types_context, term, either_type{types_context.get_type_id(type)});
        }

        [[nodiscard]] either_type get_type(const std::string &name) const {
            const auto &term_type_list = m_type_map.find(name);
            return term_type_list == m_type_map.end() ? either_type{} : m_type_map.at(name);
        }

        [[nodiscard]] either_type get_type(const ast::term &term) const {
            return std::visit([&](auto &&arg) {
                const auto &term_type_list = m_type_map.find(arg->get_token().get_lexeme());
                return term_type_list == m_type_map.end() ? either_type{} : m_type_map.at(arg->get_token().get_lexeme());
            }, term);
        }

        [[nodiscard]] std::optional<ast::term> get_term(const std::string &name) const {
            if (const auto it = m_entities_map.find(name); it != m_entities_map.end())
                return it->second;

            if (const auto it = m_variables_map.find(name); it != m_variables_map.end())
                return it->second;

            return std::nullopt;
        }

//        void add_term_decl(const ast::term &term, const either_type &type, bool rename_variables = false) {
//            std::visit([&](auto &&arg) {
//                add_decl(arg, type, rename_variables);
//            }, term);
//        }

        void add_id_decl(const ast::term &term, const either_type &type) {
            std::visit([&](auto &&arg) {
                const std::string &name = arg->get_token_ptr()->get_lexeme();

                m_type_map[name] = type;
                m_entities_map[name] = arg;
                m_entities_names.push_back(name);
                m_entities_ids[name] = m_entities_names.size()-1;
                ++m_entities_no;
            }, term);
        }

        void add_var_decl(const ast::variable_ptr &var, const either_type &type, bool rename_variables = false) {
            const std::string &name = rename_variables
                    ? scope::get_fresh_variable_name(var->get_token().get_lexeme())
                    : var->get_token_ptr()->get_lexeme();

            m_type_map[name] = type;
            m_variables_map[name] = var;
            m_variables_names.push_back(name);
            m_variables_ids[name] = m_variables_names.size()-1;
            ++m_variables_no;
        }

        [[nodiscard]] const bit_deque &get_entities_with_type(const types_context &types_context,
                                                              const std::string &type) const {
            return m_type_entity_sets[types_context.get_type_id(type)];
        }

        [[nodiscard]] const bit_deque &get_entities_with_type(const types_context &types_context,
                                                              const type_id type) const {
            return m_type_entity_sets[type];
        }

        [[nodiscard]] const bit_deque_vector &get_entities_with_type_sets() const {
            return m_type_entity_sets;
        }

        void build_typed_entities_sets(const types_context &types_context, const bit_deque_vector &previous = {}) {
            if (not previous.empty()) {
                m_type_entity_sets = previous;

                for (unsigned long i = 0; i < types_context.get_types_size(); ++i)
                    m_type_entity_sets[i].resize(m_entities_offset + m_entities_names.size());
            } else
                for (unsigned long i = 0; i < types_context.get_types_size(); ++i)
                    m_type_entity_sets.emplace_back(m_entities_names.size());

            // Function 'init_entities' adds the given entity id to the bit_deque corresponding to the given type_ptr
            // and recursively adds the entity to all super types of 'type'
            std::function<void(const type_ptr &, unsigned long)>
                    init_entities = [&](const type_ptr &type, unsigned long e_id) {
                unsigned long type_id = types_context.get_type_id(type->get_name());
                m_type_entity_sets[type_id].push_back(e_id);

                if (types_context.get_parent(type)->get_name() != ROOT_TYPE_NAME)
                    init_entities(types_context.get_parent(type), e_id);
            };

            for (const std::string &name : m_entities_names) {
                const type_ptr &type = types_context.get_type(m_type_map.at(name).front());         // types has always size 1 here
                init_entities(type, get_entity_id(name));
            }

//            for (const auto &[name, types] : m_type_map) {
//                const type_ptr &type = types_context.get_type(types.front());       // types has always size 1 here
//                init_entities(type, get_entity_id(name));
//            }
        }

        [[nodiscard]] unsigned long get_entities_no() const {
            return m_entities_no;
        }

        [[nodiscard]] unsigned long get_variables_no() const {
            return m_variables_no;
        }

        [[nodiscard]] const ast::term& get_entity_decl(const std::string &name) const {
            return m_entities_map.at(name);
        }

        [[nodiscard]] const ast::variable_ptr& get_variable_decl(const std::string &name) const {
            return m_variables_map.at(name);
        }

        [[nodiscard]] const std::string &get_entity_name(unsigned long id) const {
            assert(id < m_entities_no);
            return m_entities_names[id - m_entities_offset];
        }

        [[nodiscard]] const std::string &get_variable_name(unsigned long id) const {
            assert(id < m_variables_no);
            return m_variables_names[id - m_variables_offset];
        }

        [[nodiscard]] unsigned long get_entity_id(const std::string &name) const {
            return m_entities_offset + m_entities_ids.at(name);
        }

        [[nodiscard]] unsigned long get_variable_id(const std::string &name) const {
            return m_variables_offset + m_variables_ids.at(name);
        }

        static std::string get_fresh_variable_name(const std::string &name) {
            return ";" + name;
        }

        [[nodiscard]] unsigned long get_entities_offset() const {
            return m_entities_offset;
        }

        [[nodiscard]] unsigned long get_next_entities_offset() const {
            return m_entities_offset + m_entities_names.size();
        }

        [[nodiscard]] unsigned long get_variables_offset() const {
            return m_variables_offset;
        }

        [[nodiscard]] unsigned long get_next_variables_offset() const {
            return m_variables_offset + m_variables_names.size();
        }

    private:
        type_map m_type_map;
        name_vector m_entities_names, m_variables_names;
        name_id_map m_entities_ids, m_variables_ids;
        bit_deque_vector m_type_entity_sets;
        size_t m_entities_offset, m_variables_offset, m_entities_no, m_variables_no;

        ast_node_map<ast::term> m_entities_map;
        ast_node_map<ast::variable_ptr> m_variables_map;
    };
}

#endif //PLANK_SCOPE_H
