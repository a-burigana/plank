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
#include "../../external/interactive-cli/cli.h"
#include "../../external/interactive-cli/loopscheduler.h"
#include "../../external/interactive-cli/clilocalsession.h"

#include "cli_commands/cd.h"
#include "cli_commands/clear.h"
#include "cli_commands/export.h"
#include "cli_commands/formula.h"
#include "cli_commands/ground.h"
#include "cli_commands/load.h"
#include "cli_commands/ls.h"
#include "cli_commands/parse.h"
#include "cli_commands/pwd.h"
#include "cli_commands/script.h"
#include "cli_commands/show.h"
#include "cli_commands/state.h"
#include "cli_commands/task.h"
#include "cli_commands/validate.h"
#include "cli_commands/version.h"

#endif //PLANK_CLI_HEADERS_H
