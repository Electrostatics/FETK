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

# vf2c library [done]
set(BUILD_VF2C ON)

# BLAS library [done]
set( BLA_STATIC ON ) # use static linkage
find_package( BLAS REQUIRED )

# lapack library [error]
# build seems disabled
# cmake has FindLAPACK
# tested in docker with apt-get installed liblapack-dev; got an error:
# -- Looking for cheev_ - not found
# CMake Error at /usr/share/cmake-3.16/Modules/FindLAPACK.cmake:423 (message):
#   A required library with LAPACK API not found.  Please specify library
#   location.
set( BLA_STATIC ON ) # use static linkage
set( BLA_VENDOR OpenBLAS )
#find_package( LAPACK REQUIRED )
#if( LAPACK_FOUND )
#    message( STATUS "##### Found LAPACK" )
#endif()
#if( TARGET LAPACK::LAPACK )
#    message( STATUS "##### Found LAPACK::LAPACK target" )
#endif()

# AMD library [done]
find_package( AMD REQUIRED )
if( AMD_FOUND )
    message( STATUS "##### Found AMD" )
endif()

# UMFPACK library [done]
find_package( UMFPACK REQUIRED )
if( UMFPACK_FOUND )
    message( STATUS "##### Found UMFPACK" )
endif()

# SuperLU library [done]
find_package( SuperLU REQUIRED )
if( SuperLU_FOUND )
    message( STATUS "##### Found SuperLU" )
endif()

# ARPACK library [done]
find_package( ARPACK REQUIRED )
if( ARPACK_FOUND )
    message( STATUS "##### Found ARPACK" )
endif()

# cgcode library [done]
set(BUILD_CGCODE ON)

# pmg library [done]
set(BUILD_PMG ON)

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
