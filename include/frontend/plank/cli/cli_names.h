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

#ifndef PLANK_CLI_NAMES_H
#define PLANK_CLI_NAMES_H

#define PLANK_VERSION              "1.0"
#define PLANK_NAME                 "plank"
#define PLANK_TAGLINE              "The DEL-based epistemic planning toolkit."
#define PLANK_LOGO_ASCII           "[===]"
#define PLANK_DIR_PATH             ".plank"
#define PLANK_HISTORY_FILENAME     ".history"
#define PLANK_SESSION_FILENAME     ".last_session.json"

#define PLANK_CMD_CD               "cd"
#define PLANK_CMD_CLEAR            "clear"
#define PLANK_CMD_EXPORT           "export"
#define PLANK_CMD_FORMULA          "formula"
#define PLANK_CMD_GROUND           "ground"
#define PLANK_CMD_HELP             "help"
#define PLANK_CMD_HISTORY          "history"
#define PLANK_CMD_LOAD             "load"
#define PLANK_CMD_LS               "ls"
#define PLANK_CMD_PARSE            "parse"
#define PLANK_CMD_PWD              "pwd"
#define PLANK_CMD_QUIT             "quit"
#define PLANK_CMD_SCRIPT           "script"
#define PLANK_CMD_SHOW             "show"
#define PLANK_CMD_STATE            "state"
#define PLANK_CMD_TASK             "task"
#define PLANK_CMD_VALIDATE         "validate"
#define PLANK_CMD_VERSION          "version"


// clear sub-commands
#define PLANK_SUB_CMD_DOMAIN       "domain"
#define PLANK_SUB_CMD_FORMULAS     "formulas"
#define PLANK_SUB_CMD_LIBRARIES    "libraries"
#define PLANK_SUB_CMD_PROBLEM      "problem"
#define PLANK_SUB_CMD_STATES       "states"
#define PLANK_SUB_CMD_TASKS        "tasks"
#define PLANK_SUB_CMD_SPEC         "spec"
#define PLANK_SUB_CMD_SCRIPTS      "scripts"

// export sub-commands
#define PLANK_SUB_CMD_ACTION       "action"
#define PLANK_SUB_CMD_STATE        "state"
#define PLANK_SUB_CMD_TASK         "task"

#define PLANK_CMD_FLAG_ALL         "--all"
#define PLANK_CMD_FLAG_EPS         "--eps"
#define PLANK_CMD_FLAG_JPG         "--jpg"
#define PLANK_CMD_FLAG_PDF         "--pdf"
#define PLANK_CMD_FLAG_PNG         "--png"
#define PLANK_CMD_FLAG_PS          "--ps"
#define PLANK_CMD_FLAG_SVG         "--svg"

// formula sub-commands
#define PLANK_SUB_CMD_ADD          "add"
#define PLANK_SUB_CMD_ADD_GOAL     "add-goal"
#define PLANK_SUB_CMD_COPY         "copy"
#define PLANK_SUB_CMD_REMOVE       "remove"
#define PLANK_SUB_CMD_RENAME       "rename"

// load sub-commands
#define PLANK_SUB_CMD_DOMAIN       "domain"
#define PLANK_SUB_CMD_LIBRARY      "library"
#define PLANK_SUB_CMD_PROBLEM      "problem"
#define PLANK_SUB_CMD_SPEC         "spec"

// script sub-commands
#define PLANK_SUB_CMD_ADD          "add"
#define PLANK_SUB_CMD_REMOVE       "remove"
#define PLANK_SUB_CMD_RENAME       "rename"
#define PLANK_SUB_CMD_RUN          "run"

// show sub-commands
#define PLANK_SUB_CMD_ACTIONS      "actions"
#define PLANK_SUB_CMD_AGENTS       "agents"
#define PLANK_SUB_CMD_AGENT_GROUPS "agent-groups"
#define PLANK_SUB_CMD_ENTITIES     "entities"
#define PLANK_SUB_CMD_FORMULAS     "formulas"
#define PLANK_SUB_CMD_OBJECTS      "objects"
#define PLANK_SUB_CMD_PREDICATES   "predicates"
#define PLANK_SUB_CMD_SCRIPTS      "scripts"
#define PLANK_SUB_CMD_STATES       "states"
#define PLANK_SUB_CMD_TASKS        "tasks"
#define PLANK_SUB_CMD_TYPES        "types"

// state sub-commands
#define PLANK_SUB_CMD_ADD_INIT     "add-init"
#define PLANK_SUB_CMD_APPLICABLE   "applicable"
#define PLANK_SUB_CMD_CHECK        "check"
#define PLANK_SUB_CMD_CONTRACT     "contract"
#define PLANK_SUB_CMD_COPY         "copy"
#define PLANK_SUB_CMD_REMOVE       "remove"
#define PLANK_SUB_CMD_RENAME       "rename"
#define PLANK_SUB_CMD_UPDATE       "update"

// task sub-commands
#define PLANK_SUB_CMD_ADD          "add"
#define PLANK_SUB_CMD_CLOSE        "close"
#define PLANK_SUB_CMD_COPY         "copy"
#define PLANK_SUB_CMD_OPEN         "open"
#define PLANK_SUB_CMD_REMOVE       "remove"
#define PLANK_SUB_CMD_RENAME       "rename"
#define PLANK_SUB_CMD_SAVE         "save"
#define PLANK_SUB_CMD_SWITCH       "switch"

#endif //PLANK_CLI_NAMES_H
