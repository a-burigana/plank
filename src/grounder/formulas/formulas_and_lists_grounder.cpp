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

#include "../../../include/grounder/formulas/formulas_and_lists_grounder.h"
#include "../../../include/grounder/language_grounder.h"
#include <memory>
#include <variant>

using namespace epddl;
using namespace epddl::grounder;

del::formula_ptr formulas_and_lists_grounder::build_goal(const planning_specification &spec, const context &context,
                                                         const type_ptr &types_tree, const del::atom_set &s_static,
                                                         const del::language_ptr &language) {
    const auto &[problem, domain, libraries] = spec;
    del::formula_deque fs;

    variables_assignment assignment{context.entities};

    for (const ast::problem_item &item : problem->get_items())
        if (std::holds_alternative<ast::goal_decl_ptr>(item))
            fs.emplace_back(formulas_and_lists_grounder::build_formula(
                    std::get<ast::goal_decl_ptr>(item)->get_goal(), context, types_tree, assignment, s_static, language));

    return fs.size() == 1
        ? std::move(fs.front())
        : std::make_shared<del::and_formula>(std::move(fs));
}

del::formula_ptr formulas_and_lists_grounder::build_formula(const ast::formula_ptr &f, const context &context,
                                                            const type_ptr &types_tree, variables_assignment &assignment,
                                                            const del::atom_set &s_static, const del::language_ptr &language) {
    return std::visit([&](auto &&arg) {
        return formulas_and_lists_grounder::build_formula(arg, context, types_tree, assignment, s_static, language);
    }, f);
}

del::formula_ptr formulas_and_lists_grounder::build_formula(const ast::true_formula_ptr &f, const context &context,
                                                            const type_ptr &types_tree, variables_assignment &assignment,
                                                            const del::atom_set &s_static, const del::language_ptr &language) {
    return std::make_shared<del::true_formula>();
}

del::formula_ptr formulas_and_lists_grounder::build_formula(const ast::false_formula_ptr &f, const context &context,
                                                            const type_ptr &types_tree, variables_assignment &assignment,
                                                            const del::atom_set &s_static, const del::language_ptr &language) {
    return std::make_shared<del::false_formula>();
}

del::formula_ptr formulas_and_lists_grounder::build_formula(const ast::predicate_formula_ptr &f, const context &context,
                                                            const type_ptr &types_tree, variables_assignment &assignment,
                                                            const del::atom_set &s_static, const del::language_ptr &language) {
    return std::make_shared<del::atom_formula>(language_grounder::get_predicate_id(f->get_predicate(), assignment, language));
}

del::formula_ptr formulas_and_lists_grounder::build_formula(const ast::eq_formula_ptr &f, const context &context,
                                                            const type_ptr &types_tree, variables_assignment &assignment,
                                                            const del::atom_set &s_static, const del::language_ptr &language) {
    if (language_grounder::get_term_id(f->get_first_term(), context.entities, assignment) ==
        language_grounder::get_term_id(f->get_second_term(), context.entities, assignment))
        return std::make_shared<del::true_formula>();
    else
        return std::make_shared<del::false_formula>();
}

del::formula_ptr formulas_and_lists_grounder::build_formula(const ast::neq_formula_ptr &f, const context &context,
                                                            const type_ptr &types_tree, variables_assignment &assignment,
                                                            const del::atom_set &s_static, const del::language_ptr &language) {
    if (language_grounder::get_term_id(f->get_first_term(), context.entities, assignment) !=
        language_grounder::get_term_id(f->get_second_term(), context.entities, assignment))
        return std::make_shared<del::true_formula>();
    else
        return std::make_shared<del::false_formula>();
}

del::formula_ptr formulas_and_lists_grounder::build_formula(const ast::not_formula_ptr &f, const context &context,
                                                            const type_ptr &types_tree, variables_assignment &assignment,
                                                            const del::atom_set &s_static, const del::language_ptr &language) {
    return std::make_shared<del::not_formula>(
            formulas_and_lists_grounder::build_formula(f->get_formula(), context, types_tree, assignment, s_static, language));
}

