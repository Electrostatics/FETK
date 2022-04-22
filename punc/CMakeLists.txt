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
set(BUILD_VF2C ON)
message(STATUS "Will build vf2c")

# BLAS library
# We do not optionally build BLAS
set( BLA_STATIC ON ) # use static linkage
if(APPLE)
    set( BLA_VENDOR Apple )
else()
    set( BLA_VENDOR OpenBLAS )
endif()
find_package( BLAS )
if(NOT BLAS_FOUND)
    set(BUILD_BLAS ON)
    message(STATUS "Will build BLAS")
else()
    set(BUILD_BLAS OFF)
    message(STATUS "Will not build BLAS; using BLAS type ${BLA_VENDOR}")
###    list(APPEND PUNC_EXT_LIBS ${AMD_LIBRARIES})
###    list(APPEND PUNC_EXT_LIB_DIRS ${AMD_LIBDIR})
endif()

# SuperLU library
# At the moment, managed distributions of SuperLU include only the shared libraries.
#   Note: checked on 4/20/22; including apt on Ubuntu and Home/Linuxbrew
# Therefore, we assume that we'll build SuperLU if we're not building shared libs.
message(STATUS "()()()() Static build? ${FETK_STATIC_BUILD}")
if(NOT FETK_STATIC_BUILD)
    message(STATUS "()()()() PUNC check of SuperLU -- Looking for pre-built")
    find_package(SuperLU)
endif()
if(SuperLU_FOUND)
    message(STATUS "()()()() Found SuperLU")
    message(STATUS "()()()() Superlu includes: ${SUPERLU_INCLUDES}")
    message(STATUS "()()()() Superlu libraries: ${SUPERLU_LIBRARIES}")
    set(BUILD_SUPERLU OFF)
else()
    message(STATUS "()()()() Building SuperLU")
    set(BUILD_SUPERLU ON)
endif()

# ARPACK library
find_package( ARPACK )
if(NOT ARPACK_FOUND)
    set(BUILD_ARPACK ON)
else()
    set(BUILD_ARPACK OFF)
###    list(APPEND PUNC_EXT_LIBS ${ARPACK_LIBRARIES})
endif()

# cgcode library
# Will always build cgcode
set(BUILD_CGCODE ON)

# pmg library
# Will always build pmg
set(BUILD_PMG ON)

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
list(APPEND PUNC_INT_LIBS maloc)


################################################################################
# Build PUNC
################################################################################

add_subdirectory(src)
