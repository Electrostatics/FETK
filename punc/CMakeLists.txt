# Minimum version: 3.7.1 required by CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
cmake_minimum_required (VERSION 3.7.1)

# Include the common FETK CMake utilities
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
include(FETKBuildFunctions)

project(punc 
        VERSION 0.0.0
        LANGUAGES C
)

# Set essential variables and paths for the project
set_basic_vars_and_paths()


# check for libraries

# check for disable vender-host-cpu triplet (?)

# readline library

# mpi library

# [embed check to be left out]

# debug compilation

# ansi/pedantic compilation

# profiling

# electric fence library (?)

# vf2c library (build or find)

# blas library (build or find)

# lapack library (build or find)
# build seems disabled

# amd library (build or find)

# umfpack library (build or find)

# superlu library (build or find)

# arpack library (build or find)
# build seems disabled

# cgcode library (build or find)
# build seems disabled

# pmg library (build or find)
# build seems disabled

# maloc library


