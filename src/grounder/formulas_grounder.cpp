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

#include "../../include/grounder/formulas_grounder.h"
#include <memory>
#include <variant>

using namespace epddl;
using namespace epddl::grounder;

del::formula_ptr formulas_grounder::build_goal(const planning_specification &spec,
                                               const context &context,
                                               const del::language_ptr &language) {
    const auto &[problem, domain, libraries] = spec;
    del::formula_deque fs;

    for (const ast::problem_item &item : problem->get_items())
        if (std::holds_alternative<ast::goal_decl_ptr>(item))
            fs.emplace_back(formulas_grounder::build_formula(std::get<ast::goal_decl_ptr>(item)->get_goal(), context, language));

    return fs.size() == 1
        ? std::move(fs.front())
        : std::make_shared<del::and_formula>(std::move(fs));
}

del::formula_ptr formulas_grounder::build_formula(const ast::formula_ptr &f, const type_checker::context &context,
                                                  const del::language_ptr &language) {
    return std::visit([&](auto &&arg) {
        return formulas_grounder::build_formula(arg, context, language);
    }, f);
}

del::formula_ptr formulas_grounder::build_formula(const ast::true_formula_ptr &f, const type_checker::context &context, const del::language_ptr &language) {
    return std::make_shared<del::true_formula>();
}

del::formula_ptr formulas_grounder::build_formula(const ast::false_formula_ptr &f, const type_checker::context &context, const del::language_ptr &language) {
    return std::make_shared<del::false_formula>();
}

del::formula_ptr formulas_grounder::build_formula(const ast::predicate_formula_ptr &f, const type_checker::context &context, const del::language_ptr &language) {
    std::string atom_name = f->get_predicate()->get_id()->get_token().get_lexeme();    // todo: fix this

    return std::make_shared<del::atom_formula>(language->get_atom_id(atom_name));
}

del::formula_ptr formulas_grounder::build_formula(const ast::not_formula_ptr &f, const type_checker::context &context, const del::language_ptr &language) {
    return std::make_shared<del::not_formula>(formulas_grounder::build_formula(f->get_formula(), context, language));
}

del::formula_ptr formulas_grounder::build_formula(const ast::and_formula_ptr &f, const type_checker::context &context, const del::language_ptr &language) {
    del::formula_deque fs;

    for (const ast::formula_ptr &f_ : f->get_formulas())
        fs.emplace_back(formulas_grounder::build_formula(f_, context, language));

    return std::make_shared<del::and_formula>(std::move(fs));
}

del::formula_ptr formulas_grounder::build_formula(const ast::or_formula_ptr &f, const type_checker::context &context, const del::language_ptr &language) {
    del::formula_deque fs;

    for (const ast::formula_ptr &f_ : f->get_formulas())
        fs.emplace_back(formulas_grounder::build_formula(f_, context, language));

    return std::make_shared<del::or_formula>(std::move(fs));
}

del::formula_ptr formulas_grounder::build_formula(const ast::imply_formula_ptr &f, const type_checker::context &context, const del::language_ptr &language) {
    return std::make_shared<del::imply_formula>(formulas_grounder::build_formula(f->get_first_formula(), context, language),
                                                formulas_grounder::build_formula(f->get_second_formula(), context, language));
}

del::formula_ptr formulas_grounder::build_formula(const ast::box_formula_ptr &f, const type_checker::context &context, const del::language_ptr &language) {
    del::agent_group group = formulas_grounder::build_agent_group(
            f->get_modality()->get_modality_index(), context, language);
    del::formula_ptr f_ = formulas_grounder::build_formula(f->get_formula(), context, language);

    if (not f->get_modality()->get_modality_name().has_value())
        return std::make_shared<del::box_formula>(std::move(group), std::move(f_));
    else if ((*f->get_modality()->get_modality_name())->get_token().get_lexeme() == "Kw.")
        return std::make_shared<del::kw_box_formula>(std::move(group), std::move(f_));
    else if ((*f->get_modality()->get_modality_name())->get_token().get_lexeme() == "C.")
        return std::make_shared<del::c_box_formula>(std::move(group), std::move(f_));

    return std::make_shared<del::false_formula>();
}

del::formula_ptr formulas_grounder::build_formula(const ast::diamond_formula_ptr &f, const type_checker::context &context, const del::language_ptr &language) {
    del::agent_group group = formulas_grounder::build_agent_group(
            f->get_modality()->get_modality_index(), context, language);
    del::formula_ptr f_ = formulas_grounder::build_formula(f->get_formula(), context, language);

    if (not f->get_modality()->get_modality_name().has_value())
        return std::make_shared<del::diamond_formula>(std::move(group), std::move(f_));
    else if ((*f->get_modality()->get_modality_name())->get_token().get_lexeme() == "Kw.")
        return std::make_shared<del::kw_diamond_formula>(std::move(group), std::move(f_));
    else if ((*f->get_modality()->get_modality_name())->get_token().get_lexeme() == "C.")
        return std::make_shared<del::c_diamond_formula>(std::move(group), std::move(f_));

    return std::make_shared<del::false_formula>();
}

del::agent_group formulas_grounder::build_agent_group(const ast::modality_index_ptr &m, const context &context,
                                                      const del::language_ptr &language) {
    return del::agent_group{};
}
