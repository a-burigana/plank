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

#ifndef PLANK_SIGNATURE_CALCULATOR_H
#define PLANK_SIGNATURE_CALCULATOR_H

#include "signature_types.h"
#include "../utils/storages_handler.h"
#include "del/semantics/states/state.h"

using namespace plank;

namespace search::utils {
    class signature_calculator {
    public:
        static signature_set_id calculate_state_id(const del::state_ptr &s, storages_handler_ptr &handler);

        static signature_id calculate_world_signature(const del::state_ptr &s, del::world_id x, unsigned long h,
                                                      storages_handler_ptr &handler, signature_matrix &worlds_signatures);
    };
}

#endif //PLANK_SIGNATURE_CALCULATOR_H
