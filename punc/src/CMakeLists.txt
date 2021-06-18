##########
# CMakeLists.txt for FETK/punc/srcdir
##########

# Initial setup for build
setup_for_build()

#####
# Included dependencies (if externals are missing)
#####

# optional build of vf2c
if(BUILD_VF2C)
#    include_directories(vf2c)
#    add_subdirectory(vf2c)
endif()

# optional build of blas
if(BUILD_BLAS)
    include_directories(blas)
    add_subdirectory(blas)
endif()

# optional build of lapack
if(BUILD_LAPACK)
    include_directories(lapack)
    add_subdirectory(lapack)
endif()

# optional build of amd
if(BUILD_AMD)
    include_directories(amd)
    add_subdirectory(amd)
endif()

# optional build of umfpack
if(BUILD_UMFPACK)
    include_directories(umfpack)
    add_subdirectory(umfpack)
endif()

# optional build of superlu
if(BUILD_SUPERLU)
    include_directories(superlu)
    add_subdirectory(superlu)
endif()

# optional build of arpack
if(BUILD_ARPACK)
    include_directories(arpack)
    add_subdirectory(arpack)
endif()

# optional build of cgcode
if(BUILD_CGCODE)
    include_directories(cgcode)
    add_subdirectory(cgcode)
endif()

# optional build of pmg
if(BUILD_PMG)
include_directories()
    add_subdirectory(pmg)
endif()


#####
# Build and install punc
#####

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config/punccf.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/punccf.h
)
add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS ${CMAKE_CURRENT_BINARY_DIR}/punccf.h
)

add_subdirectory(base)

message(STATUS "With sources: ${SOURCES}")
message(STATUS "With external headers: ${EXTERNAL_HEADERS}")
message(STATUS "With internal headers: ${INTERNAL_HEADERS}")

add_library(punc ${SOURCES} ${EXTERNAL_HEADERS} ${INTERNAL_HEADERS})
target_link_libraries(punc ${PUNC_EXT_LIBS} ${PUNC_INT_LIBS})

install(FILES ${EXTERNAL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS punc DESTINATION ${CMAKE_INSTALL_LIBDIR})