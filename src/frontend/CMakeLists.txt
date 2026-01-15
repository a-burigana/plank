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
    plank/cli_commands/cd.cpp
    plank/cli_commands/parse.cpp
    plank/cli_commands/version.cpp
    plank/cli_commands/script.cpp
    plank/cli_commands/pwd.cpp
    plank/cli_commands/state.cpp
    plank/cli_commands/validate.cpp
    plank/cli_commands/ground.cpp
    plank/cli_commands/export.cpp
    plank/cli_commands/formula.cpp
    plank/cli_commands/show.cpp
    plank/cli_commands/clear.cpp
    plank/cli_commands/task.cpp
    plank/cli_commands/load.cpp
    plank/cli_commands/ls.cpp
    plank/cli_manager.cpp
    main.cpp
)

set(
    PLANK_FRONTEND_HEADERS
    ../../include/frontend/printer/specification_printer.h
    ../../include/frontend/printer/cli_data_printer.h
    ../../include/frontend/printer/graphviz_printer.h
    ../../include/frontend/printer/formula_printer.h
    ../../include/frontend/utils/json_parser.h
    ../../include/frontend/plank/cli_names.h
    ../../include/frontend/plank/cli_manager.h
    ../../include/frontend/plank/cli_commands/clear.h
    ../../include/frontend/plank/cli_commands/pwd.h
    ../../include/frontend/plank/cli_commands/formula.h
    ../../include/frontend/plank/cli_commands/task.h
    ../../include/frontend/plank/cli_commands/version.h
    ../../include/frontend/plank/cli_commands/export.h
    ../../include/frontend/plank/cli_commands/script.h
    ../../include/frontend/plank/cli_commands/cd.h
    ../../include/frontend/plank/cli_commands/load.h
    ../../include/frontend/plank/cli_commands/parse.h
    ../../include/frontend/plank/cli_commands/validate.h
    ../../include/frontend/plank/cli_commands/show.h
    ../../include/frontend/plank/cli_commands/ls.h
    ../../include/frontend/plank/cli_commands/ground.h
    ../../include/frontend/plank/cli_commands/state.h
    ../../include/frontend/plank/cli_data/cli_data.h
    ../../include/frontend/plank/cli_data/cli_task_data.h
    ../../include/frontend/plank/cli_data/cli_data_loader.h
    ../../include/frontend/plank/cli_headers.h
    ../../include/frontend/plank/cli_types.h
    ../../include/frontend/plank/cli_utils.h
)

add_executable(plank_frontend ${PLANK_FRONTEND_SRC} ${PLANK_FRONTEND_HEADERS})

target_compile_features(plank_frontend PRIVATE cxx_std_17)
target_include_directories(plank_frontend PRIVATE ../../include/frontend)
target_link_libraries(plank_frontend PRIVATE epddl_lib)

#target_enable_warnings(plank_frontend)
target_code_coverage(plank_frontend)
add_sanitizers(plank_frontend)

set_property(TARGET plank_frontend PROPERTY OUTPUT_NAME plank)
set_property(TARGET plank_frontend PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

install(TARGETS plank_frontend RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
