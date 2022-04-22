##########
# CMakeLists.txt for FETK/maloc/src
##########

# Initial setup for build
setup_for_build()


#####
# Build and install maloc
#####

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/base)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/psh)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vsh)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vsys)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config/maloccf.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/maloccf.h
)
add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS ${CMAKE_CURRENT_BINARY_DIR}/maloccf.h
)

add_subdirectory(base)
add_subdirectory(psh)
add_subdirectory(vsh)
add_subdirectory(vsys)

#message(STATUS "With sources: ${SOURCES}")
#message(STATUS "With external headers: ${EXTERNAL_HEADERS}")
#message(STATUS "With internal headers: ${INTERNAL_HEADERS}")

add_library(maloc ${SOURCES} ${EXTERNAL_HEADERS} ${INTERNAL_HEADERS})
target_link_libraries(maloc ${MALOC_EXT_LIBS})

get_target_property( SOURCE_TREE_INCLUDE_DIRS maloc INCLUDE_DIRECTORIES )
target_include_directories( maloc
    INTERFACE 
        "$<BUILD_INTERFACE:${SOURCE_TREE_INCLUDE_DIRS}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

install(FILES ${EXTERNAL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS maloc DESTINATION ${CMAKE_INSTALL_LIBDIR})
