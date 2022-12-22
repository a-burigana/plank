cmake_minimum_required(VERSION 3.16)

project(EPDDL VERSION 1.0
    DESCRIPTION "Epistemic Planning Domain Definition Language"
    LANGUAGES C CXX)

# Source files to include in compilation -- To include all use: file(GLOB_RECURSE EFP_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
set(
    EPDDL_SOURCES
    src/main.cpp
    src/lex.cpp
)

# Headers files to include in compilation -- To include all use: file(GLOB_RECURSE EFP_HEADERS ${CMAKE_SOURCE_DIR}/src/*.h)
set(
    EPDDL_HEADERS
#    src/lex.hpp
)

# EXECUTABLES
add_executable(EPDDL ${EPDDL_SOURCES} ${EPDDL_HEADERS})


# Compilation Features
#set(CMAKE_CXX_STANDARD 17)
target_compile_features(EPDDL PUBLIC cxx_std_17)
#target_compile_features(EPDDL PRIVATE cxx_std_${CMAKE_CXX_STANDARD})
#target_compile_options(EPDDL PRIVATE -Wall) #To show one error at the time

# Auto-ignore build directory
if (NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
    file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif ()
