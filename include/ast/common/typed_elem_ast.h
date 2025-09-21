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
    class either_type;
    template<typename token_type>
    class typed_elem;

    using either_type_ptr       = std::shared_ptr<either_type>;
    using type                  = std::variant<identifier_ptr, either_type_ptr>;

    using typed_identifier      = typed_elem<identifier>;
    using typed_variable        = typed_elem<variable>;

    using typed_identifier_ptr  = std::shared_ptr<typed_identifier>;
    using typed_variable_ptr    = std::shared_ptr<typed_variable>;
    using typed_identifier_list = std::list<typed_identifier_ptr>;
    using typed_variable_list   = std::list<typed_variable_ptr>;

    using formal_param          = typed_variable_ptr;
    using formal_param_list     = std::list<formal_param>;

    class either_type : public ast_node {
    public:
        explicit either_type(identifier_list ids) :
                m_ids{std::move(ids)} {}

    private:
        const identifier_list m_ids;
    };

    template<typename elem>
    class typed_elem : public ast_node {
    public:
        using elem_ptr = std::shared_ptr<elem>;

        explicit typed_elem(elem_ptr id, std::optional<type> type = std::nullopt) :
                m_id{std::move(id)},
                m_type{std::move(type)} {}

        [[nodiscard]] const elem_ptr            &get_id()   const { return m_id;   }
        [[nodiscard]] const std::optional<type> &get_type() const { return m_type; }

    private:
        const elem_ptr m_id;
        const std::optional<type> m_type;
    };
}

#endif //EPDDL_TYPED_ELEM_AST_H
