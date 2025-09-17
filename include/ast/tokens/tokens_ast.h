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

#ifndef EPDDL_TOKENS_AST_H
#define EPDDL_TOKENS_AST_H

#include "../../ast/ast_node.h"
#include "../../lexer/tokens/token_types.h"
#include "../../lexer/tokens/token.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class identifier;
    class variable;
    class modality_name;
    class integer;
    class requirement;

    using identifier_ptr    = std::shared_ptr<ast::identifier>;
    using variable_ptr      = std::shared_ptr<ast::variable>;
    using modality_name_ptr = std::shared_ptr<ast::modality_name>;
    using integer_ptr       = std::shared_ptr<ast::integer>;
    using requirement_ptr   = std::shared_ptr<ast::requirement>;

    using identifier_list   = std::list<identifier_ptr>;
    using variable_list     = std::list<variable_ptr>;

    class identifier : public ast_node {
    public:
        using token_type = ast_token::identifier;

        explicit identifier(token_ptr tok) :
                m_token{std::move(tok)} {}

        [[nodiscard]] const token&    get_token()     const { return *m_token; }
        [[nodiscard]] const token_ptr get_token_ptr() const { return  m_token; }

    private:
        const token_ptr m_token;
    };

    class variable : public identifier {
    public:
        using token_type = ast_token::variable;

        explicit variable(token_ptr var) :
                identifier{std::move(var)} {}
    };

    class modality_name : public ast_node {
    public:
        explicit modality_name(token_ptr tok) :
                m_token{std::move(tok)} {}

        [[nodiscard]] const token& get_token() const { return *m_token; }

    private:
        const token_ptr m_token;
    };

    class integer : public ast_node {
    public:
        using token_type = ast_token::integer;

        explicit integer(token_ptr val) :
                m_token{std::move(val)} {}

        [[nodiscard]] std::string get_val() const { return m_token->get_lexeme(); }

    private:
        const token_ptr m_token;
    };

    class requirement : public ast_node {
    public:
        using token_type = ast_token::requirement;

        explicit requirement(token_ptr req, std::optional<integer_ptr> val = std::nullopt) :
                m_req{std::move(req)},
                m_val{std::move(val)} {}

    private:
        const token_ptr m_req;
        const std::optional<integer_ptr> m_val;
    };
}

#endif //EPDDL_TOKENS_AST_H
