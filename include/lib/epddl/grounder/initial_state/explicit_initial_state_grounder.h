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

#ifndef PLANK_EXPLICIT_INITIAL_STATE_GROUNDER_H
#define PLANK_EXPLICIT_INITIAL_STATE_GROUNDER_H

#include "grounder/grounder_info.h"
#include "type-checker/context/context.h"
#include "../../../del/semantics/states/state.h"

using namespace epddl::type_checker;

namespace epddl::grounder {
    class explicit_initial_state_grounder {
    public:
        static del::state_ptr build_initial_state(const ast::explicit_initial_state_ptr &state, grounder_info &info);

    private:
        static del::label_vector
        build_label_vector(const ast::explicit_initial_state_ptr &state, const name_id_map &worlds_ids,
                           del::world_id worlds_no, grounder_info &info);

        static del::label build_label(const world_label_ptr &l, const boost::dynamic_bitset<> &public_static_bitset,
                                      grounder_info &info);
    };
}

#endif //PLANK_EXPLICIT_INITIAL_STATE_GROUNDER_H
