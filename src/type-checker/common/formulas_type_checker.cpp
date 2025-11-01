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

#include "../../../include/type-checker/common/formulas_type_checker.h"

using namespace epddl;
using namespace epddl::type_checker;

void formulas_type_checker::check_formula(const ast::formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
    std::visit([&](auto &&arg) {
        check_formula(arg, context, types_tree, assert_static);
    }, f);
}

void formulas_type_checker::check_formula(const ast::true_formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
    return;
}

void formulas_type_checker::check_formula(const ast::false_formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
    return;
}

void formulas_type_checker::check_formula(const ast::predicate_formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
    const ast::predicate_ptr &pred = f->get_predicate();
    context.check_predicate_signature(pred->get_id(), pred->get_terms());

    if (assert_static)
        context.assert_static_predicate(f->get_predicate()->get_id());
}

void formulas_type_checker::check_formula(const ast::eq_formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
    context.assert_declared(f->get_first_term());
    context.assert_declared(f->get_second_term());
}

void formulas_type_checker::check_formula(const ast::neq_formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
    context.assert_declared(f->get_first_term());
    context.assert_declared(f->get_second_term());
}

//void formulas_type_checker::check_formula(const ast::in_formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
//    context.assert_declared(f->get_term());
//    check_list(f->get_list(), context, types_tree);
//}

void formulas_type_checker::check_formula(const ast::not_formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
    check_formula(f->get_formula(), context, types_tree, assert_static);
}

void formulas_type_checker::check_formula(const ast::and_formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
    for (const auto &f_ : f->get_formulas())
        check_formula(f_, context, types_tree, assert_static);
}

void formulas_type_checker::check_formula(const ast::or_formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
    for (const auto &f_ : f->get_formulas())
        check_formula(f_, context, types_tree, assert_static);
}

void formulas_type_checker::check_formula(const ast::imply_formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
    check_formula(f->get_first_formula(), context, types_tree, assert_static);
    check_formula(f->get_second_formula(), context, types_tree, assert_static);
}

void formulas_type_checker::check_formula(const ast::box_formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
    check_modality_index(f->get_modality()->get_modality_index(), context, types_tree);
    check_formula(f->get_formula(), context, types_tree, assert_static);
}

void formulas_type_checker::check_formula(const ast::diamond_formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
    check_modality_index(f->get_modality()->get_modality_index(), context, types_tree);
    check_formula(f->get_formula(), context, types_tree, assert_static);
}

void formulas_type_checker::check_formula(const ast::forall_formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
    context.push();
    check_list_comprehension(f->get_list_compr(), context, types_tree, type_utils::find(types_tree, "object"));
    check_formula(f->get_formula(), context, types_tree, assert_static);
    context.pop();
}

void formulas_type_checker::check_formula(const ast::exists_formula_ptr &f, context &context, const type_ptr &types_tree, bool assert_static) {
    context.push();
    check_list_comprehension(f->get_list_compr(), context, types_tree, type_utils::find(types_tree, "object"));
    check_formula(f->get_formula(), context, types_tree, assert_static);
    context.pop();
}

void formulas_type_checker::check_list_comprehension(const ast::list_comprehension_ptr &list_compr,
                                                   context &context, const type_ptr &types_tree,
                                                   const type_ptr &default_type) {
    context.add_decl_list(list_compr->get_formal_params(), default_type, types_tree);

    if (list_compr->get_condition().has_value())
        check_formula(*list_compr->get_condition(), context, types_tree, true);
}

void formulas_type_checker::check_list(const ast::list<ast::simple_agent_group_ptr> &list, context &context,
                                       const type_ptr &types_tree, const std::optional<type_ptr> &elem_type) {
    auto check_elem = formulas_type_checker::check_function_t<ast::simple_agent_group_ptr>(
            [&] (const ast::simple_agent_group_ptr &group, class context &context, const type_ptr &types_tree) {
                if (elem_type.has_value())
                    for (const ast::term &term : group->get_terms())
                        context.check_type(term, *elem_type);
                else
                    context.assert_declared(group->get_terms());
            });

    formulas_type_checker::check_list(list, check_elem, context, types_tree, type_utils::find(types_tree, "object"));

////    if (std::holds_alternative<ast::list_name_ptr>(list)) {
////        const type_ptr &agent_group = type_utils::find(types_tree, ";agent-group");
////        context.check_type(std::get<ast::list_name_ptr>(list)->get_name(), agent_group);
////    } else
//    if (std::holds_alternative<ast::simple_agent_group_ptr>(list)) {
//        if (elem_type.has_value())
//            for (const ast::term &term : std::get<ast::simple_agent_group_ptr>(list)->get_terms())
//                context.check_type(term, *elem_type);
//        else
//            context.assert_declared(std::get<ast::simple_agent_group_ptr>(list)->get_terms());
//    } else if (std::holds_alternative<ast::and_agent_group_ptr>(list))
//        for (const ast::agent_group_ptr &l : std::get<ast::and_agent_group_ptr>(list)->get_term_lists())
//            check_list(l, context, types_tree);
//    else if (std::holds_alternative<ast::forall_agent_group_ptr>(list)) {
//        context.push();
//        check_list_comprehension(std::get<ast::forall_agent_group_ptr>(list)->get_list_compr(), context, types_tree);
//        check_list(std::get<ast::forall_agent_group_ptr>(list)->get_terms(), context, types_tree);
//        context.pop();
//    }
}

void formulas_type_checker::check_modality_index(const ast::modality_index_ptr &index, context &context,
                                               const type_ptr &types_tree) {
    const type_ptr &agent = type_utils::find(types_tree, "agent");

    if (std::holds_alternative<ast::term>(index))
        context.check_type(std::get<ast::term>(index), agent);
    else if (std::holds_alternative<ast::list<ast::simple_agent_group_ptr>>(index))
        check_list(std::get<ast::list<ast::simple_agent_group_ptr>>(index), context, types_tree, agent);
}

void formulas_type_checker::check_literal(const ast::literal_ptr &l, context &context, const type_ptr &types_tree) {
    context.check_predicate_signature(l->get_predicate()->get_id(), l->get_predicate()->get_terms());
}
