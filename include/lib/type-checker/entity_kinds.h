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

#ifndef PLANK_ENTITY_KINDS_H
#define PLANK_ENTITY_KINDS_H

#include "../ast/common/formulas_ast.h"
#include <cstdint>
#include <optional>
#include <variant>

namespace epddl::type_checker {
    class epddl_entity_decl;
    class del_entity_decl;
    using entity_decl = std::variant<epddl_entity_decl, del_entity_decl>;

    enum class entity_kind : uint8_t {
        object,
        agent,
        agent_group
    };

    enum class del_entity_kind : uint8_t {
        world,
        event,
        observability_group
    };

    class epddl_entity_decl {
    public:
        epddl_entity_decl(token_ptr &tok, entity_kind kind, std::optional<ast::identifier_ptr> &type) :
            m_tok{tok},
            m_kind{kind},
            m_type{type} {}

        [[nodiscard]] const token_ptr &get_tok() const {
            return m_tok;
        }

        bool operator<(const epddl_entity_decl &rhs) const {
            return std::tie(m_tok, m_kind, m_type) < std::tie(rhs.m_tok, rhs.m_kind, rhs.m_type);
        }

        bool operator> (const epddl_entity_decl &rhs) const {
            return rhs < *this;
        }

        bool operator<=(const epddl_entity_decl &rhs) const {
            return not (rhs < *this);
        }

        bool operator>=(const epddl_entity_decl &rhs) const {
            return not (*this < rhs);
        }

    private:
        token_ptr m_tok;
        entity_kind m_kind;
        std::optional<ast::identifier_ptr> m_type;
    };

    class del_entity_decl {
    public:
        del_entity_decl(token_ptr &tok, del_entity_kind kind) :
            m_tok{tok},
            m_kind{kind} {}

        [[nodiscard]] const token_ptr &get_tok() const {
            return m_tok;
        }

        bool operator<(const del_entity_decl &rhs) const {
            return std::tie(m_tok, m_kind) < std::tie(rhs.m_tok, rhs.m_kind);
        }

        bool operator>(const del_entity_decl &rhs) const {
            return rhs < *this;
        }

        bool operator<=(const del_entity_decl &rhs) const {
            return not (rhs < *this);
        }

        bool operator>=(const del_entity_decl &rhs) const {
            return not (*this < rhs);
        }

    private:
        token_ptr m_tok;
        del_entity_kind m_kind;
    };
}

#endif //PLANK_ENTITY_KINDS_H
