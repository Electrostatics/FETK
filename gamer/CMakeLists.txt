# Minimum version: 3.7.1 required by CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
cmake_minimum_required (VERSION 3.7.1)

message(NOTICE "Configuring build for GAMER")

project(gamer
        VERSION 0.0.0
        LANGUAGES C CXX
)

# Include the common FETK CMake utilities
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
include(FETKBuildFunctions)


# Set essential variables and paths for the project
set_basic_vars_and_paths()
set(GAMER_VERSION ${gamer_VERSION})


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
#include_directories(
#    ${CMAKE_CURRENT_SOURCE_DIR}/../maloc/src/base
#    ${CMAKE_CURRENT_SOURCE_DIR}/../maloc/src/psh
#    ${CMAKE_CURRENT_SOURCE_DIR}/../maloc/src/vsh
#    ${CMAKE_CURRENT_SOURCE_DIR}/../maloc/src/vsys
#)
list(APPEND GAMER_INT_LIBS maloc)


################################################################################
# Build GAMER
################################################################################

add_subdirectory(src)
