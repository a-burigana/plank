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
#include <memory>
#include <string>

using namespace epddl;

TEST_CASE("Basic lexing operations") {
    auto err_manager = std::make_shared<error_manager>();

    SECTION("Good identifiers") {
        for (const std::string &name : {
            "a",
            "_a",
            "_a--v-af24v5ad25-v36A4S6343D22A3-C-VA--"
        }) {
            lexer l{name, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<ast_token::identifier>());
        }
    }

    SECTION("Bad identifiers") {
        for (const std::string &name : {
            "2a",
            "-a"
        }) {
            lexer l{name, err_manager, false};

            try {
                l.get_next_token();
            } catch (EPDDLException &e) {
                REQUIRE(e.get_error_type() == error_type::invalid_token);
            }
        }
    }

    SECTION("Good variables") {
        for (const std::string &name : {
            "?a",
            "?_a",
            "?_a--v-af24v5ad25-v36A4S6343D22A3-C-VA--"
        }) {
            lexer l{name, err_manager, false};
            token_ptr tok = l.get_next_token();

            REQUIRE(tok->has_type<ast_token::variable>());
        }
    }

    SECTION("Bad variables") {
        for (const std::string &name : {
            "?2a",
            "?-a"
        }) {
            lexer l{name, err_manager, false};

            try {
                l.get_next_token();
            } catch (EPDDLException &e) {
                REQUIRE(e.get_error_type() == error_type::invalid_token);
            }
        }
    }
}
