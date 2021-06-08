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

    cmake_parse_arguments(PARSE_ARGV 0 FOB options oneValueArgs multiValueArgs )


endfunction()


################################################################################
# setup_for_build (macro)
#
# Prepares the variables that will be used to build the library
################################################################################
macro(setup_for_build)
    set(LIB_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    set(ALLOWABLE_TYPES "SOURCES;EXTERNAL_HEADERS;INTERNAL_HEADERS")
    set(SOURCES)
    set(EXTERNAL_HEADERS)
    set(INTERNAL_HEADERS)
endmacro()


################################################################################
# add_build_items (macro)
#
# Adds items (sources, internal headers, and external headers) for the build
#
# Arguments:
#   TYPE: options are
#           - SOURCES
#           - INTERNAL_HEADERS
#           = EXTERNAL HEADERS
#   ITEMS: space-separated list of files (relative or absolute paths)
################################################################################
macro(add_build_items)

    set(oneValueArgs TYPE)
    set(multiValueArgs ITEMS)
    #cmake_parse_arguments(ABI "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    cmake_parse_arguments(ABI "" "TYPE" "ITEMS" ${ARGN})

    message(STATUS "Type: ${ABI_TYPE}")
    message(STATUS "Items: ${ABI_ITEMS}")

    # Make sure the TYPE argument is valid
    if(NOT "${ABI_TYPE}" IN_LIST ALLOWABLE_TYPES)
        message(
            FATAL_ERROR
            "Passed an invalid type to add_build_items macro.  "
            "Must be one of ${ALLOWABLE_TYPES}.  "
            "Was ${ABI_TYPE}."
        )
    endif()

    # Add each item successively
    foreach(ITEM ${ABI_ITEMS})
        get_filename_component(ITEM_PATH ${ITEM} ABSOLUTE)

        # Add the item to the appropriately typed list
        list(APPEND ${ABI_TYPE} "${ITEM_PATH}")
    endforeach()

    # If this folder is not the library-build directory, push the updated item list to the parent scope
    if(NOT LIB_BUILD_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
        set(${ABI_TYPE} ${${ABI_TYPE}} PARENT_SCOPE)
    endif()

endmacro()