del::formula_ptr formulas_and_lists_grounder::build_formula(const ast::and_formula_ptr &f, const context &context,
                                                            const type_ptr &types_tree, variables_assignment &assignment,
                                                            const del::atom_set &s_static, const del::language_ptr &language) {
    del::formula_deque fs;

    for (const ast::formula_ptr &f_ : f->get_formulas())
        fs.emplace_back(formulas_and_lists_grounder::build_formula(f_, context, types_tree, assignment, s_static, language));

    return std::make_shared<del::and_formula>(std::move(fs));
}

del::formula_ptr formulas_and_lists_grounder::build_formula(const ast::or_formula_ptr &f, const context &context,
                                                            const type_ptr &types_tree, variables_assignment &assignment,
                                                            const del::atom_set &s_static, const del::language_ptr &language) {
    del::formula_deque fs;

    for (const ast::formula_ptr &f_ : f->get_formulas())
        fs.emplace_back(formulas_and_lists_grounder::build_formula(f_, context, types_tree, assignment, s_static, language));

    return std::make_shared<del::or_formula>(std::move(fs));
}

del::formula_ptr formulas_and_lists_grounder::build_formula(const ast::imply_formula_ptr &f, const context &context,
                                                            const type_ptr &types_tree, variables_assignment &assignment,
                                                            const del::atom_set &s_static, const del::language_ptr &language) {
    return std::make_shared<del::imply_formula>(
            formulas_and_lists_grounder::build_formula(f->get_first_formula(), context, types_tree, assignment, s_static, language),
            formulas_and_lists_grounder::build_formula(f->get_second_formula(), context, types_tree, assignment, s_static, language));
}

del::formula_ptr formulas_and_lists_grounder::build_formula(const ast::forall_formula_ptr &f, const context &context,
                                                            const type_ptr &types_tree, variables_assignment &assignment,
                                                            const del::atom_set &s_static, const del::language_ptr &language) {
    del::formula_deque fs;
    del::formula_ptr condition = formulas_and_lists_grounder::build_condition(
            f->get_list_compr()->get_condition(), context, types_tree, assignment, s_static, language);

    combinations_handler handler{f->get_list_compr()->get_formal_params(), context, types_tree,
                                 type_checker::either_type{type_utils::find(types_tree, "object")}};

    for (const combination &combination : list_comprehensions_handler::all(handler, condition, s_static)) {
        assignment.push(handler.get_typed_vars(), combination);
        fs.emplace_back(formulas_and_lists_grounder::build_formula(
                f->get_formula(), context, types_tree, assignment, s_static, language));
        assignment.pop();
    }
    return std::make_shared<del::and_formula>(std::move(fs));
}

del::formula_ptr formulas_and_lists_grounder::build_formula(const ast::exists_formula_ptr &f, const context &context,
                                                            const type_ptr &types_tree, variables_assignment &assignment,
                                                            const del::atom_set &s_static, const del::language_ptr &language) {
    del::formula_deque fs;
    del::formula_ptr condition = formulas_and_lists_grounder::build_condition(
            f->get_list_compr()->get_condition(), context, types_tree, assignment, s_static, language);

    combinations_handler handler{f->get_list_compr()->get_formal_params(), context, types_tree,
                                 type_checker::either_type{type_utils::find(types_tree, "object")}};

    for (const combination &combination : list_comprehensions_handler::all(handler, condition, s_static)) {
        assignment.push(handler.get_typed_vars(), combination);
        fs.emplace_back(formulas_and_lists_grounder::build_formula(
                f->get_formula(), context, types_tree, assignment, s_static, language));
        assignment.pop();
    }
    return std::make_shared<del::or_formula>(std::move(fs));
}

del::formula_ptr formulas_and_lists_grounder::build_formula(const ast::box_formula_ptr &f, const context &context,
                                                            const type_ptr &types_tree, variables_assignment &assignment,
                                                            const del::atom_set &s_static, const del::language_ptr &language) {
    del::agent_set group = formulas_and_lists_grounder::build_agent_group(
            f->get_modality()->get_modality_index(), context, types_tree, assignment, s_static, language);
    del::formula_ptr f_ = formulas_and_lists_grounder::build_formula(f->get_formula(), context, types_tree, assignment, s_static, language);

    if (not f->get_modality()->get_modality_name().has_value())
        return std::make_shared<del::box_formula>(std::move(group), std::move(f_));
    else if ((*f->get_modality()->get_modality_name())->get_token().get_lexeme() == "Kw.")
        return std::make_shared<del::kw_box_formula>(std::move(group), std::move(f_));
    else if ((*f->get_modality()->get_modality_name())->get_token().get_lexeme() == "C.")
        return std::make_shared<del::c_box_formula>(std::move(group), std::move(f_));

    return std::make_shared<del::false_formula>();
}

