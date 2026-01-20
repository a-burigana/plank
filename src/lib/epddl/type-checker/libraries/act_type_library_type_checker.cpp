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

#include "type-checker/libraries/act_type_library_type_checker.h"
#include "type-checker/libraries/act_types_type_checker.h"

using namespace epddl;
using namespace epddl::type_checker;

void act_type_library_type_checker::check(const ast::act_type_library_ptr &library, context &context,
                                          error_manager_ptr &err_manager) {
    context.components_names.add_library_name(err_manager, library);

    err_manager->push_error_info(error_manager::get_error_info(
            decl_type::library_decl, library->get_name()->get_token().get_lexeme()));

    for (const auto &item : library->get_items())
        if (std::holds_alternative<ast::action_type_ptr>(item))
            act_types_type_checker::check(std::get<ast::action_type_ptr>(item), context, err_manager);

    err_manager->pop_error_info();
}
