# FETKBuildFunctions.cmake
#
# Author: N.S. Oblath
# Created: Apr 6, 2021


# Determine if this is a standalone build or not
set(FETK_STANDALONE FALSE CACHE INTERNAL "Flag for whether or not this is a stand-alone build")
if(${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
    set(FETK_STANDALONE TRUE)
    



endif()


################################################################################
# set_basic_vars_and_paths (macro)
#
# Use this macro just after the project() command to set common variables and paths
#
# No arguments
################################################################################
macro(set_basic_vars_and_paths)

    ################################################################################
    # Set package variables
    ################################################################################

    set(FETK_VERSION ${FETK_VERSION})
    set(PACKAGE_NAME ${PROJECT_NAME})
    set(PACKAGE_TARNAME ${PROJECT_NAME})
    set(PACKAGE_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}")
    set(PACKAGE_STRING "${PROJECT_NAME} ${PACKAGE_VERSION}")
    set(PACKAGE_BUGREPORT "mholst@math.ucsd.edu")


    ################################################################################
    # Set project paths
    ################################################################################

    message(STATUS "Setting project paths")

    if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH "Install prefix" FORCE)
    endif()
    message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

    set(CMAKE_INSTALL_INCLUDEDIR include/${PROJECT_NAME})
    include(GNUInstallDirs)


    ################################################################################
    # Other options and settings
    ################################################################################

    set(BUILD_SHARED_LIBRARIES OFF)


    ################################################################################
    # Enable ansi pedantic compiling
    ################################################################################

    option(ENABLE_PEDANTIC "Enable the pedantic ansi compilation" OFF)

    if(ENABLE_PEDANTIC)
        add_compile_options("-Wall -pedantic -ansi")
        message(STATUS "Pedantic compilation enabled")
    endif()



endmacro()


################################################################################
# find_or_build (function)
#
# Finds a library or builds it if it isn't found
################################################################################
function(find_or_build)

    set(options OPTIONAL FAST)
    set(oneValueArgs DESTINATION RENAME)
    set(multiValueArgs TARGETS CONFIGURATIONS)

    cmake_parse_arguments(PARSE_ARGV 0 FOB_ options oneValueArgs multiValueArgs )


endfunction()