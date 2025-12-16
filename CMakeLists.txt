cmake_minimum_required(VERSION 3.16)

project(EPDDL VERSION 1.0
    DESCRIPTION "Official parser of the Epistemic Planning Domain Definition Language"
    LANGUAGES C CXX)

# BOOST
#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.74.0 REQUIRED COMPONENTS filesystem)
message(STATUS "Boost version: ${Boost_VERSION}")

include_directories(${Boost_INCLUDE_DIR})

# Collect all headers in include/**
file(GLOB_RECURSE EPDDL_HEADERS
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
        )

# Collect all sources in src/**
file(GLOB_RECURSE EPDDL_SOURCES
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        )

#
# Additional modules
#
set(CMAKE_MODULE_PATH
        "${CMAKE_SOURCE_DIR}/sanitizers-cmake/cmake"
        ${CMAKE_MODULE_PATH})

find_package(Sanitizers) # Sanitizers

#
# EXECUTABLES
#
add_executable(EPDDL ${EPDDL_SOURCES} ${EPDDL_HEADERS} src/del/semantics/states/finitary_s5_theory.cpp include/del/semantics/states/finitary_s5_theory.h)

# Compilation Features
target_compile_features(EPDDL PUBLIC cxx_std_17)
#target_compile_features(EPDDL PRIVATE cxx_std_${CMAKE_CXX_STANDARD})
#target_compile_options(EPDDL PRIVATE -Wall) #To show one error at the time

add_sanitizers(EPDDL)

# Auto-ignore build directory
if (NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
    file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif ()
