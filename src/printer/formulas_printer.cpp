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

#include "../../include/printer/formulas_printer.h"

using namespace epddl::printer;

json formulas_printer::build_formula_json(const del::language_ptr &language, const del::formula_ptr &f) {
    return std::visit([&](auto &&arg) -> json {
        return formulas_printer::build_formula_json(language, arg);
    }, f);
}

json formulas_printer::build_formula_json(const del::language_ptr &language, const del::true_formula_ptr &f) {
    return json{"true"};
}

json formulas_printer::build_formula_json(const del::language_ptr &language, const del::false_formula_ptr &f) {
    return json{"false"};
}

json formulas_printer::build_formula_json(const del::language_ptr &language, const del::atom_formula_ptr &f) {
    return json{language->get_atom_name(f->get_atom())};
}

json formulas_printer::build_formula_json(const del::language_ptr &language, const del::not_formula_ptr &f) {
    json f_json = formulas_printer::build_formula_json(language, f->get_formula());

    return json::object({
        {"connective", "not"},
        {"formula", std::move(f_json)}
    });
}

json formulas_printer::build_formula_json(const del::language_ptr &language, const del::and_formula_ptr &f) {
    json fs_json = json::array();

    for (const del::formula_ptr &f_ : f->get_formulas())
        fs_json.emplace_back(formulas_printer::build_formula_json(language, f_));

    return json::object({
        {"connective", "and"},
        {"formulas", std::move(fs_json)}
    });
}

json formulas_printer::build_formula_json(const del::language_ptr &language, const del::or_formula_ptr &f) {
    json fs_json = json::array();

    for (const del::formula_ptr &f_ : f->get_formulas())
        fs_json.emplace_back(formulas_printer::build_formula_json(language, f_));

    return json::object({
        {"connective", "or"},
        {"formulas", std::move(fs_json)}
    });
}

json formulas_printer::build_formula_json(const del::language_ptr &language, const del::imply_formula_ptr &f) {
    json f1_json = formulas_printer::build_formula_json(language, f->get_first_formula());
    json f2_json = formulas_printer::build_formula_json(language, f->get_second_formula());

    return json::object({
        {"connective", "imply"},
        {"formula", std::move(f1_json)},
        {"formula", std::move(f2_json)},
    });
}

json formulas_printer::build_formula_json(const del::language_ptr &language, const del::box_formula_ptr &f) {
    json modality = formulas_printer::build_agent_set_json(language, f->get_mod_index());
    json f_json = formulas_printer::build_formula_json(language, f->get_formula());

    return json::object({
        {"modality-name",  ""},
        {"modality-index", std::move(modality)},
        {"formula", std::move(f_json)}
    });
}

json formulas_printer::build_formula_json(const del::language_ptr &language, const del::diamond_formula_ptr &f) {
    json modality = formulas_printer::build_agent_set_json(language, f->get_mod_index());
    json f_json = formulas_printer::build_formula_json(language, f->get_formula());

    return json::object({
        {"modality-name",  ""},
        {"modality-index", std::move(modality)},
        {"formula", std::move(f_json)}
    });
}

json formulas_printer::build_formula_json(const del::language_ptr &language, const del::kw_box_formula_ptr &f) {
    json modality = formulas_printer::build_agent_set_json(language, f->get_mod_index());
    json f_json = formulas_printer::build_formula_json(language, f->get_formula());

    return json::object({
        {"modality-name",  "Kw."},
        {"modality-index", std::move(modality)},
        {"formula", std::move(f_json)}
    });
}

json formulas_printer::build_formula_json(const del::language_ptr &language, const del::kw_diamond_formula_ptr &f) {
    json modality = formulas_printer::build_agent_set_json(language, f->get_mod_index());
    json f_json = formulas_printer::build_formula_json(language, f->get_formula());

    return json::object({
        {"modality-name",  "Kw."},
        {"modality-index", std::move(modality)},
        {"formula", std::move(f_json)}
    });
}

json formulas_printer::build_formula_json(const del::language_ptr &language, const del::c_box_formula_ptr &f) {
    json modality = formulas_printer::build_agent_set_json(language, f->get_mod_index(), false);
    json f_json = formulas_printer::build_formula_json(language, f->get_formula());

    return json::object({
        {"modality-name",  "C."},
        {"modality-index", std::move(modality)},
        {"formula", std::move(f_json)}
    });
}

json formulas_printer::build_formula_json(const del::language_ptr &language, const del::c_diamond_formula_ptr &f) {
    json modality = formulas_printer::build_agent_set_json(language, f->get_mod_index(), false);
    json f_json = formulas_printer::build_formula_json(language, f->get_formula());

    return json::object({
        {"modality-name",  "C."},
        {"modality-index", std::move(modality)},
        {"formula", std::move(f_json)}
    });
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
