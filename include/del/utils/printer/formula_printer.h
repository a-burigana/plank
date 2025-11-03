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

#ifndef EPDDL_FORMULA_PRINTER_H
#define EPDDL_FORMULA_PRINTER_H

#include <string>
#include "../../language/language.h"
#include "../../language/formulas.h"

namespace printer {
    class formula_printer {
    public:
        [[nodiscard]] static std::string to_string(const del::formula_ptr &f, const del::language_ptr &language, bool escape_html);

    private:
        [[nodiscard]] static std::string to_string(const del::atom_formula_ptr &f, const del::language_ptr &language, bool escape_html);
        [[nodiscard]] static std::string to_string(const del::not_formula_ptr &f, const del::language_ptr &language, bool escape_html);
        [[nodiscard]] static std::string to_string(const del::and_formula_ptr &f, const del::language_ptr &language, bool escape_html);
        [[nodiscard]] static std::string to_string(const del::or_formula_ptr &f, const del::language_ptr &language, bool escape_html);
        [[nodiscard]] static std::string to_string(const del::imply_formula_ptr &f, const del::language_ptr &language, bool escape_html);
        [[nodiscard]] static std::string to_string(const del::box_formula_ptr &f, const del::language_ptr &language, bool escape_html);
        [[nodiscard]] static std::string to_string(const del::diamond_formula_ptr &f, const del::language_ptr &language, bool escape_html);
        [[nodiscard]] static std::string to_string(const del::kw_box_formula_ptr &f, const del::language_ptr &language, bool escape_html);
        [[nodiscard]] static std::string to_string(const del::kw_diamond_formula_ptr &f, const del::language_ptr &language, bool escape_html);
        [[nodiscard]] static std::string to_string(const del::c_box_formula_ptr &f, const del::language_ptr &language, bool escape_html);
        [[nodiscard]] static std::string to_string(const del::c_diamond_formula_ptr &f, const del::language_ptr &language, bool escape_html);

        [[nodiscard]] static std::string to_string(const del::agent_group &group, const del::language_ptr &language);
    };
}

#endif //EPDDL_FORMULA_PRINTER_H
