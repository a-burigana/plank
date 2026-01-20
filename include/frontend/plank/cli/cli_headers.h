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

#ifndef PLANK_CLI_HEADERS_H
#define PLANK_CLI_HEADERS_H

#include "cli_names.h"
#include "cli_utils.h"
#include "../../../../external/interactive-cli/cli.h"
#include "../../../../external/interactive-cli/loopscheduler.h"
#include "../../../../external/interactive-cli/clilocalsession.h"
#include "../../../../external/interactive-cli/filehistorystorage.h"

#include "commands/cd.h"
#include "commands/clear.h"
#include "commands/export.h"
#include "commands/formula.h"
#include "commands/ground.h"
#include "commands/load.h"
#include "commands/ls.h"
#include "commands/parse.h"
#include "commands/pwd.h"
#include "commands/script.h"
#include "commands/show.h"
#include "commands/state.h"
#include "commands/task.h"
#include "commands/validate.h"
#include "commands/version.h"

#endif //PLANK_CLI_HEADERS_H
