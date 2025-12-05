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
#include <algorithm>
#include <memory>
#include <optional>
#include <unordered_map>

#define ROOT_TYPE_NAME ";root"

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

        [[nodiscard]] unsigned long get_type_id(const type_ptr &type) const {
            return get_type_id(type->get_name());
        }

        [[nodiscard]] unsigned long get_types_size() const {
            return m_types_ids.size();
        }

        [[nodiscard]] const type_names_map &get_types_map() const {
            return m_types_map;
        }

        [[nodiscard]] const type_ptr &get_type(const type_id id) const {
            return m_types_map.at(m_types_names[id]);
        }

        [[nodiscard]] const type_ptr &get_type(const std::string &type_name) const {
            return m_types_map.at(type_name);
        }

        [[nodiscard]] const type_ptr &get_parent(const type_ptr &type) const {
            return m_types_map.at(type->get_parent());
        }

        [[nodiscard]] bool is_declared(const ast::identifier_ptr &type) const {
            return m_types_map.find(type->get_token().get_lexeme()) != m_types_map.end();
        }

        void assert_declared_type(const ast::type &type) const {
            std::visit([&](auto &&arg) { assert_declared_type(arg); }, type);
        }

        void assert_declared_type(const ast::identifier_ptr &type) const {
            if (not is_declared(type))
                throw EPDDLException(type->get_info(),
                                     "Use of undeclared type '" + type->get_token().get_lexeme() + "'.");
        }

        void assert_declared_type(const ast::either_type_ptr &type) const {
            for (const ast::identifier_ptr &t: type->get_ids())
                assert_declared_type(t);
        }

        void assert_not_declared_type(const ast::identifier_ptr &type) {
            if (is_declared(type)) {
                const type_ptr &declared_type = m_types_map.at(type->get_token().get_lexeme());
                const auto &position = declared_type->get_position();

                const std::string
                        declared_type_str = declared_type->is_reserved() ? "reserved type" : "type",
                        previous_decl_str = " Previous declaration at " +
                                            std::to_string(position.first) + ":" +
                                            std::to_string(position.second) + ".";

                throw EPDDLException{type->get_info(),
                                     "Redeclaration of " + declared_type_str + " '" +
                                     type->get_token().get_lexeme() + "'." +
                                     (declared_type->is_reserved() ? "" : previous_decl_str)};
            }
        }

        [[nodiscard]] bool is_specializable(const ast::identifier_ptr &type) const {
            assert_declared_type(type);
            return m_types_map.find(type->get_token().get_lexeme()) != m_types_map.end();
        }

        void assert_specializable_type(const ast::identifier_ptr &type) const {
            if (not is_specializable(type))
                throw EPDDLException{type->get_info(), "Specialization of non-specializable type '" +
                                                       type->get_token().get_lexeme() + "'."};
        }

        void add_type_decl(const ast::identifier_ptr &type_id,
                           const std::optional<ast::identifier_ptr> &parent = std::nullopt) {
            assert_not_declared_type(type_id);
            if (parent.has_value()) assert_specializable_type(*parent);

            const std::string &type_name = type_id->get_token().get_lexeme();
            // If no syper type is specified, we assume it's 'object'
            std::string parent_name = parent.has_value() ? (*parent)->get_token().get_lexeme() : "object";

            m_types_names.emplace_back(type_name);
            m_types_ids[type_name] = m_types_names.size() - 1;
            m_types_map[type_name] = std::make_shared<type>(type_id, std::move(parent_name));

            m_types_map[parent_name]->add_child(type_name);
        }

        void add_reserved_type_decl(const std::string &type_name, const std::string &parent_name = ROOT_TYPE_NAME,
                                    bool is_specializable = true) {
            m_types_names.emplace_back(type_name);
            m_types_ids[type_name] = m_types_names.size() - 1;
            m_types_map[type_name] = std::make_shared<type>(type_name, parent_name, true, is_specializable);

            m_types_map[parent_name]->add_child(type_name);
        }

        [[nodiscard]]
        type_ptr find(const type_ptr &type, const std::string &type_name) const {
            if (type->get_name() == type_name)
                return type;

            for (const std::string &child_name : type->get_children())
                if (auto result = find(m_types_map.at(child_name), type_name); result)
                    return result;

            return nullptr;
        }

        [[nodiscard]]
        bool is_compatible_with(const type_ptr &sub_type, const type_ptr &super_type) const {
            return find(super_type, sub_type->get_name()) != nullptr;
        }

        [[nodiscard]]
        bool is_compatible_with(const either_type &type_actual, const either_type &type_formal) const {
            // Let (either ft_1 ft_2 ... ft_m) and (either at_1 at_2 ... at_n) be the types of the formal and
            // actual parameter, respectively. If for all primitive types at_j there exists a primitive type ft_i
            // such that at_j is a subtype of ft_i, then the two either-types are compatible
            return std::all_of(type_actual.begin(), type_actual.end(), [&](const type_id &at) {
                return std::any_of(type_formal.begin(), type_formal.end(), [&](const type_id &ft) {
                    return is_compatible_with(get_type(at), get_type(ft));
                });
            });
        }

        void assert_compatible_decl_type(const ast::type &type, const either_type &given_type, const type_ptr &decl_type) const {
            if (not is_compatible_with(given_type, either_type{get_type_id(decl_type)}))
                std::visit([&](auto &&arg) {
                    throw EPDDLException(arg->get_info(), "Type '" + types_context::to_string_type(given_type) +
                                                          "' is incompatible with expected type '" + decl_type->get_name() + "'.");
                }, type);
        }

