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

#ifndef EPDDL_DOMAIN_AST_H
#define EPDDL_DOMAIN_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "domain_libraries_ast.h"
#include "../common/requirements_decl_ast.h"
#include "types_decl_ast.h"
#include "predicates_decl_ast.h"
#include "constants_decl_ast.h"
#include "events/event_decl_ast.h"
#include "actions/action_decl_ast.h"
#include <list>
#include <memory>
#include <variant>

namespace epddl::ast {
    class domain;
    using domain_ptr       = std::shared_ptr<ast::domain>;

    using domain_item      = std::variant<domain_libraries_ptr, requirements_decl_ptr, types_decl_ptr,
                                          domain_predicates_ptr, constants_decl_ptr, event_ptr, action_ptr>;
    using domain_item_list = std::list<domain_item>;

    class domain : public ast_node {
    public:
        explicit domain(identifier_ptr name, domain_item_list items) :
                m_name{std::move(name)},
                m_items{std::move(items)} {}

        const identifier_ptr   &get_name()  const { return m_name;  }
        const domain_item_list &get_items() const { return m_items; }

    private:
        const identifier_ptr m_name;
        const domain_item_list m_items;
    };
}

#endif //EPDDL_DOMAIN_AST_H
