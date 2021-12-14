# Minimum version: 3.7.1 required by CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
cmake_minimum_required (VERSION 3.7.1)

cmake_policy(SET CMP0042 NEW)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0077 NEW)

# this is needed for keeping the new behavior of CMP0077 in the build of superlu, which uses and older minimum required CMake
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

# Parse the VERSION file
# First, remove comments
execute_process(
    COMMAND "sed" "s/#.*//g" "${CMAKE_CURRENT_SOURCE_DIR}/VERSION"  
    OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/VERSION
)
file(STRINGS ${CMAKE_CURRENT_BINARY_DIR}/VERSION VERSION_STRING)
# Turn the spaces into semicolons to create a list
string(REPLACE " " ";" VERSION_LIST ${VERSION_STRING})
# Extract the project name and version
list(GET VERSION_LIST 0 _PROJECT)
list(GET VERSION_LIST 2 _VERSION)
# strip off any version suffix starting with a hyphen
string(REGEX REPLACE "-[A-Za-z0-9_-]*$" "" _VERSION ${_VERSION})

project(${_PROJECT}
        VERSION ${_VERSION}
        LANGUAGES C
)

# Include the common FETK CMake utilities
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(FETKBuildFunctions)

# Set essential variables and paths for the project
set_basic_vars_and_paths()


########
# Options for modules to build
########

option(BUILD_MALOC "Set to TRUE to include the Maloc module in the build" TRUE)

option(BUILD_PUNC "Set to TRUE to include the Punc module in the build" TRUE)

option(BUILD_GAMER "Set to TRUE to include the Gamer module in the build" TRUE)

# SG has not been included in the CMake build at this point

option(BUILD_MC "Set to TRUE to include the MC module in the build" TRUE)

########
# Options
########

option(CREATE_PACKAGE "Use CPack to create an OS-dependent package" FALSE)


########
# Logic for build dependencies
########

if(BUILD_MC)
    set(BUILD_PUNC TRUE)
endif()

if(BUILD_PUNC OR BUILD_GAMER) # SG would be included in this if statement
    set(BUILD_MALOC TRUE)
endif()


########
# Build the modules
########

if(BUILD_MALOC)
    add_subdirectory(maloc)
endif()

if(BUILD_PUNC)
    add_subdirectory(punc)
endif()

if(BUILD_GAMER)
    add_subdirectory(gamer)
endif()

# SG would go here

if(BUILD_MC)
    add_subdirectory(mc)
endif()


########
# Package config
########

# TODO


########
# Packaging
########

if(CREATE_PACKAGE)

    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(CPACK_GENERATOR "TGZ")
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(CPACK_GENERATOR "TGZ")
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set(CPACK_GENERATOR "ZIP")
    endif()

    include(CPack)

endif()
