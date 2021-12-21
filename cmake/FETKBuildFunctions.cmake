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

    message(STATUS "FETK set_basic_vars_and_paths: ${FETK_STANDALONE}, ${PROJECT_NAME}")
    # Conditions for this being used:
    #   1. FETK_STANDALONE means FETK or one of its subprojects is being built in standalone mode
    #   2. If FETK is a subproject; in this case FETK_STANDALONE will be false and the project name will be FETK
    if( FETK_STANDALONE OR (NOT FETK_STANDALONE AND ${PROJECT_NAME} STREQUAL "FETK") )
    
        ################################################################################
        # Set paths
        ################################################################################

        message(STATUS "Setting project paths")

        if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
            set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH "Install prefix" FORCE)
        endif()
        message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

        set(CMAKE_INSTALL_DATAROOTDIR "share/fetk")
        include(GNUInstallDirs)

        ################################################################################
        # Other options and settings
        ################################################################################

        add_compile_options(-fPIC)

        option(FETK_STATIC_BUILD "Flag to indicate whether a static build should be used (if false, will be dynamic)" ON)

        if(FETK_STATIC_BUILD)
            add_definitions(-DFETK_STATIC_BUILD)
            set(BLA_STATIC ON)
            set(BUILD_SHARED_LIBS OFF)
            set(CMAKE_LINK_SEARCH_START_STATIC ON)
            set(CMAKE_LINK_SEARCH_END_STATIC ON)
            if(WIN32)
                set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
                list(PREPEND CMAKE_FIND_LIBRARY_SUFFIXES .lib .a)
            else()
                list(PREPEND CMAKE_FIND_LIBRARY_SUFFIXES .a)
            endif()
        else()
            remove_definitions(-DFETK_STATIC_BUILD)
            set(BLA_STATIC OFF)
            set(BUILD_SHARED_LIBS ON)
            set(CMAKE_LINK_SEARCH_START_STATIC OFF)
            set(CMAKE_LINK_SEARCH_END_STATIC OFF)
            if(WIN32)
                set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL$<$<CONFIG:Debug>:Debug>")
                list(PREPEND CMAKE_FIND_LIBRARY_SUFFIXES .dll)
            elseif(APPLE)
                list(PREPEND CMAKE_FIND_LIBRARY_SUFFIXES .dylib .so)
            else()
                list(PREPEND CMAKE_FIND_LIBRARY_SUFFIXES .so)
            endif()
        endif()

        message(STATUS "FETK static build: ${FETK_STATIC_BUILD}")
        message(STATUS "Building shared libs: ${BUILD_SHARED_LIBS}")
        message(STATUS "Find-library suffixes: ${CMAKE_FIND_LIBRARY_SUFFIXES}")

        
        ################################################################################
        # Enable ansi pedantic compiling
        ################################################################################

        option(ENABLE_PEDANTIC "Enable the pedantic ansi compilation" OFF)

        if(ENABLE_PEDANTIC)
            add_compile_options("-Wall -pedantic -ansi")
            message(STATUS "Pedantic compilation enabled")
        endif()

        ################################################################################
        # Handle conditional debug building                                            #
        ################################################################################

        if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
            set(DEBUG 1)
            set(HAVE_DEBUG 1)
            message(STATUS "Debugging compilation enabled")
            add_definitions(-DHAVE_DEBUG)
        endif()

    else( FETK_STANDALONE )

        ################################################################################
        # Set package variables
        ################################################################################

        set(FETK_VERSION ${FETK_VERSION})
        set(PACKAGE_NAME ${PROJECT_NAME})
        set(PACKAGE_TARNAME ${PROJECT_NAME})
        set(PACKAGE_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}")
        set(PACKAGE_STRING "${PROJECT_NAME} ${PACKAGE_VERSION}")
        set(PACKAGE_BUGREPORT "mholst@math.ucsd.edu")

    endif( FETK_STANDALONE )

    set(CMAKE_INSTALL_INCLUDEDIR "include/${PROJECT_NAME}")

endmacro()


