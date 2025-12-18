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

#include "../../../include/type-checker/common/formulas_and_lists_type_checker.h"

using namespace epddl;
using namespace epddl::type_checker;

void formulas_and_lists_type_checker::check_formula(const ast::formula_ptr &f, context &context, bool assert_static) {
    std::visit([&](auto &&arg) {
        check_formula(arg, context, assert_static);
    }, f);
}

void formulas_and_lists_type_checker::check_formula(const ast::true_formula_ptr &f, context &context, bool assert_static) {
}

void formulas_and_lists_type_checker::check_formula(const ast::false_formula_ptr &f, context &context, bool assert_static) {
}

void formulas_and_lists_type_checker::check_formula(const ast::predicate_formula_ptr &f, context &context, bool assert_static) {
    const ast::predicate_ptr &pred = f->get_predicate();
    context.predicates.check_predicate_signature(context.types, context.entities, pred->get_id(), pred->get_terms());

    if (assert_static)
        context.predicates.assert_fact(f->get_predicate()->get_id());
}

void formulas_and_lists_type_checker::check_formula(const ast::eq_formula_ptr &f, context &context, bool assert_static) {
    context.entities.assert_declared(f->get_first_term());
    context.entities.assert_declared(f->get_second_term());
}

void formulas_and_lists_type_checker::check_formula(const ast::neq_formula_ptr &f, context &context, bool assert_static) {
    context.entities.assert_declared(f->get_first_term());
    context.entities.assert_declared(f->get_second_term());
}

//void formulas_type_checker::check_formula(const ast::in_formula_ptr &f, context &context, bool assert_static) {
//    context.assert_declared(f->get_term());
//    check_list(f->get_list(), context);
//}

void formulas_and_lists_type_checker::check_formula(const ast::not_formula_ptr &f, context &context, bool assert_static) {
    check_formula(f->get_formula(), context, assert_static);
}

void formulas_and_lists_type_checker::check_formula(const ast::and_formula_ptr &f, context &context, bool assert_static) {
    for (const auto &f_ : f->get_formulas())
        check_formula(f_, context, assert_static);
}

void formulas_and_lists_type_checker::check_formula(const ast::or_formula_ptr &f, context &context, bool assert_static) {
    for (const auto &f_ : f->get_formulas())
        check_formula(f_, context, assert_static);
}

void formulas_and_lists_type_checker::check_formula(const ast::imply_formula_ptr &f, context &context, bool assert_static) {
    check_formula(f->get_first_formula(), context, assert_static);
    check_formula(f->get_second_formula(), context, assert_static);
}

void formulas_and_lists_type_checker::check_formula(const ast::box_formula_ptr &f, context &context, bool assert_static) {
    bool group_only_modality = formulas_and_lists_type_checker::is_group_only_modality(f->get_modality());
    bool is_ck_modality = f->get_modality()->get_modality_name().has_value() and
                          (*f->get_modality()->get_modality_name())->get_token().get_lexeme() == "C.";

    if (is_ck_modality) {
        if (formulas_and_lists_type_checker::is_static_formula(f->get_formula(), context))
            f->get_modality()->add_requirement(":static-common-knowledge",
                                               "Use of C. modalities in static formulas requires ':static-common-knowledge'.");
        else
            f->get_modality()->add_requirement(":common-knowledge",
                                               "Use of C. modalities requires ':common-knowledge'.");
    }

    check_modality_index(f->get_modality()->get_modality_index(), context, group_only_modality);
    check_formula(f->get_formula(), context, assert_static);
}

void formulas_and_lists_type_checker::check_formula(const ast::diamond_formula_ptr &f, context &context, bool assert_static) {
    bool group_only_modality = formulas_and_lists_type_checker::is_group_only_modality(f->get_modality());

    check_modality_index(f->get_modality()->get_modality_index(), context, group_only_modality);
    check_formula(f->get_formula(), context, assert_static);
}

void formulas_and_lists_type_checker::check_formula(const ast::forall_formula_ptr &f, context &context, bool assert_static) {
    context.entities.push();
    check_list_comprehension(f->get_list_compr(), context, context.types.get_type("entity"));
    context.entities.update_typed_entities_sets(context.types);
    check_formula(f->get_formula(), context, assert_static);
    context.entities.pop();
}

