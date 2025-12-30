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

#ifndef PLANK_CONTEXT_UTILS_H
#define PLANK_CONTEXT_UTILS_H

#include "context_types.h"
#include "entities_context.h"
#include <deque>

namespace epddl::type_checker {
    class context_utils {
    public:
        [[nodiscard]] static bool is_declared(const ast::identifier_ptr &id, const signature_map &signatures) {
            return context_utils::is_declared(id->get_token().get_lexeme(), signatures);
        }

        [[nodiscard]] static bool is_declared(const std::string &name, const signature_map &signatures) {
            return signatures.find(name) != signatures.end();
        }

        static void check_signature(const types_context &types_context, const entities_context &entities_context,
                                    error_manager_ptr &err_manager, const signature_map &signatures,
                                    const ast::identifier_ptr &id, const ast::term_list &terms,
                                    const std::string &decl_str) {
            const auto &types = signatures.at(id->get_token().get_lexeme());

            if (types.size() != terms.size())
                context_utils::throw_arguments_number_error(err_manager, id, types, terms, decl_str);

            for (auto [typed_var, term] = std::tuple{types.begin(), terms.begin()};
                 typed_var != types.end(); ++typed_var, ++term) {
                // We want to check that the type of our current actual parameter is compatible with that of
                // our current formal parameter

                // Type of the formal parameter declared in the predicate definition
                const either_type &param_type = typed_var->type;
                // Type of the actual parameter passed to the predicate
                const either_type term_type = entities_context.get_type(err_manager, *term);

                // We check that the type of the actual parameter is compatible with that of the formal parameter
                if (not types_context.is_compatible_with(term_type, param_type))
                    err_manager->throw_error(
                            error_type::incompatible_term_type,
                            std::visit([](auto &&arg) { return arg->get_token_ptr(); }, *term),
                            {types_context.to_string_type(term_type), types_context.to_string_type(param_type)});
            }
        }

        template<typename T>
        static void throw_arguments_number_error(error_manager_ptr &err_manager, const ast::identifier_ptr &id,
                                                 const typed_var_list &expected_list, const std::list<T> &found_list,
                                                 const std::string &decl_str) {
            std::string many_few = expected_list.size() < found_list.size() ? "many" : "few";
            err_manager->throw_error(error_type::arguments_number_mismatch, id->get_token_ptr(),
                                     {many_few, decl_str, std::to_string(expected_list.size()),
                                      std::to_string(found_list.size())});
        }
    };
}

#endif //PLANK_CONTEXT_UTILS_H
