// MIT License
//
// Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano_
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

#include "../../../include/frontend/printer/formula_printer.h"
#include <variant>

using namespace printer;

std::string formula_printer::to_string(const del::formula_ptr &f, const del::language_ptr &language, bool escape_html) {
    return std::visit([&](auto &&arg) {
        return formula_printer::to_string(arg, language, escape_html);
    }, f);
}

std::string formula_printer::to_string(const del::true_formula_ptr &f, const del::language_ptr &language, bool escape_html) {
    return "(true)";
}

std::string formula_printer::to_string(const del::false_formula_ptr &f, const del::language_ptr &language, bool escape_html) {
    return "(false)";
}

std::string formula_printer::to_string(const del::atom_formula_ptr &f, const del::language_ptr &language, bool escape_html) {
    return "(" + language->get_atom_name(f->get_atom()) + ")";
}

std::string formula_printer::to_string(const del::not_formula_ptr &f, const del::language_ptr &language, bool escape_html) {
    return "(not " + formula_printer::to_string(f->get_formula(), language, escape_html) + ")";
}

std::string formula_printer::to_string(const del::and_formula_ptr &f, const del::language_ptr &language, bool escape_html) {
    std::string f_and;

    for (const del::formula_ptr &g : f->get_formulas())
        f_and += " " + formula_printer::to_string(g, language, escape_html);

    return "(and" + f_and + ")";
}

std::string formula_printer::to_string(const del::or_formula_ptr &f, const del::language_ptr &language, bool escape_html) {
    std::string f_or;

    for (const del::formula_ptr &g : f->get_formulas())
        f_or += " " + formula_printer::to_string(g, language, escape_html);

    return "(or" + f_or + ")";
}

std::string formula_printer::to_string(const del::imply_formula_ptr &f, const del::language_ptr &language, bool escape_html) {
    return "(imply " + formula_printer::to_string(f->get_first_formula(), language, escape_html) + " " + formula_printer::to_string(f->get_second_formula(), language, escape_html) + ")";
}

std::string formula_printer::to_string(const del::box_formula_ptr &f, const del::language_ptr &language, bool escape_html) {
    return "([" + formula_printer::to_string(f->get_mod_index(), language) + "] " +
        formula_printer::to_string(f->get_formula(), language, escape_html) + ")";
}

std::string formula_printer::to_string(const del::diamond_formula_ptr &f, const del::language_ptr &language, bool escape_html) {
    std::string lt_str = escape_html ? "&lt;" : "<", gt_str = escape_html ? "&gt;" : ">";
    return "(" + lt_str + formula_printer::to_string(f->get_mod_index(), language) + gt_str + " " +
        formula_printer::to_string(f->get_formula(), language, escape_html) + ")";
}

std::string formula_printer::to_string(const del::kw_box_formula_ptr &f, const del::language_ptr &language, bool escape_html) {
    return "([Kw. " + formula_printer::to_string(f->get_mod_index(), language) + "] " +
        formula_printer::to_string(f->get_formula(), language, escape_html) + ")";
}

std::string formula_printer::to_string(const del::kw_diamond_formula_ptr &f, const del::language_ptr &language, bool escape_html) {
    std::string lt_str = escape_html ? "&lt;" : "<", gt_str = escape_html ? "&gt;" : ">";
    return "(" + lt_str + "Kw. " + formula_printer::to_string(f->get_mod_index(), language) + gt_str + " " +
        formula_printer::to_string(f->get_formula(), language, escape_html) + ")";
}

std::string formula_printer::to_string(const del::c_box_formula_ptr &f, const del::language_ptr &language, bool escape_html) {
    return "([C. " + formula_printer::to_string(f->get_mod_index(), language) + "] " +
        formula_printer::to_string(f->get_formula(), language, escape_html) + ")";
}

std::string formula_printer::to_string(const del::c_diamond_formula_ptr &f, const del::language_ptr &language, bool escape_html) {
    std::string lt_str = escape_html ? "&lt;" : "<", gt_str = escape_html ? "&gt;" : ">";
    return "(" + lt_str + "C. " + formula_printer::to_string(f->get_mod_index(), language) + gt_str + " " +
        formula_printer::to_string(f->get_formula(), language, escape_html) + ")";
}

std::string formula_printer::to_string(const del::agent_set &group, const del::language_ptr &language) {
    std::string group_str;

    for (const del::agent i : group)
        group_str += " " + language->get_agent_name(i);

    return group_str.substr(1);
}