void formulas_and_lists_type_checker::check_formula(const ast::exists_formula_ptr &f, context &context, bool assert_static) {
    context.entities.push();
    check_list_comprehension(f->get_list_compr(), context, context.types.get_type("entity"));
    context.entities.update_typed_entities_sets(context.types);
    check_formula(f->get_formula(), context, assert_static);
    context.entities.pop();
}

void formulas_and_lists_type_checker::check_list_comprehension(const ast::list_comprehension_ptr &list_compr,
                                                               context &context, const type_ptr &default_type) {
    context.entities.add_decl_list(context.types, list_compr->get_formal_params(), default_type);

    if (list_compr->get_condition().has_value())
        check_formula(*list_compr->get_condition(), context, true);
}

void formulas_and_lists_type_checker::check_agent_group(const ast::list<ast::simple_agent_group_ptr> &list,
                                                        context &context, bool group_only_modality) {
    auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::simple_agent_group_ptr>(
            [&] (const ast::simple_agent_group_ptr &group, class context &context, const type_ptr &default_type) {
                for (const ast::term &term : group->get_terms())
                    formulas_and_lists_type_checker::check_modality_index_type(term, context, group_only_modality);
            });

    formulas_and_lists_type_checker::check_list(list, check_elem, context, context.types.get_type("agent"));
}

void formulas_and_lists_type_checker::check_modality_index(const ast::modality_index_ptr &index, context &context,
                                                           bool group_only_modality) {
    const type_ptr &agent = context.types.get_type("agent");

    if (std::holds_alternative<ast::term>(index))
        formulas_and_lists_type_checker::check_modality_index_type(std::get<ast::term>(index), context, group_only_modality);
    else if (std::holds_alternative<ast::list<ast::simple_agent_group_ptr>>(index))
        check_agent_group(std::get<ast::list<ast::simple_agent_group_ptr>>(index), context, group_only_modality);
}

void formulas_and_lists_type_checker::check_modality_index_type(const ast::term &term, context &context,
                                                                bool group_only_modality) {
    either_type only_group_mod_index = either_type{context.types.get_type_id(context.types.get_type("agent-group"))};
    either_type all_mod_index = either_type{context.types.get_type_id("agent"),
                                            context.types.get_type_id("agent-group")};

    if (group_only_modality)
        context.entities.check_type(context.types, term, only_group_mod_index);
    else
        context.entities.check_type(context.types, term, all_mod_index);
}

bool formulas_and_lists_type_checker::is_group_only_modality(const ast::modality_ptr &mod) {
    return mod->get_modality_name().has_value() and
           (*mod->get_modality_name())->get_token().get_lexeme() == "C.";
}

void formulas_and_lists_type_checker::check_literal(const ast::literal_ptr &l, context &context) {
    context.predicates.check_predicate_signature(context.types, context.entities, l->get_predicate()->get_id(), l->get_predicate()->get_terms());
}

bool formulas_and_lists_type_checker::is_propositional_formula(const ast::formula_ptr &f) {
    return std::visit([&](auto &&arg) {
        return formulas_and_lists_type_checker::is_propositional_formula(arg);
    }, f);
}

bool formulas_and_lists_type_checker::is_propositional_formula(const ast::true_formula_ptr &f) {
    return true;
}

bool formulas_and_lists_type_checker::is_propositional_formula(const ast::false_formula_ptr &f) {
    return true;
}

bool formulas_and_lists_type_checker::is_propositional_formula(const ast::predicate_formula_ptr &f) {
    return true;
}

bool formulas_and_lists_type_checker::is_propositional_formula(const ast::eq_formula_ptr &f) {
    return true;
}

bool formulas_and_lists_type_checker::is_propositional_formula(const ast::neq_formula_ptr &f) {
    return true;
}

bool formulas_and_lists_type_checker::is_propositional_formula(const ast::not_formula_ptr &f) {
    return formulas_and_lists_type_checker::is_propositional_formula(f->get_formula());
}

bool formulas_and_lists_type_checker::is_propositional_formula(const ast::and_formula_ptr &f) {
    return std::all_of(f->get_formulas().begin(), f->get_formulas().end(), [&](const ast::formula_ptr &f) {
        return formulas_and_lists_type_checker::is_propositional_formula(f);
    });
}

