# MIT License
#
# Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

#
# Main plank executable
#
set(
    PLANK_FRONTEND_SRC
    printer/formula_printer.cpp
    printer/specification_printer.cpp
    printer/cli_data_printer.cpp
    cli/commands/cd.cpp
    cli/commands/parse.cpp
    cli/commands/version.cpp
    cli/commands/script.cpp
    cli/commands/pwd.cpp
    cli/commands/state.cpp
    cli/commands/validate.cpp
    cli/commands/ground.cpp
    cli/commands/export.cpp
    cli/commands/formula.cpp
    cli/commands/show.cpp
    cli/commands/clear.cpp
    cli/commands/task.cpp
    cli/commands/load.cpp
    cli/commands/ls.cpp
    cli/cli_manager.cpp
    main.cpp
)

set(
    PLANK_FRONTEND_HEADERS
    ../../../include/frontend/plank/printer/specification_printer.h
    ../../../include/frontend/plank/printer/cli_data_printer.h
    ../../../include/frontend/plank/printer/graphviz_printer.h
    ../../../include/frontend/plank/printer/formula_printer.h
    ../../../include/frontend/plank/utils/json_parser.h
    ../../../include/frontend/plank/cli/cli_names.h
    ../../../include/frontend/plank/cli/cli_manager.h
    ../../../include/frontend/plank/cli/commands/clear.h
    ../../../include/frontend/plank/cli/commands/pwd.h
    ../../../include/frontend/plank/cli/commands/formula.h
    ../../../include/frontend/plank/cli/commands/task.h
    ../../../include/frontend/plank/cli/commands/version.h
    ../../../include/frontend/plank/cli/commands/export.h
    ../../../include/frontend/plank/cli/commands/script.h
    ../../../include/frontend/plank/cli/commands/cd.h
    ../../../include/frontend/plank/cli/commands/load.h
    ../../../include/frontend/plank/cli/commands/parse.h
    ../../../include/frontend/plank/cli/commands/validate.h
    ../../../include/frontend/plank/cli/commands/show.h
    ../../../include/frontend/plank/cli/commands/ls.h
    ../../../include/frontend/plank/cli/commands/ground.h
    ../../../include/frontend/plank/cli/commands/state.h
    ../../../include/frontend/plank/cli/data/cli_data.h
    ../../../include/frontend/plank/cli/data/cli_task_data.h
    ../../../include/frontend/plank/cli/data/cli_data_loader.h
    ../../../include/frontend/plank/cli/cli_headers.h
    ../../../include/frontend/plank/cli/cli_types.h
    ../../../include/frontend/plank/cli/cli_utils.h
)

add_executable(plank_frontend ${PLANK_FRONTEND_SRC} ${PLANK_FRONTEND_HEADERS})

target_compile_features(plank_frontend PRIVATE cxx_std_17)
target_include_directories(plank_frontend PRIVATE ../../include/frontend/plank)
target_link_libraries(plank_frontend PRIVATE epddl_lib del_lib)

#target_enable_warnings(plank_frontend)
target_code_coverage(plank_frontend)
add_sanitizers(plank_frontend)

set_property(TARGET plank_frontend PROPERTY OUTPUT_NAME plank)
set_property(TARGET plank_frontend PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

install(TARGETS plank_frontend RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
