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

#include "../../../include/type-checker/domains/domains_type_checker.h"
#include "../../../include/type-checker/domains/events_type_checker.h"
#include "../../../include/type-checker/domains/actions_type_checker.h"

using namespace epddl;
using namespace epddl::type_checker;

void domains_type_checker::check(const ast::domain_ptr &domain, context &context, const type_ptr &types_tree) {
    context.components_names.set_domain_name(domain);

    for (const auto &item: domain->get_items())
        if (std::holds_alternative<ast::domain_libraries_ptr>(item))
            for (const ast::identifier_ptr &lib_name : std::get<ast::domain_libraries_ptr>(item)->get_libraries())
                context.components_names.assert_declared_library(lib_name);
        else if (std::holds_alternative<ast::event_ptr>(item))
            events_type_checker::check(std::get<ast::event_ptr>(item), context, types_tree);
        else if (std::holds_alternative<ast::action_ptr>(item))
            actions_type_checker::check(std::get<ast::action_ptr>(item), context, types_tree);
}
