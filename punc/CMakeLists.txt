# Minimum version: 3.7.1 required by CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
cmake_minimum_required (VERSION 3.7.1)

message(NOTICE "Configuring build for PUNC")

# CXX is included as an enabled language because the SuperLU checks require it
project(punc
        VERSION 0.0.0
        LANGUAGES C CXX
)

# Include the common FETK CMake utilities
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
include(FETKBuildFunctions)
include(FetchContent)

# Set essential variables and paths for the project
set_basic_vars_and_paths()
set(PUNC_VERSION ${punc_VERSION})


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
# Here are the libraries that can be built by PUNC
################################################################################

# vf2c library
# We only build vf2c
option(BUILD_VF2C "Flag to build VF2C" ON)
if(BUILD_VF2C)
    message(STATUS "Will build vf2c")
endif()

# BLAS library
# We do not optionally build BLAS
set( BLA_STATIC ON ) # use static linkage
if(APPLE)
    set( BLA_VENDOR Apple )
else()
    set( BLA_VENDOR OpenBLAS )
endif()
find_package( BLAS )
if(BLAS_FOUND)
    set(BUILD_BLAS OFF)
else()
    option(BUILD_BLAS "Flag to build BLAS" ON)
endif()
if(BUILD_BLAS)
    message(STATUS "Will build BLAS")
endif()

# SuperLU library
# At the moment, managed distributions of SuperLU include only the shared libraries.
#   Note: checked on 4/20/22; including apt on Ubuntu and Home/Linuxbrew
# Therefore, we assume that we'll build SuperLU if we're not building shared libs.
if(NOT FETK_STATIC_BUILD)
    find_package(SuperLU)
endif()
if(SuperLU_FOUND)
    set(BUILD_SUPERLU OFF)
else()
    option(BUILD_SUPERLU "Flag to build SuperLU" ON)
endif()
if(BUILD_SUPERLU)
    message(STATUS "Will build SuperLU")
endif()

# ARPACK library
find_package( ARPACK )
if(NOT ARPACK_FOUND)
    set(BUILD_ARPACK ON)
else()
    option(BUILD_ARPACK "Flag to build ARPACK" OFF)
###    list(APPEND PUNC_EXT_LIBS ${ARPACK_LIBRARIES})
endif()
if(BUILD_ARPACK)
    message(STATUS "Will build ARPACK")
endif()

# cgcode library
# Will always build cgcode
option(BUILD_CGCODE "Flag to build CGCODE" ON)
if(BUILD_CGCODE)
    message(STATUS "Will build CGCODE")
endif()

# pmg library
# Will always build pmg
option(BUILD_PMG "Flag to build PMG" ON)
if(BUILD_PMG)
    message(STATUS "Will build PMG")
endif()

################################################################################
# Ensure we have the MALOC library
################################################################################

# maloc library
if(NOT TARGET maloc)
    message(FATAL_ERROR "Maloc target not found")
endif()
list(APPEND PUNC_INT_LIBS maloc)


################################################################################
# Build PUNC
################################################################################

add_subdirectory(src)
