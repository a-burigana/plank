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

#ifndef PLANK_TYPED_ELEM_AST_H
#define PLANK_TYPED_ELEM_AST_H

#include "../../ast/ast_node.h"
#include "../tokens/tokens_ast.h"
#include <list>
#include <memory>
#include <optional>

namespace epddl::ast {
    class either_type;
    class typed_identifier;
    class typed_variable;

    using either_type_ptr       = std::shared_ptr<either_type>;
    using type                  = std::variant<identifier_ptr, either_type_ptr>;

    using typed_identifier_ptr  = std::shared_ptr<typed_identifier>;
    using typed_variable_ptr    = std::shared_ptr<typed_variable>;
    using typed_identifier_list = std::list<typed_identifier_ptr>;
    using typed_variable_list   = std::list<typed_variable_ptr>;

    using formal_param          = typed_variable_ptr;
    using formal_param_list     = std::list<formal_param>;

    class either_type : public ast_node {
    public:
        explicit either_type(info info, identifier_list ids) :
                ast_node{std::move(info)},
                m_ids{std::move(ids)} {
            for (const identifier_ptr &id : m_ids)
                add_child(id);
        }

        [[nodiscard]] const identifier_list &get_ids() const { return m_ids; }

    private:
        const identifier_list m_ids;
    };

    class typed_identifier : public ast_node {
    public:
        explicit typed_identifier(info info, identifier_ptr id, std::optional<identifier_ptr> type = std::nullopt) :
                ast_node{std::move(info)},
                m_id{std::move(id)},
                m_type{std::move(type)} {
            add_child(m_id);
            if (m_type.has_value()) add_child(*m_type);
        }

        [[nodiscard]] const identifier_ptr                &get_id()   const { return m_id;   }
        [[nodiscard]] const std::optional<identifier_ptr> &get_type() const { return m_type; }

    private:
        const identifier_ptr m_id;
        const std::optional<identifier_ptr> m_type;
    };

    class typed_variable : public ast_node {
    public:
        explicit typed_variable(info info, variable_ptr var, std::optional<type> type = std::nullopt) :
                ast_node{std::move(info)},
                m_var{std::move(var)},
                m_type{std::move(type)} {
            add_child(m_var);
            if (m_type.has_value()) std::visit([&](auto &&arg) { add_child(arg); }, *m_type);
        }

        [[nodiscard]] const variable_ptr        &get_var()  const { return m_var;  }
        [[nodiscard]] const std::optional<type> &get_type() const { return m_type; }

    private:
        const variable_ptr m_var;
        const std::optional<type> m_type;
    };
}

#endif //PLANK_TYPED_ELEM_AST_H
