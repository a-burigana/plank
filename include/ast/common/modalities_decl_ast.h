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

#ifndef EPDDL_MODALITIES_DECL_AST_H
#define EPDDL_MODALITIES_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class modalities_decl;
    using modalities_decl_ptr = std::unique_ptr<ast::modalities_decl>;
    using modality_name_list  = std::list<modality_name_ptr>;

    class modalities_decl : public ast_node {
    public:
        explicit modalities_decl(modality_name_list mods) :
                m_mods{std::move(mods)} {}

    private:
        const modality_name_list m_mods;
    };
}

#endif //EPDDL_MODALITIES_DECL_AST_H