bool formulas_and_lists_type_checker::is_propositional_formula(const ast::or_formula_ptr &f) {
    return std::all_of(f->get_formulas().begin(), f->get_formulas().end(), [&](const ast::formula_ptr &f) {
        return formulas_and_lists_type_checker::is_propositional_formula(f);
    });
}

bool formulas_and_lists_type_checker::is_propositional_formula(const ast::imply_formula_ptr &f) {
    return formulas_and_lists_type_checker::is_propositional_formula(f->get_first_formula()) and
           formulas_and_lists_type_checker::is_propositional_formula(f->get_second_formula());
}

bool formulas_and_lists_type_checker::is_propositional_formula(const ast::box_formula_ptr &f) {
    return false;
}

bool formulas_and_lists_type_checker::is_propositional_formula(const ast::diamond_formula_ptr &f) {
    return false;
}

bool formulas_and_lists_type_checker::is_propositional_formula(const ast::forall_formula_ptr &f) {
    // We don't need to check whether the list formula is static, this was already taken care of
    return formulas_and_lists_type_checker::is_propositional_formula(f->get_formula());
}

bool formulas_and_lists_type_checker::is_propositional_formula(const ast::exists_formula_ptr &f) {
    // We don't need to check whether the list formula is static, this was already taken care of
    return formulas_and_lists_type_checker::is_propositional_formula(f->get_formula());
}

bool formulas_and_lists_type_checker::is_static_formula(const ast::formula_ptr &f, context &context) {
    return std::visit([&](auto &&arg) {
        return formulas_and_lists_type_checker::is_static_formula(arg, context);
    }, f);
}

bool formulas_and_lists_type_checker::is_static_formula(const ast::true_formula_ptr &f, context &context) {
    return true;
}

bool formulas_and_lists_type_checker::is_static_formula(const ast::false_formula_ptr &f, context &context) {
    return true;
}

bool formulas_and_lists_type_checker::is_static_formula(const ast::predicate_formula_ptr &f, context &context) {
    return context.predicates.is_fact(f->get_predicate()->get_id());
}

bool formulas_and_lists_type_checker::is_static_formula(const ast::eq_formula_ptr &f, context &context) {
    return true;
}

bool formulas_and_lists_type_checker::is_static_formula(const ast::neq_formula_ptr &f, context &context) {
    return true;
}

bool formulas_and_lists_type_checker::is_static_formula(const ast::not_formula_ptr &f, context &context) {
    return formulas_and_lists_type_checker::is_static_formula(f->get_formula(), context);
}

bool formulas_and_lists_type_checker::is_static_formula(const ast::and_formula_ptr &f, context &context) {
    return std::all_of(f->get_formulas().begin(), f->get_formulas().end(), [&](const ast::formula_ptr &f) {
        return formulas_and_lists_type_checker::is_static_formula(f, context);
    });
}

bool formulas_and_lists_type_checker::is_static_formula(const ast::or_formula_ptr &f, context &context) {
    return std::all_of(f->get_formulas().begin(), f->get_formulas().end(), [&](const ast::formula_ptr &f) {
        return formulas_and_lists_type_checker::is_static_formula(f, context);
    });
}

bool formulas_and_lists_type_checker::is_static_formula(const ast::imply_formula_ptr &f, context &context) {
    return formulas_and_lists_type_checker::is_static_formula(f->get_first_formula(), context) and
           formulas_and_lists_type_checker::is_static_formula(f->get_second_formula(), context);
}

bool formulas_and_lists_type_checker::is_static_formula(const ast::box_formula_ptr &f, context &context) {
    return formulas_and_lists_type_checker::is_static_formula(f->get_formula(), context);
}

bool formulas_and_lists_type_checker::is_static_formula(const ast::diamond_formula_ptr &f, context &context) {
    return formulas_and_lists_type_checker::is_static_formula(f->get_formula(), context);
}

bool formulas_and_lists_type_checker::is_static_formula(const ast::forall_formula_ptr &f, context &context) {
    // We don't need to check whether the list formula is static, this was already taken care of
    return formulas_and_lists_type_checker::is_static_formula(f->get_formula(), context);
}

bool formulas_and_lists_type_checker::is_static_formula(const ast::exists_formula_ptr &f, context &context) {
    // We don't need to check whether the list formula is static, this was already taken care of
    return formulas_and_lists_type_checker::is_static_formula(f->get_formula(), context);
}
