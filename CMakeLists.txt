# Minimum version: 3.7.1 required by CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
cmake_minimum_required (VERSION 3.7.1)

# Parse the VERSION file
file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/VERSION VERSION_STRING)
string(REPLACE " " ";" VERSION_LIST ${VERSION_STRING})
list(GET VERSION_LIST 0 _PROJECT)
list(GET VERSION_LIST 2 _VERSION)

project(${_PROJECT}
        VERSION ${_VERSION}
        LANGUAGES C
)


########
# Options for modules to build
########

option(BUILD_MALOC "Set to TRUE to include the Maloc module in the build" TRUE)

option(BUILD_PUNC "Set to TRUE to include the Punc module in the build" TRUE)

option(BUILD_GAMER "Set to TRUE to include the Gamer module in the build" TRUE)

# SG has not been included in the CMake build at this point

option(BUILD_MC "Set to TRUE to include the MC module in the build" TRUE)


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
#    add_subdirectory(gamer)
endif()

# SG would go here

if(BUILD_MC)
#    add_subdirectory(mc)
endif()


########
# Package config
########

# TODO
