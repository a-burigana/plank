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

#include "json-printer/formulas_printer.h"

using namespace printer;

ordered_json formulas_printer::build_formula_json(const del::language_ptr &language, const del::formula_ptr &f) {
    ordered_json f_json;
    f_json["formula"] = formulas_printer::build_formula_json_helper(language, f);

    return f_json;
}

ordered_json formulas_printer::build_formula_json_helper(const del::language_ptr &language, const del::formula_ptr &f) {
    return std::visit([&](auto &&arg) -> ordered_json {
        return formulas_printer::build_formula_json_helper(language, arg);
    }, f);
}

ordered_json formulas_printer::build_formula_json_helper(const del::language_ptr &language, const del::true_formula_ptr &f) {
    return "true";
}

ordered_json formulas_printer::build_formula_json_helper(const del::language_ptr &language, const del::false_formula_ptr &f) {
    return "false";
}

ordered_json formulas_printer::build_formula_json_helper(const del::language_ptr &language, const del::atom_formula_ptr &f) {
    return language->get_atom_name(f->get_atom());
}

ordered_json formulas_printer::build_formula_json_helper(const del::language_ptr &language, const del::not_formula_ptr &f) {
    ordered_json not_json;
    not_json["connective"] = "not";
    not_json["formula"] = formulas_printer::build_formula_json_helper(language, f->get_formula());

    return not_json;
}

ordered_json formulas_printer::build_formula_json_helper(const del::language_ptr &language, const del::and_formula_ptr &f) {
    json fs_json = json::array();

    for (const del::formula_ptr &f_ : f->get_formulas())
        fs_json.emplace_back(formulas_printer::build_formula_json_helper(language, f_));

    ordered_json and_json;
    and_json["connective"] = "and";
    and_json["formulas"] = fs_json;

    return and_json;
}

ordered_json formulas_printer::build_formula_json_helper(const del::language_ptr &language, const del::or_formula_ptr &f) {
    json fs_json = json::array();

    for (const del::formula_ptr &f_ : f->get_formulas())
        fs_json.emplace_back(formulas_printer::build_formula_json_helper(language, f_));

    ordered_json or_json;
    or_json["connective"] = "or";
    or_json["formulas"] = fs_json;

    return or_json;
}

ordered_json formulas_printer::build_formula_json_helper(const del::language_ptr &language, const del::imply_formula_ptr &f) {
    json fs_json = json::array();

    fs_json.emplace_back(formulas_printer::build_formula_json_helper(language, f->get_first_formula()));
    fs_json.emplace_back(formulas_printer::build_formula_json_helper(language, f->get_second_formula()));

    ordered_json imply_json;
    imply_json["connective"] = "imply";
    imply_json["formulas"] = fs_json;

    return imply_json;
}

ordered_json formulas_printer::build_formula_json_helper(const del::language_ptr &language, const del::box_formula_ptr &f) {
    ordered_json mod_json;
    mod_json["modality-name"] = "box";
    mod_json["modality-index"] = formulas_printer::build_agent_set_json(language, f->get_mod_index());
    mod_json["formula"] = formulas_printer::build_formula_json_helper(language, f->get_formula());

    return mod_json;
}

ordered_json formulas_printer::build_formula_json_helper(const del::language_ptr &language, const del::diamond_formula_ptr &f) {
    ordered_json mod_json;
    mod_json["modality-name"] = "diamond";
    mod_json["modality-index"] = formulas_printer::build_agent_set_json(language, f->get_mod_index());
    mod_json["formula"] = formulas_printer::build_formula_json_helper(language, f->get_formula());

    return mod_json;
}

ordered_json formulas_printer::build_formula_json_helper(const del::language_ptr &language, const del::kw_box_formula_ptr &f) {
    ordered_json mod_json;
    mod_json["modality-name"] = "Kw.box";
    mod_json["modality-index"] = formulas_printer::build_agent_set_json(language, f->get_mod_index());
    mod_json["formula"] = formulas_printer::build_formula_json_helper(language, f->get_formula());

    return mod_json;
}

ordered_json formulas_printer::build_formula_json_helper(const del::language_ptr &language, const del::kw_diamond_formula_ptr &f) {
    ordered_json mod_json;
    mod_json["modality-name"] = "Kw.diamond";
    mod_json["modality-index"] = formulas_printer::build_agent_set_json(language, f->get_mod_index());
    mod_json["formula"] = formulas_printer::build_formula_json_helper(language, f->get_formula());

    return mod_json;
}

ordered_json formulas_printer::build_formula_json_helper(const del::language_ptr &language, const del::c_box_formula_ptr &f) {
    ordered_json mod_json;
    mod_json["modality-name"] = "C.box";
    mod_json["modality-index"] = formulas_printer::build_agent_set_json(language, f->get_mod_index(), false);
    mod_json["formula"] = formulas_printer::build_formula_json_helper(language, f->get_formula());

    return mod_json;
}

ordered_json formulas_printer::build_formula_json_helper(const del::language_ptr &language, const del::c_diamond_formula_ptr &f) {
    ordered_json mod_json;
    mod_json["modality-name"] = "C.diamond";
    mod_json["modality-index"] = formulas_printer::build_agent_set_json(language, f->get_mod_index(), false);
    mod_json["formula"] = formulas_printer::build_formula_json_helper(language, f->get_formula());

    return mod_json;
}

json formulas_printer::build_agent_set_json(const del::language_ptr &language, const del::agent_set &ags,
                                            bool simplify_singleton) {
    json ags_json = json::array();

    for (del::agent i : ags)
        ags_json.emplace_back(language->get_agent_name(i));

    return ags.size() == 1 and simplify_singleton
        ? json{ags_json.front()}
        : ags_json;
}
