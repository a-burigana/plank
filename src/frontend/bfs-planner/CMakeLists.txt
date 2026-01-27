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
# Main bfs_planner executable
#
set(
    BFS_PLANNER_SRC
    search/search_space.cpp
    search/planner.cpp
    utils/spec_paths_loader.cpp
    main.cpp
)

set(
    BFS_PLANNER_HEADERS
    ../../../include/frontend/bfs-planner/search/search_types.h
    ../../../include/frontend/bfs-planner/search/search_space.h
    ../../../include/frontend/bfs-planner/search/planner.h
    ../../../include/frontend/bfs-planner/utils/time_utils.h
    ../../../include/frontend/bfs-planner/utils/spec_paths_loader.h
)

add_executable(bfs_planner ${BFS_PLANNER_SRC} ${BFS_PLANNER_HEADERS})

target_compile_features(bfs_planner PRIVATE cxx_std_17)
target_include_directories(bfs_planner PRIVATE ../../include/frontend/bfs_planner)
target_link_libraries(bfs_planner PRIVATE epddl_lib del_lib)

#target_enable_warnings(bfs_planner)
target_code_coverage(bfs_planner)
add_sanitizers(bfs_planner)

set_property(TARGET bfs_planner PROPERTY OUTPUT_NAME bfs_planner)
set_property(TARGET bfs_planner PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

install(TARGETS bfs_planner RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
