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
#include "../../include/lib/error-manager/error_manager.h"
#include "../../include/lib/lexer/lexer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>

using namespace epddl;

TEST_CASE("Basic lexing operations") {
    INFO("Basic lexing operations");

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
}
