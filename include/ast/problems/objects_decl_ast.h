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

#ifndef EPDDL_OBJECTS_DECL_AST_H
#define EPDDL_OBJECTS_DECL_AST_H

#include "../ast_node.h"
#include "../common/typed_elem_ast.h"
#include <memory>

namespace epddl::ast {
    class objects_decl;
    using objects_decl_ptr  = std::shared_ptr<objects_decl>;

    class objects_decl : public ast_node {
    public:
        explicit objects_decl(typed_identifier_list objects) :
                m_objects{std::move(objects)} {}

        [[nodiscard]] const typed_identifier_list &get_objects() const { return m_objects; }

    private:
        const typed_identifier_list m_objects;
    };
}

#endif //EPDDL_OBJECTS_DECL_AST_H
