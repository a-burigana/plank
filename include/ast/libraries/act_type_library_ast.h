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

#ifndef EPDDL_ACT_TYPE_LIBRARY_AST_H
#define EPDDL_ACT_TYPE_LIBRARY_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "../common/requirements_decl_ast.h"
#include "../common/modalities_decl_ast.h"
#include "act_type_decl_ast.h"
#include <list>
#include <memory>
#include <variant>

namespace epddl::ast {
    class act_type_library;
    using act_type_library_ptr       = std::shared_ptr<ast::act_type_library>;

    using act_type_library_item      = std::variant<requirements_decl_ptr, action_type_ptr>;
    using act_type_library_item_list = std::list<act_type_library_item>;

    class act_type_library : public ast_node {
    public:
        explicit act_type_library(identifier_ptr name, act_type_library_item_list items) :
                m_name{std::move(name)},
                m_items{std::move(items)} {}

    private:
        const identifier_ptr m_name;
        const act_type_library_item_list m_items;
    };
}

#endif //EPDDL_ACT_TYPE_LIBRARY_AST_H
