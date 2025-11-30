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

#ifndef EPDDL_CONTEXT_UTILS_H
#define EPDDL_CONTEXT_UTILS_H

#include "context_types.h"
#include "scope.h"
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

        [[nodiscard]] static bool is_declared(const std::deque<scope> &scopes, const ast::term &term) {
            return std::any_of(scopes.begin(), scopes.end(),
                               [&](const scope &scope) { return scope.is_declared(term); });
        }

        static void assert_declared(const std::deque<scope> &scopes, const ast::term &term) {
            if (context_utils::is_declared(scopes, term)) return;

            std::visit([&](auto &&arg) {
                using token_type = typename std::remove_reference_t<decltype(*arg)>::token_type;
                throw EPDDLException(arg->get_info(), "Use of undeclared " + std::string{token_type::name} +
                                                      " '" + arg->get_token().get_lexeme() + "'.");
            }, term);
        }

        [[nodiscard]] static either_type get_type(const std::deque<scope> &scopes, const ast::term &term) {
            context_utils::assert_declared(scopes, term);

            for (const auto &scope : scopes)
                if (const either_type &type = scope.get_type(term); not type.empty())
                    return type;

            return either_type{};
        }

        static void check_signature(const signature_map &signatures, const ast::identifier_ptr &id,
                                    const ast::term_list &terms, const std::deque<scope> &scopes,
                                    const std::string &decl_str) {
            const auto &types = signatures.at(id->get_token().get_lexeme());

            if (types.size() != terms.size())
                context_utils::throw_arguments_number_error(id, types, terms, decl_str);

            for (auto [type, term] = std::tuple{types.begin(), terms.begin()}; type != types.end(); ++type, ++term) {
                // We want to check that the type of our current actual parameter is compatible with that of
                // our current formal parameter
                const either_type &param_type = type->second;                           // Type of the formal parameter declared in the predicate definition
                const either_type term_type = context_utils::get_type(scopes, *term);   // Type of the actual parameter passed to the predicate

                // We check that the type of the actual parameter is compatible with that of the formal parameter
                if (not type::is_compatible_with(term_type, param_type))
                    type::throw_incompatible_types(param_type, term_type, *term);
            }
        }

        template<typename T, typename U>
        static void throw_arguments_number_error(const ast::identifier_ptr &id, const std::list<T> &expected_list,
                                                 const std::list<U> &found_list, const std::string &decl_str) {
            std::string many_few = expected_list.size() < found_list.size() ? "many" : "few";

            throw EPDDLException{std::string{""}, id->get_token().get_row(), id->get_token().get_col(),
                                 std::string{"Too " + many_few + " arguments for " + decl_str + " '" +
                                             id->get_token().get_lexeme() + "'. Expected " +
                                             std::to_string(expected_list.size()) + ", found " +
                                             std::to_string(found_list.size()) + "."}};
        }
    };
}

#endif //EPDDL_CONTEXT_UTILS_H
