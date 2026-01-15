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

#ifndef PLANK_CONTEXT_TYPES_H
#define PLANK_CONTEXT_TYPES_H

#include "../entity_kinds.h"
#include "../type.h"
#include "../../ast/planning_specification.h"
#include "../../utils/bit_deque.h"
#include <set>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace epddl::type_checker {
    using type_map          = std::unordered_map<std::string, either_type>;
    using string_set        = std::unordered_set<std::string>;

    class typed_var;
    using typed_var_list    = std::list<typed_var>;
    using signature_map     = std::unordered_map<std::string, typed_var_list>;
    using string_bool_map   = std::unordered_map<std::string, bool>;
    using string_string_map = std::unordered_map<std::string, std::string>;

    using name_vector       = std::vector<std::string>;
    using name_id_map       = std::unordered_map<std::string, unsigned long>;
    using bit_deque_vector  = std::vector<bit_deque>;

    template<typename ast_node_type>
    using ast_node_map = std::unordered_map<std::string, ast_node_type>;

    struct typed_var {
        typed_var(std::string var_, either_type type_) :
            var{std::move(var_)},
            type{std::move(type_)} {
        }

        std::string var;
        either_type type;
    };
}

#endif //PLANK_CONTEXT_TYPES_H
