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

#ifndef EPDDL_CONTEXT_H
#define EPDDL_CONTEXT_H

#include "context/context_utils.h"
#include "context/types_context.h"
#include "context/entities_context.h"
#include "context/predicates_context.h"
#include "context/events_context.h"
#include "context/actions_context.h"
#include "context/action_types_context.h"
#include "context/requirements_context.h"

namespace epddl::type_checker {
    struct context {
        types_context types;
        entities_context entities;
        predicates_context predicates;
        events_context events;
        actions_context actions;
        action_types_context action_types;
        requirements_context requirements;
    };
}

#endif //EPDDL_CONTEXT_H
