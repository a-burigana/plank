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

#ifndef EPDDL_TYPED_ELEM_AST_H
#define EPDDL_TYPED_ELEM_AST_H

#include "../../ast/ast_node.h"
#include "../tokens/tokens_ast.h"
#include <list>
#include <memory>
#include <optional>

namespace epddl::ast {
    template<typename token_type>
    class typed_elem;

    using typed_identifier      = typed_elem<identifier>;
    using typed_variable        = typed_elem<variable>;

    using typed_identifier_ptr  = std::unique_ptr<typed_identifier>;
    using typed_variable_ptr    = std::unique_ptr<typed_variable>;
    using typed_identifier_list = std::list<typed_identifier_ptr>;
    using typed_variable_list   = std::list<typed_variable_ptr>;

    using formal_param          = typed_variable_ptr;
    using formal_param_list     = std::list<formal_param>;

    template<typename token_type>
    class typed_elem : public ast_node {
    public:
        using token_type_ptr = std::unique_ptr<token_type>;

        explicit typed_elem(token_type_ptr id, std::optional<identifier_ptr> type = std::nullopt) :
                m_id{std::move(id)},
                m_type{std::move(type)} {}

    private:
        const token_type_ptr m_id;
        const std::optional<identifier_ptr> m_type;
    };
}

#endif //EPDDL_TYPED_ELEM_AST_H
