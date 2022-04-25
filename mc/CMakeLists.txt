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
#set( BLA_VENDOR "OpenBLAS" )
set( BLA_STATIC ON )
#message(STATUS "looking for MC dependencies with openblas and static on")
#find_library( lapack_found_separately openblas REQUIRED )
#message(STATUS "#### found lapack: ${lapack_found_separately}")
#set( paths_from_module ENV;LD_LIBRARY_PATH;/usr/lib/gcc/x86_64-linux-gnu/9;/usr/lib/x86_64-linux-gnu;/usr/lib;/lib/x86_64-linux-gnu;/lib)
#find_library( lapack_found_separately_2 openblas REQUIRED PATHS ${paths_from_module})
#message(STATUS "#### found lapack 2: ${lapack_found_separately_2}")
#find_package( LAPACK REQUIRED )
find_package( UMFPACK REQUIRED )
find_package( SuiteSparse REQUIRED )
include_directories( ${SUITESPARSE_INCLUDE_DIRS} )
list(APPEND MC_EXT_LIBS
    ${UMFPACK_LIBRARIES}
    ${SUITESPARSE_LIBRARIES}
)

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
list(APPEND MC_INT_LIBS maloc)

# punc library
if(NOT TARGET punc)
    message(FATAL_ERROR "Punc target not found")
endif()
list(APPEND MC_INT_LIBS punc)


################################################################################
# Build MC
################################################################################

add_subdirectory(src)
