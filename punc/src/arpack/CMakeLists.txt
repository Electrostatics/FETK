# CMakeLists.txt for arpack
# Author: N.S. Oblath
#
# Builds arpack library

message(STATUS "Building arpack")

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
    ITEMS varpack.h
)

# Add source files
set(SSRC sgetv0.c slaqrb.c sstqrb.c ssortc.c ssortr.c sstatn.c sstats.c snaitr.c snapps.c snaup2.c snaupd.c snconv.c sneigh.c sngets.c ssaitr.c ssapps.c ssaup2.c ssaupd.c ssconv.c sseigt.c ssgets.c sneupd.c sseupd.c ssesrt.c)
set(DSRC dgetv0.c dlaqrb.c dstqrb.c dsortc.c dsortr.c dstatn.c dstats.c dnaitr.c dnapps.c dnaup2.c dnaupd.c dnconv.c dneigh.c dngets.c dsaitr.c dsapps.c dsaup2.c dsaupd.c dsconv.c dseigt.c dsgets.c dneupd.c dseupd.c dsesrt.c)
set(CSRC cnaitr.c cnapps.c cnaup2.c cnaupd.c cneigh.c cneupd.c cngets.c cgetv0.c csortc.c cstatn.c)
set(ZSRC znaitr.c znapps.c znaup2.c znaupd.c zneigh.c zneupd.c zngets.c zgetv0.c zsortc.c zstatn.c)
set(UTIL cmout.c cvout.c dmout.c dvout.c icnteq.c icopy.c iset.c iswap.c ivout.c second.c smout.c svout.c zmout.c zvout.c)

add_build_items(
    TYPE SOURCES
    ITEMS ${SSRC} ${DSRC} ${CSRC} ${ZSRC} ${UTIL}
)

#message(STATUS "internal headers: ${INTERNAL_HEADERS}")
#message(STATUS "external headers: ${EXTERNAL_HEADERS}")
#message(STATUS "sources: ${SOURCES}")

add_library(arpack ${SOURCES} ${EXTERNAL_HEADERS} ${INTERNAL_HEADERS})
#target_link_libraries(arpack ${MALOC_EXT_LIBS})

install(FILES ${EXTERNAL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS arpack DESTINATION ${CMAKE_INSTALL_LIBDIR})
