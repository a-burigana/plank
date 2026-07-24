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

#ifndef PLANK_SIGNATURE_TYPES_H
#define PLANK_SIGNATURE_TYPES_H

#include <memory>
#include <vector>
#include <deque>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include "del/semantics/states/states_types.h"

namespace search::utils {
    class signature;

    using label_id = unsigned long long;
    using signature_id = unsigned long long;

    using signature_set = std::set<signature_id>;
    using signature_set_id = unsigned long long;

    using signature_ptr = std::shared_ptr<signature>;
    using signature_set_ptr = std::shared_ptr<signature_set>;
    using agents_signature_set = std::vector<signature_set_id>;

    // using signature_map = std::unordered_map<signature_id, signature_id>;
    using signature_set_map    = std::unordered_map<signature_id, signature_set>;
    using signature_set_id_map = std::unordered_map<signature_id, signature_set_id>;

    using signature_vector = std::vector<signature_id>;
    using signature_matrix = std::vector<signature_vector>;
    // using signature_map = std::unordered_map<signature_id, std::pair<std::unique_ptr<del::world_bitset>, del::world_id>>;
}

#endif //PLANK_SIGNATURE_TYPES_H
