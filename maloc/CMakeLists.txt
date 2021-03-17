cmake_minimum_required (VERSION 3.1)

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

#include(CheckIncludeFiles)
#include(CheckFunctionExists)
#include(CheckSymbolExists)
#include(CheckTypeSize)
#include(ExternalProject)

#set(MALOC_VERSION "1.0.1")
#set(FETK_VERSION "1.0.0")
#set(PACKAGE_NAME "maloc")
#set(PACKAGE_TARNAME "maloc")
#set(PACKAGE_VERSION "1.0")
#set(PACKAGE_STRING "maloc 1.0")
#set(PACKAGE_BUGREPORT "mholst@math.ucsd.edu")

project(maloc 
        VERSION 1.0.1
        LANGUAGES C
)


################################################################################
# Set project paths                                                            #
################################################################################

message(STATUS "Setting project paths")

set(CMAKE_INSTALL_INCLUDEDIR include/${PROJECT_NAME})
include(GNUInstallDirs)

#set(MALOC_ROOT ${PROJECT_SOURCE_DIR})
#set(EXECUTABLE_OUTPUT_PATH ${MALOC_ROOT}/bin)
#set(LIBRARY_OUTPUT_PATH ${MALOC_ROOT}/lib)
#set(MALOC_BINARY ${EXECUTABLE_OUTPUT_PATH}/maloc)

#set(INCLUDE_INSTALL_DIR include/maloc)
#set(LIBRARY_INSTALL_DIR lib)
#set(EXECUTABLE_INSTALL_DIR bin)


################################################################################
# Set up temporary files and directories                                       #
################################################################################

#file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/temp)



################################################################################
# Set the lookup paths for external library dependencies                       #
################################################################################

#message(STATUS "Setting lookup paths for headers and libraries")

#set(SYS_INCPATHS "${CMAKE_INCLUDE_PATH}")
#list(APPEND SYS_INCPATHS /usr/include)
#list(APPEND SYS_INCPATHS /usr/local/include)
#include_directories(${SYS_INCPATHS})

#set(SYS_LIBPATHS "")
#list(APPEND SYS_LIBPATHS /usr/lib)
#list(APPEND SYS_LIBPATHS /usr/local/lib)
#list(APPEND SYS_LIBPATHS /lib/x86_64-linux-gnu)

#set(MALOC_LIBS)



################################################################################
# Enable ansi pedantic compiling                                               #
################################################################################

option(ENABLE_PEDANTIC "Enable the pedantic ansi compilation" OFF)

if(ENABLE_PEDANTIC)
    ADD_DEFINITIONS("-Wall -pedantic -ansi")
    message(STATUS "Pedantic compilation enabled")
endif()


################################################################################
# Find some libraries                                                          #
################################################################################

if(NOT WIN32)
    find_library(MATH_LIBRARY "m" REQUIRED)
    list(APPEND MALOC_EXT_LIBS ${MATH_LIBRARY})
endif()

find_library(LIBERTY_LIBRARY "iberty" REQUIRED)
if(LIBERTY_LIBRARY)
    list(APPEND MALOC_EXT_LIBS ${LIBERTY_LIBRARY})
endif()

find_library(NSL_LIBRARY "nsl" REQUIRED)
if(NSL_LIBRARY)
    list(APPEND MALOC_EXT_LIBS ${NSL_LIBRARY})
endif()

find_library(SOCKET_LIBRARY "socket" REQUIRED)
if(SOCKET_LIBRARY)
    list(APPEND MALOC_EXT_LIBS ${SOCKET_LIBRARY})
endif()

find_package(Threads REQUIRED)
if(TARGET Threads::Threads)
    list(APPEND MALOC_EXT_LIBS Threads::Threads)
endif()

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

option(ENABLE_EFENCE "Enable the electric fence library" OFF)
if(ENABLE_EFENCE)
    message(STATUS "Checking for efence library")
    find_library(EFENCE_LIBRARY "efence" REQUIRED)
    if(EFENCE_LIBRARY)
        list(APPEND MALOC_EXT_LIBS ${EFENCE_LIBRARY})
    endif()
endif()



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



################################################################################
# Handle conditional availability of macro embedding                           #
################################################################################

try_compile(
    HAVE_EMBED
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src/config/embed_test.c
    )

# TODO: Determine if the EMBED macro is even used



################################################################################
# Handle conditional debug building                                            #
################################################################################

option(ENABLE_DEBUG "Enable debugging mode" OFF)

if(ENABLE_DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
    set(DEBUG 1)
    set(HAVE_DEBUG 1)
    message(STATUS "Debugging compilation enabled")
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

if(MINGW)
    message(STATUS "Checking for wsock32 in MinGW environment")
    find_library(
        MINGW_WSOCK32
        NAMES wsock32
        PATHS ${SYS_LIBPATHS}
        DOC   "The wsock32 library"
        )

    if(MINGW_WSOCK32)
        message(STATUS "The wsock32 library was found: ${MINGW_HAS_WSOCK32}")
    else()
        message(FATAL_ERROR "The wsock32 library was not fond")
    endif()
endif()



if(CYGWIN)
    message(STATUS "Checking for wsock32 in Cygwin environment")
    find_library(
        CYGWIN_WSOCK32
        NAMES wsock32
        PATHS ${SYS_LIBPATHS}
        DOC   "The wsock32 library"
        )

    if(CYGWIN_WSOCK32)
        message(STATUS "The wsock32 library was found: ${CYGWIN_WSOCK32}")
        list(APPEND MALOC_LIBS ${CYGWIN_WSOCK32})
    else()
        message(FATAL_ERROR "The wsock32 library was not fond")
    endif()

    set(MSDOS 1)
    set(WIN32 1)
    set(HAVE_CYGWIN 1)
endif()

if(NOT CYGWIN AND NOT MINGW AND WIN32)
    ADD_DEFINITIONS("/D _CRT_SECURE_NO_WARNINGS")
endif()

################################################################################
# Build MALOCsources                                                           #
################################################################################

add_subdirectory(src)

