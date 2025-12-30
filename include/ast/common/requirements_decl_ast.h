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

#ifndef PLANK_REQUIREMENTS_DECL_AST_H
#define PLANK_REQUIREMENTS_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class requirements_decl;
    using requirements_decl_ptr = std::shared_ptr<requirements_decl>;
    using requirement_list      = std::list<requirement_ptr>;


    class requirements_decl : public ast_node {
    public:
        explicit requirements_decl(info info, requirement_list reqs) :
                 ast_node{std::move(info)},
                 m_reqs{std::move(reqs)} {
            for (const requirement_ptr &req : m_reqs)
                add_child(req);
        }

        [[nodiscard]] const requirement_list &get_requirements() const { return m_reqs; }

    private:
        const requirement_list m_reqs;
    };
}

#endif //PLANK_REQUIREMENTS_DECL_AST_H
