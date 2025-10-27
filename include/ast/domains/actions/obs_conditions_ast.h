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
    class static_obs_condition;
    class if_then_else_obs_condition;
    class if_obs_condition;
    class else_if_obs_condition;
    class else_obs_condition;
    class default_obs_condition;

    using static_obs_cond_ptr       = std::shared_ptr<static_obs_condition>;
    using if_then_else_obs_cond_ptr = std::shared_ptr<if_then_else_obs_condition>;
    using if_obs_cond_ptr           = std::shared_ptr<if_obs_condition>;
    using else_if_obs_cond_ptr      = std::shared_ptr<else_if_obs_condition>;
    using else_obs_cond_ptr         = std::shared_ptr<else_obs_condition>;
    using default_obs_cond_ptr      = std::shared_ptr<default_obs_condition>;

    using obs_cond                  = std::variant<static_obs_cond_ptr, if_then_else_obs_cond_ptr, default_obs_cond_ptr>;
    using else_if_obs_cond_list     = std::list<else_if_obs_cond_ptr>;
    using obs_cond_list             = std::list<obs_cond>;

    class static_obs_condition : public ast_node {
    public:
        explicit static_obs_condition(info info, identifier_ptr obs_group, term agent);

        [[nodiscard]] const identifier_ptr &get_obs_group() const { return m_obs_group; }
        [[nodiscard]] const term &get_agent() const { return m_agent; }

    private:
        const identifier_ptr m_obs_group;
        const term m_agent;
    };

    class if_then_else_obs_condition : public ast_node {
    public:
        explicit if_then_else_obs_condition(info info, if_obs_cond_ptr if_cond, else_if_obs_cond_list else_if_conds,
                                            std::optional<else_obs_cond_ptr> else_cond);

        [[nodiscard]] const if_obs_cond_ptr &get_if_cond() const { return m_if_cond; }
        [[nodiscard]] const else_if_obs_cond_list &get_else_if_conds() const { return m_else_if_conds; }
        [[nodiscard]] const std::optional<else_obs_cond_ptr> &get_else_cond() const { return m_else_cond; }

    private:
        const if_obs_cond_ptr m_if_cond;
        const else_if_obs_cond_list m_else_if_conds;
        const std::optional<else_obs_cond_ptr> m_else_cond;
    };

    class if_obs_condition : public ast_node {
    public:
        explicit if_obs_condition(info info, formula_ptr cond, static_obs_cond_ptr obs_cond);

        [[nodiscard]] const formula_ptr &get_cond() const { return m_cond; }
        [[nodiscard]] const static_obs_cond_ptr &get_obs_cond() const { return m_obs_cond; }

    private:
        const formula_ptr m_cond;
        const static_obs_cond_ptr m_obs_cond;
    };

    class else_if_obs_condition : public if_obs_condition {
    public:
        explicit else_if_obs_condition(info info, formula_ptr cond, static_obs_cond_ptr obs_cond);
    };

    class else_obs_condition : public static_obs_condition {
    public:
        explicit else_obs_condition(info info, identifier_ptr obs_group, term agent);
    };

    class default_obs_condition : public ast_node {
    public:
        explicit default_obs_condition(info info, identifier_ptr obs_group) :
                ast_node{std::move(info)},
                m_obs_group{std::move(obs_group)} {}

        [[nodiscard]] const identifier_ptr &get_obs_group() const { return m_obs_group; }

    private:
        const identifier_ptr m_obs_group;
    };
}

#endif //EPDDL_OBS_CONDITIONS_AST_H
