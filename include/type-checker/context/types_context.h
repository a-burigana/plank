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

#ifndef EPDDL_TYPES_CONTEXT_H
#define EPDDL_TYPES_CONTEXT_H

#include "context_types.h"
#include "context_utils.h"

namespace epddl::type_checker {
    class types_context {
    public:
        types_context() = default;

        [[nodiscard]] const std::string &get_type_name(unsigned long id) const {
            return m_types_names[id];
        }

        [[nodiscard]] unsigned long get_type_id(const std::string &name) const {
            return m_types_ids.at(name);
        }

        [[nodiscard]] unsigned long get_types_size() const {
            return m_types_ids.size();
        }

        static void assert_declared_type(const type_ptr &types_tree, const ast::type &type) {
            std::visit([&](auto && arg) { types_context::assert_declared_type(types_tree, arg); }, type);
        }

        static void assert_declared_type(const type_ptr &types_tree, const ast::identifier_ptr &type) {
            if (not type_utils::find(types_tree, type))
                throw EPDDLException(type->get_info(), "Use of undeclared type '" + type->get_token().get_lexeme() + "'.");
        }

        static void assert_declared_type(const type_ptr &types_tree, const ast::either_type_ptr &type) {
            for (const ast::identifier_ptr &t : type->get_ids())
                types_context::assert_declared_type(types_tree, t);
        }

        static void assert_compatible_decl_type(const ast::type &type, const either_type &given_type, const type_ptr &decl_type) {
            if (not type::is_compatible_with(given_type, either_type{decl_type}))
                std::visit([&](auto &&arg) {
                    throw EPDDLException(arg->get_info(), "Type '" + type::to_string_type(given_type) +
                                                          "' is incompatible with expected type '" + decl_type->get_name() + "'.");
                }, type);
        }

        void build_type_names(const type_ptr &root) {
            std::function<void(const type_ptr &)> init_id = [&](const type_ptr &type) {
                m_types_names.emplace_back(type->get_name());
                m_types_ids[type->get_name()] = m_types_names.size() - 1;

                for (const type_ptr &child : type->get_children())
                    init_id(child);
            };

            init_id(root);
        }

        static typed_var_list build_typed_var_list(const ast::formal_param_list &params, const type_ptr &types_tree,
                                                   const either_type &default_type) {
            typed_var_list types;
            either_type current_type = default_type;

            for (const ast::formal_param &param : params) {
                if (param->get_type().has_value())
                    types_context::assert_declared_type(types_tree, *param->get_type());
            }

            // We visit the list of entities backwards to determine the type of each identifier
            for (auto it = params.rbegin(); it != params.rend(); ++it) {
                current_type = build_type((*it)->get_type(), types_tree, current_type);
                types.emplace_front((*it)->get_var()->get_token().get_lexeme(), current_type);
            }

            return types;
        }

        static either_type build_type(const std::optional<ast::type> &entity_decl_type, const type_ptr &types_tree,
                                      const either_type &default_type) {
            either_type entity_type;

            if (entity_decl_type.has_value()) {
                if (std::holds_alternative<ast::identifier_ptr>(*entity_decl_type))
                    entity_type = either_type{type_utils::find(types_tree, std::get<ast::identifier_ptr>(*entity_decl_type))};
                else if (std::holds_alternative<ast::either_type_ptr>(*entity_decl_type)) {
                    const ast::identifier_list &either_type_list =
                            std::get<ast::either_type_ptr>(*entity_decl_type)->get_ids();

                    for (const ast::identifier_ptr &id : either_type_list) {
                        bool good = std::all_of(entity_type.begin(), entity_type.end(), [&](const type_ptr &type) {
                            return not type_utils::find(type, id);
                        });

                        if (good)       // We make sure 'entity_type' does not already contain a super type of the new type
                            entity_type.push_back(type_utils::find(types_tree, id));
                    }
                }
            } else
                entity_type = default_type;

            return entity_type;
        }

    private:
        name_vector m_types_names;
        name_id_map m_types_ids;
    };
}

#endif //EPDDL_TYPES_CONTEXT_H
