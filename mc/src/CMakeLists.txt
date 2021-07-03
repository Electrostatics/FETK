##########
# CMakeLists.txt for FETK/gamer/src
##########

# Initial setup for build
setup_for_build()


#####
# Build and install gamer
#####

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/base
    ${CMAKE_CURRENT_SOURCE_DIR}/bam
    ${CMAKE_CURRENT_SOURCE_DIR}/whb
    ${CMAKE_CURRENT_SOURCE_DIR}/aprx
    ${CMAKE_CURRENT_SOURCE_DIR}/gem
    ${CMAKE_CURRENT_SOURCE_DIR}/pde
    ${CMAKE_CURRENT_SOURCE_DIR}/nam
    ${CMAKE_CURRENT_SOURCE_DIR}/dyn
    ${CMAKE_CURRENT_SOURCE_DIR}/mcsh
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config/mccf.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/mccf.h
)
add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS ${CMAKE_CURRENT_BINARY_DIR}/mccf.h
)

add_subdirectory(base)
add_subdirectory(bam)
add_subdirectory(whb)
add_subdirectory(aprx)
add_subdirectory(gem)
add_subdirectory(pde)
add_subdirectory(nam)
add_subdirectory(dyn)
add_subdirectory(mcsh)

#message(STATUS "With sources: ${SOURCES}")
#message(STATUS "With external headers: ${EXTERNAL_HEADERS}")
#message(STATUS "With internal headers: ${INTERNAL_HEADERS}")

add_library(mc ${SOURCES} ${EXTERNAL_HEADERS} ${INTERNAL_HEADERS})
target_link_libraries(mc ${MC_EXT_LIBS} ${MC_INT_LIBS})

install(FILES ${EXTERNAL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS mc DESTINATION ${CMAKE_INSTALL_LIBDIR})
