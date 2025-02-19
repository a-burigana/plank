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

#ifndef EPDDL_ACTION_DECL_AST_H
#define EPDDL_ACTION_DECL_AST_H

#include "../../ast_node.h"
#include "../../tokens/tokens_ast.h"
#include "../../common/parameters_ast.h"
#include "action_signatures_ast.h"
#include "obs_conditions_ast.h"
#include "action_preconditions_ast.h"
#include "action_postconditions_ast.h"

namespace epddl::ast {
    class action;
    using action_ptr = std::unique_ptr<ast::action>;

    class action : public ast_node {
    public:
        explicit action(identifier_ptr name, parameters_ptr params, action_signature_ptr signature,
                        event_precondition_list preconditions, event_postconditions_list postconditions,
                        std::optional<obs_cond> obs_conditions) :
                m_name{std::move(name)},
                m_params{std::move(params)},
                m_signature{std::move(signature)},
                m_preconditions{std::move(preconditions)},
                m_postconditions{std::move(postconditions)},
                m_obs_conditions{std::move(obs_conditions)} {}

    private:
        const identifier_ptr m_name;
        const parameters_ptr m_params;
        const action_signature_ptr m_signature;
        const event_precondition_list m_preconditions;
        const event_postconditions_list m_postconditions;
        const std::optional<obs_cond> m_obs_conditions;
    };
}

#endif //EPDDL_ACTION_DECL_AST_H
