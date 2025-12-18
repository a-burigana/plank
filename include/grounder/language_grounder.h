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

#ifndef EPDDL_LANGUAGE_GROUNDER_H
#define EPDDL_LANGUAGE_GROUNDER_H

#include "grounder_info.h"
#include "../type-checker/context/context.h"
#include "../del/language/language.h"
#include "combinations_handler.h"
#include "variables_assignment.h"

using namespace epddl::type_checker;

namespace epddl::grounder {
    class language_grounder {
    public:
        static del::language_ptr build_language(context &context);

        static std::string get_predicate_name(const ast::predicate_ptr &pred, grounder_info &info);
        static unsigned long get_predicate_id(const ast::predicate_ptr &pred, grounder_info &info);
        static std::string get_term_name(const ast::term &t, grounder_info &info, bool rename_variables = false);
        static unsigned long get_term_id(const ast::term &t, grounder_info &info, bool rename_variables = false);

    private:
        using atoms_info = std::tuple<del::name_vector, boost::dynamic_bitset<>>;

        static atoms_info build_atoms(context &context);
        static del::name_vector build_agents(context &context);
    };
}

#endif //EPDDL_LANGUAGE_GROUNDER_H
