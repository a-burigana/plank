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

set(
    DEL_LIB_SRC
    language/language.cpp
    language/label.cpp
    language/formulas.cpp
    semantics/model_checker.cpp
    semantics/update/updater.cpp
    semantics/states/state.cpp
    semantics/states/finitary_s5_theory.cpp
    semantics/states/bisimulations/bisimulator.cpp
    semantics/states/bisimulations/contraction_builder.cpp
    semantics/states/bisimulations/partition_refinement.cpp
    semantics/actions/action.cpp
)

set(
    DEL_LIB_HEADERS
    ../../../include/lib/del/utils/bit_deque.h
    ../../../include/lib/del/language/label.h
    ../../../include/lib/del/language/language.h
    ../../../include/lib/del/language/formulas.h
    ../../../include/lib/del/language/language_types.h
    ../../../include/lib/del/semantics/update/updater.h
    ../../../include/lib/del/semantics/model_checker.h
    ../../../include/lib/del/semantics/states/states_types.h
    ../../../include/lib/del/semantics/states/bisimulations/bisimulation_types.h
    ../../../include/lib/del/semantics/states/bisimulations/contraction_builder.h
    ../../../include/lib/del/semantics/states/bisimulations/partition_refinement.h
    ../../../include/lib/del/semantics/states/bisimulations/bisimulator.h
    ../../../include/lib/del/semantics/states/state.h
    ../../../include/lib/del/semantics/states/finitary_s5_theory.h
    ../../../include/lib/del/semantics/actions/action.h
    ../../../include/lib/del/semantics/actions/actions_types.h
    ../../../include/lib/del/semantics/planning_task.h
)

# EPDDL library
add_library(del_lib ${DEL_LIB_SRC} ${DEL_LIB_HEADERS})
target_compile_features(del_lib PUBLIC cxx_std_17)

target_include_directories(del_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(del_lib PRIVATE ../../../include/lib/del)

#target_enable_warnings(del_lib)
target_code_coverage(del_lib)
add_sanitizers(del_lib)
