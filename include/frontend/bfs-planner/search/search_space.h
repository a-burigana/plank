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

#ifndef PLANK_SEARCH_SPACE_H
#define PLANK_SEARCH_SPACE_H

#include <memory>
#include "search_types.h"
#include "../../../lib/del/semantics/states/state.h"
#include "../../../lib/del/semantics/actions/action.h"

namespace search {
    class node {
    public:
        node(unsigned long long id, del::state_ptr state, del::action_ptr action = nullptr, node_ptr parent = nullptr);

        node(const node&) = delete;
        node& operator=(const node&) = delete;

        node(node&&) = default;
        node& operator=(node&&) = default;

        ~node() = default;

        [[nodiscard]] unsigned long long get_id() const;
        [[nodiscard]] unsigned long long get_graph_depth() const;

        [[nodiscard]] del::state_ptr get_state() const;
        [[nodiscard]] del::action_ptr get_action() const;

        [[nodiscard]] node_ptr get_parent() const;
        [[nodiscard]] const node_deque &get_children() const;

        void add_child(const node_ptr &child);

    private:
        unsigned long long m_id, m_graph_depth;

        del::state_ptr m_state;
        del::action_ptr m_action;

        node_ptr m_parent;
        node_deque m_children;
    };
}

#endif //PLANK_SEARCH_SPACE_H
