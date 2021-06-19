# CMakeLists.txt for pmg
# Author: N.S. Oblath
#
# Builds pmg library

message(STATUS "Building pmg")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Prepare variables for the build
setup_for_build()

# Add header files
#add_build_items(
#    TYPE EXTERNAL_HEADERS
#    ITEMS ...
#)

add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS vpmg.h
)

# Add source files
# Commented labels were how the source files were organized in the original Makefile.am
add_build_items(
    TYPE SOURCES
    ITEMS buildAd.c buildBd.c buildGd.c buildPd.c cgd.c cgmgd.c cgmgdrvd.c gsd.c matvecd.c mblasd.c mgcsd.c mgdrvd.c mgfasd.c mgsubd.c mikpckd.c mlinpckd.c ncgd.c ncgdrvd.c newdrvd.c newtond.c ngsd.c ngsdrvd.c ninterpd.c nrchd.c nrchdrvd.c nsmoothd.c nsord.c nsordrvd.c nwjd.c nwjdrvd.c powerd.c rchd.c smoothd.c sord.c wjd.c
)

message(STATUS "internal headers: ${INTERNAL_HEADERS}")
message(STATUS "external headers: ${EXTERNAL_HEADERS}")
message(STATUS "sources: ${SOURCES}")

add_library(pmg ${SOURCES} ${EXTERNAL_HEADERS} ${INTERNAL_HEADERS})
#target_link_libraries(pmg ${MALOC_EXT_LIBS})

install(FILES ${EXTERNAL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS pmg DESTINATION ${CMAKE_INSTALL_LIBDIR})
