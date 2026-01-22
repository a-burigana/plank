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

#include <catch2/catch_all.hpp>
#include "../../../../include/lib/epddl/error-manager/error_manager.h"
#include "../../../../include/lib/epddl/lexer/lexer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>

using namespace epddl;

TEST_CASE("Lexer tests") {
    INFO("Lexer tests");

    auto err_manager = std::make_shared<error_manager>();
    // Also correctly tested with max_id_size = 3
    // We leave it at 2 because otherwise it takes too much time to check all combinations
    size_t max_id_size = 2;

    std::vector<char> good_first_id_chars = {
            '_', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
            'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
            'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
            'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
            'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    std::vector<char> bad_first_id_chars = {
            '0', '1', '2', '3', '4', '5', '6', '7', '8',
            '9', '-'};

    std::vector<char> good_id_chars = {
            '_', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
            'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
            'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
            'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
            'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0',
            '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'};

    std::function<void(
            std::deque<std::string> &,
            size_t,
            const std::string &prefix)>
        compute_all_ids =
        [&](std::deque<std::string> &ids,
            size_t length, const std::string &prefix) -> void {
        if (length == 0)
            ids.emplace_back(prefix);
        else
            for (char c : good_id_chars)
                compute_all_ids(ids, length-1, prefix + c);
    };

    std::deque<std::string> suffixes;
    compute_all_ids(suffixes, max_id_size-1, "");

    SECTION("Good identifiers") {
        INFO("Good identifiers");

        for (char fc : good_first_id_chars)
            for (const std::string &suffix : suffixes) {
                std::string id = std::string{fc} + suffix;
                lexer l{id, err_manager, false};
                token_ptr tok = l.get_next_token();
                bool is_valid_keyword = l.get_dictionary().is_valid_keyword(tok->get_lexeme());

                if (not is_valid_keyword)
                    REQUIRE(tok->has_type<ast_token::identifier>());
            }
    }

    SECTION("Bad identifiers") {
        INFO("Bad identifiers");

        for (char fc : bad_first_id_chars)
            for (const std::string &suffix : suffixes) {
                std::string id = std::string{fc} + suffix;
                lexer l{id, err_manager, false};

                try {
                    l.get_next_token();
                } catch (EPDDLException &e) {
                    REQUIRE(e.get_error_type() == error_type::invalid_token);
                }
            }
    }

    SECTION("Good variables") {
        INFO("Good variables");

        for (char fc : good_first_id_chars)
            for (const std::string &suffix : suffixes) {
                std::string var = "?" + std::string{fc} + suffix;
                lexer l{var, err_manager, false};
                token_ptr tok = l.get_next_token();

                REQUIRE(tok->has_type<ast_token::variable>());
            }
    }

    SECTION("Bad variables") {
        INFO("Bad variables");

        for (char fc : bad_first_id_chars)
            for (const std::string &suffix : suffixes) {
                std::string var = "?" + std::string{fc} + suffix;
                lexer l{var, err_manager, false};

                try {
                    l.get_next_token();
                } catch (EPDDLException &e) {
                    REQUIRE(e.get_error_type() == error_type::invalid_token);
                }
            }
    }

    SECTION("End of file") {
        INFO("End of file");

        lexer l{"", err_manager, false};
        token_ptr tok = l.get_next_token();

        REQUIRE(tok->has_type<special_token::eof>());
    }

    SECTION("Good punctuation") {
        INFO("Good punctuation");

        SECTION("lpar") {
            lexer l{"(", err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<punctuation_token::lpar>());
        }

        SECTION("rpar") {
            lexer l{")", err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<punctuation_token::rpar>());
        }

        SECTION("lbrack") {
            lexer l{"[", err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<punctuation_token::lbrack>());
        }

        SECTION("rbrack") {
            lexer l{"]", err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<punctuation_token::rbrack>());
        }

        SECTION("langle") {
            lexer l{"<", err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<punctuation_token::langle>());
        }

        SECTION("rangle") {
            lexer l{">", err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<punctuation_token::rangle>());
        }

        SECTION("dash") {
            lexer l{"-", err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<punctuation_token::dash>());
        }

        SECTION("eq") {
            lexer l{"=", err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<punctuation_token::eq>());
        }

        SECTION("neq") {
            lexer l{"/=", err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<punctuation_token::neq>());
        }
    }

    SECTION("Bad punctuation") {
        INFO("Bad punctuation");

        std::deque<std::string> bad_punctuation_tokens = {
            ".", ",", "'", "/", "\"", "\\", "{", "}", "§", "±",
            "!", "@", "#", "$", "%", "^", "&", "*", "+", "`", "~"
        };

        for (const std::string &punct : bad_punctuation_tokens) {
            lexer l{punct, err_manager, false};

            try {
                l.get_next_token();
            } catch (EPDDLException &e) {
                REQUIRE(e.get_error_type() == error_type::invalid_token);
            }
        }
    }

    SECTION("Keywords") {
        SECTION(std::string{keyword_token::action::name}) {
            INFO(std::string{keyword_token::action::name});

            lexer l{std::string{keyword_token::action::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::action>());
        }

        SECTION(std::string{keyword_token::act_type::name}) {
            INFO(std::string{keyword_token::act_type::name});

            lexer l{std::string{keyword_token::act_type::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::act_type>());
        }

        SECTION(std::string{keyword_token::agents::name}) {
            INFO(std::string{keyword_token::agents::name});

            lexer l{std::string{keyword_token::agents::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::agents>());
        }

        SECTION(std::string{keyword_token::agent_groups::name}) {
            INFO(std::string{keyword_token::agent_groups::name});

            lexer l{std::string{keyword_token::agent_groups::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::agent_groups>());
        }

        SECTION(std::string{keyword_token::conditions::name}) {
            INFO(std::string{keyword_token::conditions::name});

            lexer l{std::string{keyword_token::conditions::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::conditions>());
        }

        SECTION(std::string{keyword_token::constants::name}) {
            INFO(std::string{keyword_token::constants::name});

            lexer l{std::string{keyword_token::constants::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::constants>());
        }

        SECTION(std::string{keyword_token::define::name}) {
            INFO(std::string{keyword_token::define::name});

            lexer l{std::string{keyword_token::define::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::define>());
        }

        SECTION(std::string{keyword_token::designated::name}) {
            INFO(std::string{keyword_token::designated::name});

            lexer l{std::string{keyword_token::designated::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::designated>());
        }

        SECTION(std::string{keyword_token::domain::name}) {
            INFO(std::string{keyword_token::domain::name});

            lexer l{std::string{keyword_token::domain::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::domain>());
        }

        SECTION(std::string{keyword_token::domain_libs::name}) {
            INFO(std::string{keyword_token::domain_libs::name});

            lexer l{std::string{keyword_token::domain_libs::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::domain_libs>());
        }

        SECTION(std::string{keyword_token::effects::name}) {
            INFO(std::string{keyword_token::effects::name});

            lexer l{std::string{keyword_token::effects::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::effects>());
        }

        SECTION(std::string{keyword_token::either::name}) {
            INFO(std::string{keyword_token::either::name});

            lexer l{std::string{keyword_token::either::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::either>());
        }

        SECTION(std::string{keyword_token::event::name}) {
            INFO(std::string{keyword_token::event::name});

            lexer l{std::string{keyword_token::event::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::event>());
        }

        SECTION(std::string{keyword_token::events::name}) {
            INFO(std::string{keyword_token::events::name});

            lexer l{std::string{keyword_token::events::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::events>());
        }

        SECTION(std::string{keyword_token::fact::name}) {
            INFO(std::string{keyword_token::fact::name});

            lexer l{std::string{keyword_token::fact::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::fact>());
        }

        SECTION(std::string{keyword_token::facts_init::name}) {
            INFO(std::string{keyword_token::facts_init::name});

            lexer l{std::string{keyword_token::facts_init::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::facts_init>());
        }

        SECTION(std::string{keyword_token::goal::name}) {
            INFO(std::string{keyword_token::goal::name});

            lexer l{std::string{keyword_token::goal::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::goal>());
        }

        SECTION(std::string{keyword_token::init::name}) {
            INFO(std::string{keyword_token::init::name});

            lexer l{std::string{keyword_token::init::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::init>());
        }

        SECTION(std::string{keyword_token::labels::name}) {
            INFO(std::string{keyword_token::labels::name});

            lexer l{std::string{keyword_token::labels::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::labels>());
        }

        SECTION(std::string{keyword_token::library::name}) {
            INFO(std::string{keyword_token::library::name});

            lexer l{std::string{keyword_token::library::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::library>());
        }

        SECTION(std::string{keyword_token::list_and::name}) {
            INFO(std::string{keyword_token::list_and::name});

            lexer l{std::string{keyword_token::list_and::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::list_and>());
        }

        SECTION(std::string{keyword_token::list_forall::name}) {
            INFO(std::string{keyword_token::list_forall::name});

            lexer l{std::string{keyword_token::list_forall::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::list_forall>());
        }

        SECTION(std::string{keyword_token::objects::name}) {
            INFO(std::string{keyword_token::objects::name});

            lexer l{std::string{keyword_token::objects::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::objects>());
        }

        SECTION(std::string{keyword_token::obs_conditions::name}) {
            INFO(std::string{keyword_token::obs_conditions::name});

            lexer l{std::string{keyword_token::obs_conditions::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::obs_conditions>());
        }

        SECTION(std::string{keyword_token::obs_types::name}) {
            INFO(std::string{keyword_token::obs_types::name});

            lexer l{std::string{keyword_token::obs_types::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::obs_types>());
        }

        SECTION(std::string{keyword_token::parameters::name}) {
            INFO(std::string{keyword_token::parameters::name});

            lexer l{std::string{keyword_token::parameters::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::parameters>());
        }

        SECTION(std::string{keyword_token::precondition::name}) {
            INFO(std::string{keyword_token::precondition::name});

            lexer l{std::string{keyword_token::precondition::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::precondition>());
        }

        SECTION(std::string{keyword_token::predicates::name}) {
            INFO(std::string{keyword_token::predicates::name});

            lexer l{std::string{keyword_token::predicates::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::predicates>());
        }

        SECTION(std::string{keyword_token::problem::name}) {
            INFO(std::string{keyword_token::problem::name});

            lexer l{std::string{keyword_token::problem::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::problem>());
        }

        SECTION(std::string{keyword_token::prob_domain::name}) {
            INFO(std::string{keyword_token::prob_domain::name});

            lexer l{std::string{keyword_token::prob_domain::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::prob_domain>());
        }

        SECTION(std::string{keyword_token::relations::name}) {
            INFO(std::string{keyword_token::relations::name});

            lexer l{std::string{keyword_token::relations::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::relations>());
        }

        SECTION(std::string{keyword_token::requirements::name}) {
            INFO(std::string{keyword_token::requirements::name});

            lexer l{std::string{keyword_token::requirements::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::requirements>());
        }

        SECTION(std::string{keyword_token::state::name}) {
            INFO(std::string{keyword_token::state::name});

            lexer l{std::string{keyword_token::state::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::state>());
        }

        SECTION(std::string{keyword_token::state_name::name}) {
            INFO(std::string{keyword_token::state_name::name});

            lexer l{std::string{keyword_token::state_name::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::state_name>());
        }

        SECTION(std::string{keyword_token::types::name}) {
            INFO(std::string{keyword_token::types::name});

            lexer l{std::string{keyword_token::types::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::types>());
        }

        SECTION(std::string{keyword_token::worlds::name}) {
            INFO(std::string{keyword_token::worlds::name});

            lexer l{std::string{keyword_token::worlds::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<keyword_token::worlds>());
        }
    }

    SECTION("Propositional connectives") {
        SECTION(std::string{connective_token::conjunction::name}) {
            INFO(std::string{connective_token::conjunction::name});

            lexer l{std::string{connective_token::conjunction::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<connective_token::conjunction>());
        }

        SECTION(std::string{connective_token::disjunction::name}) {
            INFO(std::string{connective_token::disjunction::name});

            lexer l{std::string{connective_token::disjunction::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<connective_token::disjunction>());
        }

        SECTION(std::string{connective_token::implication::name}) {
            INFO(std::string{connective_token::implication::name});

            lexer l{std::string{connective_token::implication::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<connective_token::implication>());
        }

        SECTION(std::string{connective_token::negation::name}) {
            INFO(std::string{connective_token::negation::name});

            lexer l{std::string{connective_token::negation::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<connective_token::negation>());
        }
    }

    SECTION("Propositional quantifiers") {
        SECTION(std::string{quantifier_token::exists::name}) {
            INFO(std::string{quantifier_token::exists::name});

            lexer l{std::string{quantifier_token::exists::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<quantifier_token::exists>());
        }

        SECTION(std::string{quantifier_token::forall::name}) {
            INFO(std::string{quantifier_token::forall::name});

            lexer l{std::string{quantifier_token::forall::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<quantifier_token::forall>());
        }
    }

    SECTION("Modalities") {
        SECTION(std::string{modality_token::ck::name}) {
            INFO(std::string{modality_token::ck::name});

            lexer l{std::string{modality_token::ck::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<modality_token::ck>());
        }

        SECTION(std::string{modality_token::kw::name}) {
            INFO(std::string{modality_token::kw::name});

            lexer l{std::string{modality_token::kw::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<modality_token::kw>());
        }
    }

    SECTION("Atomic formulas") {
        SECTION(std::string{atomic_formula_token::bot::name}) {
            INFO(std::string{atomic_formula_token::bot::name});

            lexer l{std::string{atomic_formula_token::bot::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<atomic_formula_token::bot>());
        }

        SECTION(std::string{atomic_formula_token::top::name}) {
            INFO(std::string{atomic_formula_token::top::name});

            lexer l{std::string{atomic_formula_token::top::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<atomic_formula_token::top>());
        }
    }

    SECTION("Postconditions connectives") {
        SECTION(std::string{post_connective_token::iff::name}) {
            INFO(std::string{post_connective_token::iff::name});

            lexer l{std::string{post_connective_token::iff::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<post_connective_token::iff>());
        }

        SECTION(std::string{post_connective_token::when::name}) {
            INFO(std::string{post_connective_token::when::name});

            lexer l{std::string{post_connective_token::when::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<post_connective_token::when>());
        }
    }

    SECTION("Observability conditions keywords") {
        SECTION(std::string{observability_token::if_cond::name}) {
            INFO(std::string{observability_token::if_cond::name});

            lexer l{std::string{observability_token::if_cond::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<observability_token::if_cond>());
        }

        SECTION(std::string{observability_token::else_if_cond::name}) {
            INFO(std::string{observability_token::else_if_cond::name});

            lexer l{std::string{observability_token::else_if_cond::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<observability_token::else_if_cond>());
        }

        SECTION(std::string{observability_token::else_cond::name}) {
            INFO(std::string{observability_token::else_cond::name});

            lexer l{std::string{observability_token::else_cond::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<observability_token::else_cond>());
        }

        SECTION(std::string{observability_token::default_cond::name}) {
            INFO(std::string{observability_token::default_cond::name});

            lexer l{std::string{observability_token::default_cond::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<observability_token::default_cond>());
        }
    }

    SECTION("Agent groups") {
        SECTION(std::string{agent_group_token::all::name}) {
            INFO(std::string{agent_group_token::all::name});

            lexer l{std::string{agent_group_token::all::lexeme}, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<agent_group_token::all>());
        }
    }

    SECTION("Event conditions") {
        SECTION(std::string{event_condition_token::non_trivial_pre::name}) {
            INFO(std::string{event_condition_token::non_trivial_pre::name});

            lexer l{std::string{event_condition_token::non_trivial_pre::lexeme}, err_manager, false};
            l.set_expected_keyword_type(keyword_type::event_condition);

            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<event_condition_token::non_trivial_pre>());
        }

        SECTION(std::string{event_condition_token::non_trivial_post::name}) {
            INFO(std::string{event_condition_token::non_trivial_post::name});

            lexer l{std::string{event_condition_token::non_trivial_post::lexeme}, err_manager, false};
            l.set_expected_keyword_type(keyword_type::event_condition);

            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<event_condition_token::non_trivial_post>());
        }

        SECTION(std::string{event_condition_token::non_trivial_event::name}) {
            INFO(std::string{event_condition_token::non_trivial_event::name});

            lexer l{std::string{event_condition_token::non_trivial_event::lexeme}, err_manager, false};
            l.set_expected_keyword_type(keyword_type::event_condition);

            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<event_condition_token::non_trivial_event>());
        }

        SECTION(std::string{event_condition_token::prop_pre::name}) {
            INFO(std::string{event_condition_token::prop_pre::name});

            lexer l{std::string{event_condition_token::prop_pre::lexeme}, err_manager, false};
            l.set_expected_keyword_type(keyword_type::event_condition);

            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<event_condition_token::prop_pre>());
        }

        SECTION(std::string{event_condition_token::prop_post::name}) {
            INFO(std::string{event_condition_token::prop_post::name});

            lexer l{std::string{event_condition_token::prop_post::lexeme}, err_manager, false};
            l.set_expected_keyword_type(keyword_type::event_condition);

            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<event_condition_token::prop_post>());
        }

        SECTION(std::string{event_condition_token::prop_event::name}) {
            INFO(std::string{event_condition_token::prop_event::name});

            lexer l{std::string{event_condition_token::prop_event::lexeme}, err_manager, false};
            l.set_expected_keyword_type(keyword_type::event_condition);

            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<event_condition_token::prop_event>());
        }

        SECTION(std::string{event_condition_token::trivial_pre::name}) {
            INFO(std::string{event_condition_token::trivial_pre::name});

            lexer l{std::string{event_condition_token::trivial_pre::lexeme}, err_manager, false};
            l.set_expected_keyword_type(keyword_type::event_condition);

            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<event_condition_token::trivial_pre>());
        }

        SECTION(std::string{event_condition_token::trivial_post::name}) {
            INFO(std::string{event_condition_token::trivial_post::name});

            lexer l{std::string{event_condition_token::trivial_post::lexeme}, err_manager, false};
            l.set_expected_keyword_type(keyword_type::event_condition);

            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<event_condition_token::trivial_post>());
        }

        SECTION(std::string{event_condition_token::trivial_event::name}) {
            INFO(std::string{event_condition_token::trivial_event::name});

            lexer l{std::string{event_condition_token::trivial_event::lexeme}, err_manager, false};
            l.set_expected_keyword_type(keyword_type::event_condition);

            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<event_condition_token::trivial_event>());
        }
    }

    SECTION("Requirements") {
        INFO("Requirements");

        std::vector<std::string> good_requirements = {
            ":agent-groups",
            ":common-knowledge",
            ":conditional-effects",
            ":del",
            ":disjunctive-formulas",
            ":disjunctive-goals",
            ":disjunctive-list-formulas",
            ":disjunctive-obs-conditions",
            ":disjunctive-postconditions",
            ":disjunctive-preconditions",
            ":equality",
            ":events-conditions",
            ":existential-formulas",
            ":existential-goals",
            ":existential-list-formulas",
            ":existential-obs-conditions",
            ":existential-postconditions",
            ":existential-preconditions",
            ":finitary-S5-theories",
            ":facts",
            ":general-formulas",
            ":general-frames",
            ":general-goals",
            ":general-list-formulas",
            ":general-obs-conditions",
            ":general-postconditions",
            ":general-preconditions",
            ":group-modalities",
            ":KD45-frames",
            ":knowing-whether",
            ":lists",
            ":list-comprehensions",
            ":modal-formulas",
            ":modal-goals",
            ":modal-obs-conditions",
            ":modal-postconditions",
            ":modal-preconditions",
            ":multi-pointed-models",
            ":negative-formulas",
            ":negative-goals",
            ":negative-list-formulas",
            ":negative-obs-conditions",
            ":negative-postconditions",
            ":negative-preconditions",
            ":ontic-actions",
            ":pal",
            ":partial-observability",
            ":quantified-formulas",
            ":quantified-goals",
            ":quantified-list-formulas",
            ":quantified-obs-conditions",
            ":quantified-postconditions",
            ":quantified-preconditions",
            ":static-common-knowledge",
            ":typing",
            ":universal-formulas",
            ":universal-goals",
            ":universal-list-formulas",
            ":universal-obs-conditions",
            ":universal-postconditions",
            ":universal-preconditions"
        };

        for (const std::string &req : good_requirements) {
            lexer l{req, err_manager, false};
            l.set_expected_keyword_type(keyword_type::requirement);

            token_ptr tok = l.get_next_token();

            if (not tok->has_type<ast_token::requirement>())
                std::cout << req << std::endl;

            REQUIRE(tok->has_type<ast_token::requirement>());
        }
    }
}