del::formula_ptr formulas_and_lists_grounder::build_formula(const ast::diamond_formula_ptr &f, const context &context,
                                                            const type_ptr &types_tree, variables_assignment &assignment,
                                                            const del::atom_set &s_static, const del::language_ptr &language) {
    del::agent_set group = formulas_and_lists_grounder::build_agent_group(
            f->get_modality()->get_modality_index(), context, types_tree, assignment, s_static, language);
    del::formula_ptr f_ = formulas_and_lists_grounder::build_formula(f->get_formula(), context, types_tree, assignment, s_static, language);

    if (not f->get_modality()->get_modality_name().has_value())
        return std::make_shared<del::diamond_formula>(std::move(group), std::move(f_));
    else if ((*f->get_modality()->get_modality_name())->get_token().get_lexeme() == "Kw.")
        return std::make_shared<del::kw_diamond_formula>(std::move(group), std::move(f_));
    else if ((*f->get_modality()->get_modality_name())->get_token().get_lexeme() == "C.")
        return std::make_shared<del::c_diamond_formula>(std::move(group), std::move(f_));

    return std::make_shared<del::false_formula>();
}

del::formula_ptr formulas_and_lists_grounder::build_condition(const std::optional<formula_ptr> &f, const context &context,
                                                              const type_ptr &types_tree, variables_assignment &assignment,
                                                              const del::atom_set &s_static, const del::language_ptr &language) {
    return f.has_value()
        ? formulas_and_lists_grounder::build_formula(*f, context, types_tree, assignment, s_static, language)
        : std::make_shared<del::true_formula>();
}

del::agent_set formulas_and_lists_grounder::build_agent_group(const ast::modality_index_ptr &m, const context &context,
                                                              const type_ptr &types_tree, variables_assignment &assignment,
                                                              const del::atom_set &s_static, const del::language_ptr &language) {
    return std::visit([&](auto &&arg) -> del::agent_set {
        return formulas_and_lists_grounder::build_agent_group(arg, context, types_tree, assignment, s_static, language);
    }, m);
}

del::agent_set formulas_and_lists_grounder::build_agent_group(const ast::term &m, const context &context,
                                                              const type_ptr &types_tree, variables_assignment &assignment,
                                                              const del::atom_set &s_static, const del::language_ptr &language) {
    del::agent_set group{language->get_agents_number()};
    group.push_back(language_grounder::get_term_id(m, context.entities, assignment));

    return group;
}

del::agent_set formulas_and_lists_grounder::build_agent_group(const ast::list<ast::simple_agent_group_ptr> &m, const context &context,
                                                              const type_ptr &types_tree, variables_assignment &assignment,
                                                              const del::atom_set &s_static, const del::language_ptr &language) {
    boost::dynamic_bitset<> group(language->get_agents_number());

    auto ground_elem = formulas_and_lists_grounder::grounding_function_t<ast::simple_agent_group_ptr, boost::dynamic_bitset<>>(
        [&](const ast::simple_agent_group_ptr &group, const class context &context, const type_ptr &types_tree,
            const type_ptr &default_type, variables_assignment &assignment,
            const del::atom_set &s_static, const del::language_ptr &language) {
            boost::dynamic_bitset<> g{language->get_agents_number()};

            for (const ast::term &t : group->get_terms())
                g.set(language_grounder::get_term_id(t, context.entities, assignment));

            return g;
        });

    auto gs = formulas_and_lists_grounder::build_list<ast::simple_agent_group_ptr, boost::dynamic_bitset<>>(
            m, ground_elem, context, types_tree, type_utils::find(types_tree, "object"),
            assignment, s_static, language);

    for (const boost::dynamic_bitset<> &g : gs)
        group |= g;

    return bit_deque{group};
}

del::agent_set formulas_and_lists_grounder::build_agent_group(const ast::all_group_modality_ptr &m, const context &context,
                                                              const type_ptr &types_tree, variables_assignment &assignment,
                                                              const del::atom_set &s_static, const del::language_ptr &language) {
    return language->get_agent_set();
}
