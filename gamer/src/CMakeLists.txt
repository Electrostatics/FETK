##########
# CMakeLists.txt for FETK/gamer/src
##########

# Initial setup for build
setup_for_build()


#####
# Build and install gamer
#####

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/base)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/triangle)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tetgen)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/biom)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config/gamercf.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/gamercf.h
)
add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS ${CMAKE_CURRENT_BINARY_DIR}/gamercf.h
)

add_subdirectory(base)
add_subdirectory(triangle)
add_subdirectory(tetgen)
add_subdirectory(biom)

#message(STATUS "With sources: ${SOURCES}")
#message(STATUS "With external headers: ${EXTERNAL_HEADERS}")
#message(STATUS "With internal headers: ${INTERNAL_HEADERS}")

add_library(gamer ${SOURCES} ${EXTERNAL_HEADERS} ${INTERNAL_HEADERS})
target_link_libraries(gamer ${GAMER_EXT_LIBS} ${GAMER_INT_LIBS})

install(FILES ${EXTERNAL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS gamer DESTINATION ${CMAKE_INSTALL_LIBDIR})
