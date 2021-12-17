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
    list(APPEND PUNC_EXT_LIBS ${AMD_LIBRARIES})
    list(APPEND PUNC_EXT_LIB_DIRS ${AMD_LIBDIR})
endif()

# lapack library [error]
# build seems disabled
# cmake has FindLAPACK
# tested in docker with apt-get installed liblapack-dev; got an error:
# -- Looking for cheev_ - not found
# CMake Error at /usr/share/cmake-3.16/Modules/FindLAPACK.cmake:423 (message):
#   A required library with LAPACK API not found.  Please specify library
#   location.
#set( BLA_STATIC ON ) # use static linkage
#set( BLA_VENDOR OpenBLAS )
#find_package( LAPACK REQUIRED )
#if( LAPACK_FOUND )
#    message( STATUS "##### Found LAPACK" )
#endif()
#if( TARGET LAPACK::LAPACK )
#    message( STATUS "##### Found LAPACK::LAPACK target" )
#endif()

# AMD library
# We do not optionally build AMD
find_package( AMD REQUIRED )
list(APPEND PUNC_EXT_LIBS ${AMD_LIBRARIES})
list(APPEND PUNC_EXT_LIB_DIRS ${AMD_LIBDIR})

# UMFPACK library
# We do not optionally build umfpack
find_package( UMFPACK REQUIRED )
list(APPEND PUNC_EXT_LIBS ${UMFPACK_LIBRARIES})
list(APPEND PUNC_EXT_LIB_DIRS ${UMFPACK_LIBDIR})

# SuperLU library
# We only build SuperLU from its git repo
set(BUILD_SUPERLU ON)
#find_package( SuperLU )
#if(NOT SuperLU_FOUND)
#    set(BUILD_SUPERLU ON)
#else()
#    set(BUILD_SUPERLU OFF)
#endif()

# ARPACK library
find_package( ARPACK )
if(NOT ARPACK_FOUND)
    set(BUILD_ARPACK ON)
else()
    set(BUILD_ARPACK OFF)
    list(APPEND PUNC_EXT_LIBS ${ARPACK_LIBRARIES})
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