################################################################################
# header_and_type_checks (macro)
#
# Perform standard checks for headers and types
################################################################################
macro(header_and_type_checks)

    ################################################################################
    # Check for types and required headers                                         #
    ################################################################################

    include(CheckTypeSize)

    set(CMAKE_EXTRA_INCLUDE_FILES stddef.h sys/stat.h sys/types.h)
    CHECK_TYPE_SIZE("mode_t" MODE_T)
    CHECK_TYPE_SIZE("pid_t" PID_T)
    CHECK_TYPE_SIZE("size_t" SIZE_T)
    set(CMAKE_EXTRA_INCLUDE_FILES)

    if(NOT HAVE_MODE_T)
        set(mode_t "int")
    endif()

    if(NOT HAVE_PID_T)
        set(pid_t "int")
    endif()

    if(NOT HAVE_SIZE_T)
        set(size_t "unsigned int")
    endif()


    include(CheckIncludeFiles)

    CHECK_INCLUDE_FILES("stdlib.h;stdarg.h;string.h;float.h" STDC_HEADERS)
    if(NOT STDC_HEADERS)
        message(FATAL_ERROR "Missing standard C headers")
    endif()


    if(NOT WIN32)
        CHECK_INCLUDE_FILES("unistd.h" HAVE_UNISTD_H)
        if(NOT HAVE_UNISTD_H)
            message(FATAL_ERROR "Missing required unistd.h header")
        endif()

        CHECK_INCLUDE_FILES("sys/socket.h" HAVE_SYS_SOCKET_H)
        if(NOT HAVE_SYS_SOCKET_H)
            message(FATAL_ERROR "Missing required sys/socket.h header")
        endif()

        CHECK_INCLUDE_FILES("sys/time.h" HAVE_SYS_TIME_H)
        if(NOT HAVE_SYS_TIME_H)
            message(FATAL_ERROR "Missing required sys/time.h header")
        endif()

        CHECK_INCLUDE_FILES("sys/un.h" HAVE_SYS_UN_H)
        if(NOT HAVE_SYS_UN_H)
            message(FATAL_ERROR "Missing required sys/un.h header")
        endif()

        CHECK_INCLUDE_FILES("sys/wait.h" HAVE_SYS_WAIT_H)
        if(NOT HAVE_SYS_WAIT_H)
            message(FATAL_ERROR "Missing required sys/wait.h header")
        endif()

        CHECK_INCLUDE_FILES("netinet/in.h" HAVE_NETINET_IN_H)
        if(NOT HAVE_NETINET_IN_H)
            message(FATAL_ERROR "Missing required netinet/in.h header")
        endif()

        CHECK_INCLUDE_FILES("arpa/inet.h" HAVE_ARPA_INET_H)
        if(NOT HAVE_ARPA_INET_H)
            message(FATAL_ERROR "Missing required arpa/inet.h header")
        endif()

        CHECK_INCLUDE_FILES("netdb.h" HAVE_NETDB_H)
        if(NOT HAVE_UNISTD_H)
            message(FATAL_ERROR "Missing required netdb.h header")
        endif()
        list(APPEND MALOC_REQUIRED_HEADERS "netdb.h")
    endif()

    CHECK_INCLUDE_FILES("sys/stat.h" HAVE_SYS_STAT_H)
    if(NOT HAVE_SYS_STAT_H)
        message(FATAL_ERROR "Missing required sys/stat.h header")
    endif()

    CHECK_INCLUDE_FILES("sys/types.h" HAVE_SYS_TYPES_H)
    if(NOT HAVE_SYS_TYPES_H)
        message(FATAL_ERROR "Missing required sys/types.h header")
    endif()

    CHECK_INCLUDE_FILES("fcntl.h" HAVE_FCNTL_H)
    if(NOT HAVE_FCNTL_H)
        message(FATAL_ERROR "Missing required rcntl.h header")
    endif()

    CHECK_INCLUDE_FILES("rpc/rpc.h" HAVE_RPC_RPC_H)
    if(NOT HAVE_RPC_RPC_H)
        message(WARNING "Missing/invalid rpc/rpc.h header.  XDR support disabled")
        set(HAVE_XDR NO)
    else()
        list(APPEND MALOC_REQUIRED_HEADERS "rpc/rpc.h")
        set(HAVE_XDR YES)
    endif()


    ################################################################################
    # Check for a few required functions and symbols                               #
    ################################################################################

    include(CheckFunctionExists)

    CHECK_FUNCTION_EXISTS(getcwd HAVE_GETCWD)

    if(NOT HAVE_GETCWD)
        message(WARNING "The getcwd function was not found")
    endif()


    include(CheckSymbolExists)

    CHECK_SYMBOL_EXISTS(O_NONBLOCK "fcntl.h" HAVE_O_NONBLOCK)

    if(NOT HAVE_O_NONBLOCK)
        message(WARNING "The O_NONBLOCK symbol was not found")
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
#           - EXTERNAL HEADERS
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
