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

#ifndef PLANK_AGENTS_DECL_AST_H
#define PLANK_AGENTS_DECL_AST_H

#include "../ast_node.h"
#include "../common/typed_elem_ast.h"
#include <memory>

namespace epddl::ast {
    class agents_decl;
    using agents_decl_ptr  = std::shared_ptr<agents_decl>;

    class agents_decl : public ast_node {
    public:
        explicit agents_decl(info info, typed_identifier_list agents) :
                ast_node{std::move(info)},
                m_agents{std::move(agents)} {
            for (const typed_identifier_ptr &id : m_agents)
                add_child(id);
        }

        [[nodiscard]] const typed_identifier_list &get_agents() const { return m_agents; }

    private:
        const typed_identifier_list m_agents;
    };
}

#endif //PLANK_AGENTS_DECL_AST_H
