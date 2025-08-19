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

#ifndef EPDDL_OBS_CONDITIONS_AST_H
#define EPDDL_OBS_CONDITIONS_AST_H

#include "../../ast_node.h"
#include "../../tokens/tokens_ast.h"
#include "../../common/formulas_ast.h"
#include <list>
#include <memory>
#include <variant>

namespace epddl::ast {
    class always_obs_condition;
    class if_then_else_obs_condition;
    class if_obs_condition;
    class else_if_obs_condition;
    class else_obs_condition;
    class forall_obs_condition;
    class default_obs_condition;

    using always_obs_cond_ptr       = std::shared_ptr<always_obs_condition>;
    using if_then_else_obs_cond_ptr = std::shared_ptr<if_then_else_obs_condition>;
    using if_obs_cond_ptr           = std::shared_ptr<if_obs_condition>;
    using else_if_obs_cond_ptr      = std::shared_ptr<else_if_obs_condition>;
    using else_obs_cond_ptr         = std::shared_ptr<else_obs_condition>;
    using forall_obs_cond_ptr       = std::shared_ptr<forall_obs_condition>;
    using default_obs_cond_ptr      = std::shared_ptr<default_obs_condition>;

    using observing_agent           = std::variant<identifier_ptr, variable_ptr, agent_group_token::all>;
//    using simple_obs_cond           = std::variant<always_obs_cond_ptr, if_then_else_obs_cond_ptr>;
    using single_obs_cond           = std::variant<always_obs_cond_ptr, if_then_else_obs_cond_ptr, forall_obs_cond_ptr, default_obs_cond_ptr>;
    using else_if_obs_cond_list     = std::list<else_if_obs_cond_ptr>;
    using obs_cond_list             = std::list<single_obs_cond>;
    using obs_cond                  = std::variant<single_obs_cond, obs_cond_list>;

    class always_obs_condition : public ast_node {
    public:
        explicit always_obs_condition(observing_agent agent, identifier_ptr obs_group) :
                m_agent{std::move(agent)},
                m_obs_group{std::move(obs_group)} {}

    private:
        const observing_agent m_agent;
        const identifier_ptr m_obs_group;
    };

    class if_then_else_obs_condition : public ast_node {
    public:
        explicit if_then_else_obs_condition(if_obs_cond_ptr if_cond, else_if_obs_cond_list else_if_conds, std::optional<else_obs_cond_ptr> else_cond) :
                m_if_cond{std::move(if_cond)},
                m_else_if_conds{std::move(else_if_conds)},
                m_else_cond{std::move(else_cond)} {}

    private:
        const if_obs_cond_ptr m_if_cond;
        const else_if_obs_cond_list m_else_if_conds;
        const std::optional<else_obs_cond_ptr> m_else_cond;
    };

    class if_obs_condition : public ast_node {
    public:
        explicit if_obs_condition(formula_ptr cond, observing_agent agent, identifier_ptr obs_group) :
                m_cond{std::move(cond)},
                m_agent{std::move(agent)},
                m_obs_group{std::move(obs_group)} {}

    private:
        const observing_agent m_agent;
        const identifier_ptr m_obs_group;
        const formula_ptr m_cond;
    };

    class else_if_obs_condition : if_obs_condition {
    public:
        explicit else_if_obs_condition(formula_ptr cond, observing_agent agent, identifier_ptr obs_group) :
                if_obs_condition(std::move(cond), std::move(agent), std::move(obs_group)) {}
    };

    class else_obs_condition : public ast_node {
    public:
        explicit else_obs_condition(observing_agent agent, identifier_ptr obs_group) :
                m_agent{std::move(agent)},
                m_obs_group{std::move(obs_group)} {}

    private:
        const observing_agent m_agent;
        const identifier_ptr m_obs_group;
    };

    class forall_obs_condition : public ast_node {
    public:
        explicit forall_obs_condition(int_list_comprehension_ptr params, obs_cond obs_condition) :
                m_params{std::move(params)},
                m_obs_condition{std::move(obs_condition)} {}

    private:
        const int_list_comprehension_ptr m_params;
        const obs_cond m_obs_condition;
    };

    class default_obs_condition : public ast_node {
    public:
        explicit default_obs_condition(identifier_ptr obs_group) :
                m_obs_group{std::move(obs_group)} {}

    private:
        const identifier_ptr m_obs_group;
    };
}

#endif //EPDDL_OBS_CONDITIONS_AST_H
