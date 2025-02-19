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

#ifndef EPDDL_REQUIREMENTS_DEF_H
#define EPDDL_REQUIREMENTS_DEF_H

#define epddl_requirement_keywords \
    epddl_req_keyword(":common-knowledge")          \
    epddl_req_keyword(":conditional-effects")       \
    epddl_req_keyword(":del")                       \
    epddl_req_keyword(":disjunctive-preconditions") \
    epddl_req_keyword(":equality")                  \
    epddl_req_keyword(":existential-preconditions") \
    epddl_req_keyword(":finitary-S5-theory")        \
    epddl_req_keyword(":full-del")                  \
    epddl_req_keyword(":knowing-whether")           \
    epddl_req_keyword(":modal-postconditions")      \
    epddl_req_keyword(":modal-preconditions")       \
    epddl_req_keyword(":multi-pointed-models")      \
    epddl_req_keyword(":negative-preconditions")    \
    epddl_req_keyword(":observability-conditions")  \
    epddl_req_keyword(":ontic-actions")             \
    epddl_req_keyword(":pal")                       \
    epddl_req_keyword(":quantified-preconditions")  \
    epddl_req_keyword(":static-common-knowledge")   \
    epddl_req_keyword(":static-predicates")         \
    epddl_req_keyword(":typing")                    \
    epddl_req_keyword(":universal-preconditions")

#define epddl_val_requirement_keywords \
    epddl_req_keyword(":max-modal-depth")          \
    epddl_req_keyword(":max-postconditions-depth") \
    epddl_req_keyword(":max-preconditions-depth")

#endif //EPDDL_REQUIREMENTS_DEF_H
