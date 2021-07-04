# Minimum version: 3.7.1 required by CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
cmake_minimum_required (VERSION 3.7.1)

################################################################################
# TODO:
################################################################################

################################################################################
# Future Enchancements
# --------------------
# [ ] Adding a profiling mode set by a flag
# [ ] Add functionality for creating rpm and deb packages
################################################################################


################################################################################
# Test platforms
# --------------
# [ ] Ubuntu x86_64
# [ ] Ubuntu i386
# [ ] Redhat 5
# [ ] ArchLinux x86_64
# [ ] Mac OSX
# [ ] Windows 7 x86_64
# [ ] Windows 7 i386
################################################################################

message(NOTICE "Configuring build for MALOC")

project(maloc 
        VERSION 1.0.1
        LANGUAGES C
)

# Include the common FETK CMake utilities
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
include(FETKBuildFunctions)


# Set essential variables and paths for the project
set_basic_vars_and_paths()
set(MALOC_VERSION ${maloc_VERSION})


################################################################################
# Check for necessary headers and types
################################################################################

header_and_type_checks()


################################################################################
# Handle conditional availability of macro embedding                           #
################################################################################

try_compile(
    HAVE_EMBED
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/config/embed_test.c
)

# TODO: Determine if the EMBED macro is even used


################################################################################
# Find some libraries                                                          #
################################################################################

#if(NOT WIN32)
#    find_library(MATH_LIBRARY "m" REQUIRED)
#    list(APPEND MALOC_EXT_LIBS ${MATH_LIBRARY})
#endif()

#find_library(LIBERTY_LIBRARY "iberty" REQUIRED)
#if(LIBERTY_LIBRARY)
#    list(APPEND MALOC_EXT_LIBS ${LIBERTY_LIBRARY})
#endif()

#find_library(NSL_LIBRARY "nsl" REQUIRED)
#if(NSL_LIBRARY)
#    list(APPEND MALOC_EXT_LIBS ${NSL_LIBRARY})
#endif()

find_library(SOCKET_LIBRARY "socket")
if(SOCKET_LIBRARY)
    list(APPEND MALOC_EXT_LIBS ${SOCKET_LIBRARY})
endif()

#find_package(Threads REQUIRED)
#if(TARGET Threads::Threads)
#    list(APPEND MALOC_EXT_LIBS Threads::Threads)
#endif()

option(ENABLE_READLINE "Enable the readline library" OFF)
if(ENABLE_READLINE)
    find_library(READLINE_LIBRARY "readline" REQUIRED)
    if(READLINE_LIBRARY)
        list(APPEND MALOC_EXT_LIBS ${READLINE_LIBRARY})
        set(HAVE_LIBREADLINE TRUE)

        set(CURSES_NEED_NCURSES TRUE)
        find_package(Curses REQUIRED)
        if(NCURSES_LIBRARY)
            list(APPEND MALOC_EXT_LIBS ${CURSES_LIBRARIES})
        endif()
    endif()
endif()


################################################################################
# Handle conditional building with MPI Support                                 #
################################################################################

option(ENABLE_MPI "Enable MPI parallelism" OFF)

if(ENABLE_MPI)
    if(NOT ENABLE_DEBUG)
        message(STATUS "Checking for MPI")
        find_package(MPI)
        if(MPI_FOUND)
            message(STATUS "MPI support enabled")
            include_directories(${MPI_INCLUDE_PATH})
            list(APPEND MALOC_LIBS ${MPI_LIBRARIES})
        else()
            message(WARNING "MPI was not found; disabling")
        endif()
    else()
        message(WARNING "MPI may not be enabled in debugging mode")
    endif()
endif()



################################################################################
# Handle library checks for embedded unix environments in windows              #
################################################################################

if(NOT CYGWIN AND NOT MINGW AND WIN32)
    ADD_DEFINITIONS("/D _CRT_SECURE_NO_WARNINGS")
endif()


################################################################################
# Build MALOCsources                                                           #
################################################################################

add_subdirectory(src)

