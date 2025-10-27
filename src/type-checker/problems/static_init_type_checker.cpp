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

#include "../../../include/type-checker/problems/static_init_type_checker.h"
#include "../../../include/type-checker/common/formulas_type_checker.h"

using namespace epddl;
using namespace epddl::type_checker;

void static_init_type_checker::check(const ast::static_init_ptr &init, context &context, const type_ptr &types_tree) {
    auto check_elem = formulas_type_checker::check_function_t<ast::predicate_ptr>(
            [&] (const ast::predicate_ptr &p, class context &context, const type_ptr &types_tree) {
                context.check_predicate_signature(p->get_id(), p->get_terms());
                context.assert_static_predicate(p->get_id());
            });

    formulas_type_checker::check_list(init->get_predicates(), check_elem, context, types_tree);
}

