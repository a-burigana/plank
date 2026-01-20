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

cmake_minimum_required(VERSION 3.16)

project(
    plank
    VERSION 1.0.0
    DESCRIPTION "The *plank* toolkit for DEL-based epistemic planning."
    LANGUAGES C CXX
)

# User options
option(ENABLE_TESTS "Enable test suite" ON)

#
# Additional modules
#
set(
    CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/external/sanitizers-cmake/cmake"
    "${CMAKE_SOURCE_DIR}/cmake"
    ${CMAKE_MODULE_PATH}
)

include(EnableWarnings) # Common warnings to enable or disable
include(CodeCoverage)   # Code to enable code coverage instrumentation

find_package(Sanitizers) # Sanitizers

# BOOST
find_package(Boost 1.74.0 REQUIRED COMPONENTS filesystem)

if (BOOST_FOUND)
    message(STATUS "Boost version: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIR})
else()
    message(SEND_ERROR "Could not find Boost library.")
endif ()

# DEL library, EPDDL library and plank frontend
add_subdirectory(src/lib/del)
add_subdirectory(src/lib/epddl)
add_subdirectory(src/frontend/plank)

# Tests

if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Auto-ignore build directory
if (NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
    file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif ()