//        void build_type_names(const type_ptr &root) {
//            std::function<void(const type_ptr &)> init_id = [&](const type_ptr &type) {
//                m_types_map[type->get_name()] = type;
//                m_types_names.emplace_back(type->get_name());
//                m_types_ids[type->get_name()] = m_types_names.size() - 1;
//
//                for (const type_ptr &child : type->get_children())
//                    init_id(child);
//            };
//
//            init_id(root);
//        }
//
//        void build_parents_map(const type_ptr &root) {
//            std::function<void(const type_ptr &)> init_parent = [&](const type_ptr &type) {
//                for (const type_ptr &child : type->get_children()) {
//                    m_parents_map[child->get_name()] = type;
//                    init_parent(child);
//                }
//            };
//
//            init_parent(root);
//        }

        [[nodiscard]] typed_var_list build_typed_var_list(const ast::formal_param_list &params,
                                                          const either_type &default_type) const {
            typed_var_list types;
            either_type current_type = default_type;

            for (const ast::formal_param &param : params) {
                if (param->get_type().has_value())
                    assert_declared_type(*param->get_type());
            }

            // We visit the list of entities backwards to determine the type of each identifier
            for (auto it = params.rbegin(); it != params.rend(); ++it) {
                const std::string &var_name = (*it)->get_var()->get_token_ptr()->get_lexeme();
                current_type = build_type((*it)->get_type(), current_type);

                types.emplace_front(var_name, current_type);
            }

            return types;
        }

        [[nodiscard]] either_type build_type(const std::optional<ast::type> &entity_decl_type,
                                             const either_type &default_type) const {
            either_type entity_type;

            if (entity_decl_type.has_value()) {
                if (std::holds_alternative<ast::identifier_ptr>(*entity_decl_type)) {
                    const auto &id = std::get<ast::identifier_ptr>(*entity_decl_type);
                    entity_type = either_type{get_type_id(id->get_token().get_lexeme())};
                } else if (std::holds_alternative<ast::either_type_ptr>(*entity_decl_type)) {
                    const ast::identifier_list &either_type_list =
                            std::get<ast::either_type_ptr>(*entity_decl_type)->get_ids();

                    for (const ast::identifier_ptr &id : either_type_list) {
                        bool good = std::all_of(entity_type.begin(), entity_type.end(), [&](const type_id &t) {
                            return not find(get_type(t), id->get_token().get_lexeme());
                        });

                        // todo: check this
//                        if (good)       // We make sure 'entity_type' does not already contain a super type of the new type
//                            entity_type.push_back(find(types_tree, id->get_token().get_lexeme()));
                    }
                }
            } else
                entity_type = default_type;

            return entity_type;
        }

        [[nodiscard]] bool has_either_type(const type_ptr &type, const either_type &types) const {
            return std::any_of(types.begin(), types.end(), [&](const type_id &t) {
                return type->has_type(get_type(t));
            });
        }

        [[nodiscard]] std::string to_string_type(const type_id &t) const {
            return get_type(t)->get_name();
        }

        [[nodiscard]] std::string to_string_type(const either_type &type) const {
            if (type.size() == 1) return to_string_type(type.back());

            std::string type_str = "(either";
            for (const type_id t : type) type_str.append(" " + to_string_type(t));
            return type_str + ")";
        }

        void throw_incompatible_types(const either_type &type_formal, const either_type &type_actual, const ast::term& term) const {
            std::visit([&](auto &&arg) {
                throw EPDDLException(arg->get_info(), "Type error. Expected term with type '" +
                                                      types_context::to_string_type(type_formal) +
                                                      "', found '" + arg->get_token().get_lexeme() + "' with type '" +
                                                      types_context::to_string_type(type_actual) + "'.");
            }, term);
        }

    private:
        name_vector m_types_names;
        name_id_map m_types_ids;
        type_names_map m_types_map;
    };
}

#endif //EPDDL_TYPES_CONTEXT_H
