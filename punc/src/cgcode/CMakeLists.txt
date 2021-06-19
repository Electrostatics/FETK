# CMakeLists.txt for cgcode
# Author: N.S. Oblath
#
# Builds cgcode library

message(STATUS "Building cgcode")

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
    ITEMS vcgcode.h
)

# Add source files
# Commented labels were how the source files were organized in the original Makefile.am
add_build_items(
    TYPE SOURCES
    ITEMS
        # SSRCLIB
        scgdrv.c scg.c scr.c scrind.c spcg.c scgnr.c scgne.c spcgnr.c spcgne.c sppcg.c spcgca.c sdpchb.c scbfix.c sckchb.c scgchk.c sonest.c msstop.c
        # SAUXLIB
        r1mach.c sratqr.c
        # DSRCLIB
        dcgdrv.c dcg.c dcr.c dcrind.c dpcg.c dcgnr.c dcgne.c dpcgnr.c dpcgne.c dppcg.c dpcgca.c ddpchb.c dcbfix.c dckchb.c dcgchk.c donest.c mdstop.c
        # DAUXLIB
        d1mach.c dratqr.c depsln.c
)

message(STATUS "internal headers: ${INTERNAL_HEADERS}")
message(STATUS "external headers: ${EXTERNAL_HEADERS}")
message(STATUS "sources: ${SOURCES}")

add_library(cgcode ${SOURCES} ${EXTERNAL_HEADERS} ${INTERNAL_HEADERS})
#target_link_libraries(cgcode ${MALOC_EXT_LIBS})

install(FILES ${EXTERNAL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS cgcode DESTINATION ${CMAKE_INSTALL_LIBDIR})
