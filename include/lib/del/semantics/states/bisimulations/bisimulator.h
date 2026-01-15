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

#ifndef PLANK_BISIMULATOR_H
#define PLANK_BISIMULATOR_H

#include <utility>
#include "../../../language/language.h"
#include "bisimulation_types.h"
#include "../state.h"

namespace del {
    class bisimulator {
    public:
        static del::state_ptr contract(const del::state_ptr &s);

//        static bool are_bisimilar(const del::state_ptr &s, const del::state_ptr &t, unsigned long k, del::storages_handler_ptr handler);

    private:
        static del::state_ptr disjoint_union(const del::state_ptr &s, const del::state_ptr &t);
    };
}

#endif //PLANK_BISIMULATOR_H
