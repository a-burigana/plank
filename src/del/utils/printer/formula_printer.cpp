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

#include "../../../../include/del/utils/printer/formula_printer.h"

using namespace printer;

std::string formula_printer::to_string(const del::formula &f, const del::language_ptr &language, bool escape_html) {
    switch (f.get_type()) {
        case del::formula_type::true_formula:
            return "true";
        case del::formula_type::false_formula:
            return "false";
        case del::formula_type::atom_formula:
            return formula_printer::to_string(dynamic_cast<const del::atom_formula &>(f), language, escape_html);
        case del::formula_type::not_formula:
            return formula_printer::to_string(dynamic_cast<const del::not_formula &>(f), language, escape_html);
        case del::formula_type::and_formula:
            return formula_printer::to_string(dynamic_cast<const del::and_formula &>(f), language, escape_html);
        case del::formula_type::or_formula:
            return formula_printer::to_string(dynamic_cast<const del::or_formula &>(f), language, escape_html);
        case del::formula_type::imply_formula:
            return formula_printer::to_string(dynamic_cast<const del::imply_formula &>(f), language, escape_html);
        case del::formula_type::box_formula:
            return formula_printer::to_string(dynamic_cast<const del::box_formula &>(f), language, escape_html);
        case del::formula_type::diamond_formula:
            return formula_printer::to_string(dynamic_cast<const del::diamond_formula &>(f), language, escape_html);
    }
}

std::string formula_printer::to_string(const del::atom_formula &f, const del::language_ptr &language, bool escape_html) {
    return language->get_atom_name(f.get_atom());
}

std::string formula_printer::to_string(const del::not_formula &f, const del::language_ptr &language, bool escape_html) {
    return "~" + formula_printer::to_string(*f.get_f(), language, escape_html);
}

std::string formula_printer::to_string(const del::and_formula &f, const del::language_ptr &language, bool escape_html) {
    std::string f_and;

    for (const del::formula_ptr &g : f.get_fs())
        f_and += formula_printer::to_string(*g, language, escape_html) + " /\\ ";

    return "(" + f_and.substr(0, f_and.size() - 4) + ")";
}

std::string formula_printer::to_string(const del::or_formula &f, const del::language_ptr &language, bool escape_html) {
    std::string f_or;

    for (const del::formula_ptr &g : f.get_fs())
        f_or += formula_printer::to_string(*g, language, escape_html) + " \\/ ";

    return "(" + f_or.substr(0, f_or.size() - 4) + ")";
}

std::string formula_printer::to_string(const del::imply_formula &f, const del::language_ptr &language, bool escape_html) {
    std::string imply_str = escape_html ? " -&gt; " : " -> ";
    return "(" + formula_printer::to_string(*f.get_f1(), language, escape_html) + imply_str + formula_printer::to_string(*f.get_f2(), language, escape_html) + ")";
}

std::string formula_printer::to_string(const del::box_formula &f, const del::language_ptr &language, bool escape_html) {
    return "[" + language->get_agent_name(f.get_ag()) + "]" + formula_printer::to_string(*f.get_f(), language, escape_html);
}

std::string formula_printer::to_string(const del::diamond_formula &f, const del::language_ptr &language, bool escape_html) {
    std::string lt_str = escape_html ? "&lt;" : "<", gt_str = escape_html ? "&gt;" : ">";
    return lt_str + language->get_agent_name(f.get_ag()) + gt_str + formula_printer::to_string(*f.get_f(), language, escape_html);
}
