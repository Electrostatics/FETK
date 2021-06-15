# Minimum version: 3.7.1 required by CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
cmake_minimum_required (VERSION 3.7.1)

message(NOTICE "Configuring build for PUNC")

project(punc
        VERSION 0.0.0
        LANGUAGES C
)

# Include the common FETK CMake utilities
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
include(FETKBuildFunctions)


# Set essential variables and paths for the project
set_basic_vars_and_paths()
set(PUNC_VERSION ${punc_VERSION})



# check for libraries

# check for disable vender-host-cpu triplet (?)

# readline library

# mpi library

# [embed check to be left out]

# debug compilation

# ansi/pedantic compilation

# profiling

# electric fence library (?)

##########
# Here are the libraries that can be built by PUNC
##########

# vf2c library (build or find)
set(BUILD_VF2C ON)
# eigen's find for liblapack seems to have f2c find: https://gitlab.com/libeigen/eigen/-/blob/master/cmake/FindLAPACK.cmake
# need to include headers in punc subdirectory

# blas library (build or find)
# cmake has FindBLAS

# lapack library (build or find)
# build seems disabled
# cmake has FindLAPACK

# amd library (build or find)
# this includes finding amd: https://ceres-solver.googlesource.com/ceres-solver/+/master/cmake/FindSuiteSparse.cmake

# umfpack library (build or find)
# https://gitlab.com/libeigen/eigen/-/blob/master/cmake/FindUMFPACK.cmake

# superlu library (build or find)
# https://gitlab.com/libeigen/eigen/-/blob/master/cmake/FindSuperLU.cmake

# arpack library (build or find)
# check for installed version is disabled in autoconf
# https://github.com/sidch/CMake/blob/master/Modules/FindARPACK.cmake

# cgcode library (build or find)
# check for installed version is disabled in autoconf
# doesn't seem to exist in ubuntu package repository
# probably need to build

# pmg library (build or find)
# check for installed version is disabled in autoconf
# doesn't seem to exist in ubuntu package repository
# probably need to build

##########
# End of PUNC libraries
##########

# maloc library
if(NOT TARGET maloc)
    message(FATAL_ERROR "Maloc target not found")
endif()
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../maloc/src/base
    ${CMAKE_CURRENT_SOURCE_DIR}/../maloc/src/psh
    ${CMAKE_CURRENT_SOURCE_DIR}/../maloc/src/vsh
    ${CMAKE_CURRENT_SOURCE_DIR}/../maloc/src/vsys
)
list(APPEND PUNC_INT_LIBS maloc)


################################################################################
# Build PUNC
################################################################################

add_subdirectory(src)
