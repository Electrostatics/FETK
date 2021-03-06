# Minimum version: 3.7.1 required by CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
cmake_minimum_required (VERSION 3.7.1)

message(NOTICE "Configuring build for MC")

project(mc
        VERSION 0.0.0
        LANGUAGES C
)

# Include the common FETK CMake utilities
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
include(FETKBuildFunctions)


# Set essential variables and paths for the project
set_basic_vars_and_paths()
set(MC_VERSION ${mc_VERSION})


################################################################################
# Check for necessary headers and types
################################################################################

header_and_type_checks()



# check for libraries

# check for disable vender-host-cpu triplet (?)

# readline library

# mpi library

# [embed check to be left out]

# debug compilation

# ansi/pedantic compilation

# profiling

# electric fence library (?)


################################################################################
# Ensure we have the MALOC library
################################################################################

# maloc library
if(NOT TARGET maloc)
    message(FATAL_ERROR "Maloc target not found")
endif()
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../maloc/src/base
    ${CMAKE_CURRENT_SOURCE_DIR}/../maloc/src/psh
    ${CMAKE_CURRENT_SOURCE_DIR}/../maloc/src/vsh
    ${CMAKE_CURRENT_SOURCE_DIR}/../maloc/src/vsys
    ${CMAKE_CURRENT_SOURCE_DIR}/../punc/src/base
    ${CMAKE_CURRENT_SOURCE_DIR}/../punc/src/amd
    ${CMAKE_CURRENT_SOURCE_DIR}/../punc/src/amd/punc # we need this because punc/umfpack.h has #include
    ${CMAKE_CURRENT_SOURCE_DIR}/../punc/src/superlu
    ${CMAKE_CURRENT_SOURCE_DIR}/../punc/src/umfpack
)
list(APPEND MC_INT_LIBS maloc)

# punc library
if(NOT TARGET punc)
    message(FATAL_ERROR "Punc target not found")
endif()
#include_directories(
#)
list(APPEND MC_INT_LIBS punc)


################################################################################
# Build MC
################################################################################

add_subdirectory(src)
