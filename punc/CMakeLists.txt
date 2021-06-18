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

# BLAS library [done]
# cmake has FindBLAS
# this works in docker with apt-get installed blas
set( BLA_STATIC ON ) # use static linkage
find_package( BLAS REQUIRED )
if( BLAS_FOUND )
    message( STATUS "##### Found BLAS" )
    # docker: see this
endif()
if( TARGET BLAS::BLAS )
    message( STATUS "##### Found BLAS::BLAS target" )
    # docker: do not see this
endif()

# lapack library [error]
# build seems disabled
# cmake has FindLAPACK
# tested in docker with apt-get installed liblapack-dev; got an error:
# -- Looking for cheev_ - not found
# CMake Error at /usr/share/cmake-3.16/Modules/FindLAPACK.cmake:423 (message):
#   A required library with LAPACK API not found.  Please specify library
#   location.
set( BLA_STATIC ON ) # use static linkage
find_package( LAPACK REQUIRED )
if( LAPACK_FOUND )
    message( STATUS "##### Found LAPACK" )
endif()
if( TARGET LAPACK::LAPACK )
    message( STATUS "##### Found LAPACK::LAPACK target" )
endif()

# AMD library [done]
# adapted from https://gitlab.com/libeigen/eigen/-/blob/master/cmake/FindUMFPACK.cmake
find_package( AMD REQUIRED )
if( AMD_FOUND )
    message( STATUS "##### Found AMD" )
endif()

# UMFPACK library [done]
# https://gitlab.com/libeigen/eigen/-/blob/master/cmake/FindUMFPACK.cmake
find_package( UMFPACK REQUIRED )
if( UMFPACK_FOUND )
    message( STATUS "##### Found UMFPACK" )
endif()

# SuperLU library [done]
# https://gitlab.com/libeigen/eigen/-/blob/master/cmake/FindSuperLU.cmake
find_package( SuperLU REQUIRED )
if( SuperLU_FOUND )
    message( STATUS "##### Found SuperLU" )
endif()

# ARPACK library [done]
# check for installed version is disabled in autoconf
# https://github.com/sidch/CMake/blob/master/Modules/FindARPACK.cmake
find_package( ARPACK REQUIRED )
if( ARPACK_FOUND )
    message( STATUS "##### Found ARPACK" )
endif()

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
