macro(add_items TYPE)

    # Make sure the TYPE argument is valid
    if(NOT "${TYPE}" IN_LIST ALLOWABLE_TYPES)
        message(
            FATAL_ERROR
            "Passed an invalid type to add_items macro.  "
            "Must be one of ${ALLOWABLE_TYPES}.  "
            "Was ${TYPE}."
        )
    endif()
    
    # The items to add will be any additional parameters beyond TYPE
    set(ITEMS ${ARGN})
    
    # Add each item successively
    foreach(ITEM ${ITEMS})
    
        # If this folder is not src, append the relative path to the item
        #if(PATH)
        #    set(ITEM "${PATH}/${ITEM}")
        #endif()

        get_filename_component(ABS_ITEM ${ITEM} ABSOLUTE)
        
        # Add the item to the appropriately typed list
        list(APPEND ${TYPE} "${ABS_ITEM}")
    endforeach()
    
    # If this folder is not the library-build directory, push the updated item list to the parent scope
    if(NOT LIB_BUILD_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
        set(${TYPE} ${${TYPE}} PARENT_SCOPE)
    endif()

endmacro()

# Setup variables for build items
set(LIB_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ALLOWABLE_TYPES "SOURCES;EXTERNAL_HEADERS;INTERNAL_HEADERS")
set(SOURCES)
set(EXTERNAL_HEADERS)
set(INTERNAL_HEADERS)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/base)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/psh)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vsh)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vsys)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config/maloccf.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/maloccf.h
)
add_items(
    INTERNAL_HEADERS
    ${CMAKE_CURRENT_BINARY_DIR}/maloccf.h
)


add_subdirectory(base)
add_subdirectory(psh)
add_subdirectory(vsh)
add_subdirectory(vsys)

message(STATUS "With sources: ${SOURCES}")
message(STATUS "With external headers: ${EXTERNAL_HEADERS}")
message(STATUS "With internal headers: ${INTERNAL_HEADERS}")

add_library(maloc ${SOURCES} ${EXTERNAL_HEADERS} ${INTERNAL_HEADERS})
target_link_libraries(maloc ${MALOC_EXT_LIBS})

install(FILES ${EXTERNAL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS maloc DESTINATION ${CMAKE_INSTALL_LIBDIR})

