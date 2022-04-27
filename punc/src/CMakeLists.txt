##########
# CMakeLists.txt for FETK/punc/src
##########

# Initial setup for build
setup_for_build()

#####
# Included dependencies (if externals are missing)
#####

# optional build of vf2c
if(BUILD_VF2C)
    include_directories(vf2c vf2c/punc)
    add_subdirectory(vf2c)
    list(APPEND PUNC_INT_LIBS vf2c)
endif()

# optional build of cgcode
if(BUILD_CGCODE)
    include_directories(cgcode)
    add_subdirectory(cgcode)
    list(APPEND PUNC_INT_LIBS cgcode)
endif()

# optional build of pmg
if(BUILD_PMG)
    include_directories(pmg)
    add_subdirectory(pmg)
    list(APPEND PUNC_INT_LIBS pmg)
endif()

# optional build of blas
if(BUILD_BLAS)
    include_directories(blas)
    add_subdirectory(blas)
    list(APPEND PUNC_INT_LIBS blas)
else()
    list(APPEND PUNC_EXT_LIBS ${BLAS_LIBRARIES})
endif()

# optional build of arpack
if(BUILD_ARPACK)
    include_directories(arpack)
    add_subdirectory(arpack)
    list(APPEND PUNC_INT_LIBS arpack)
else()
    list(APPEND PUNC_EXT_LIBS ${ARPACK_LIBRARIES})
endif()

# optional build of superlu (actual build takes place below)
if(BUILD_SUPERLU)
    #include_directories(superlu)
    set(XSDK_ENABLE_Fortran OFF)
    set(enable_tests OFF)
    FetchContent_Declare( superlu
        GIT_REPOSITORY https://github.com/xiaoyeli/superlu.git
        GIT_TAG e8ed45225963c85a708c129bbcec17ec745d09f5
    )
    FetchContent_MakeAvailable( superlu )
    include_directories(${superlu_SOURCE_DIR}/SRC)
    list(APPEND PUNC_INT_LIBS superlu)
else()
    include_directories(${SUPERLU_INCLUDES})
    list(APPEND PUNC_EXT_LIBS ${SUPERLU_LIBRARIES})
endif()


#####
# Build and install punc
#####

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/base)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config/punccf.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/punccf.h
)
add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS ${CMAKE_CURRENT_BINARY_DIR}/punccf.h
)

add_subdirectory(base)

#message(STATUS "PUNC/src")
#message(STATUS "With sources: ${SOURCES}")
#message(STATUS "With external headers: ${EXTERNAL_HEADERS}")
#message(STATUS "With internal headers: ${INTERNAL_HEADERS}")
if(${SOURCES})
    message(FATAL_ERROR "The SOURCES variable should be empty because the PUNC build is currently setup to create an interface library.  If there are actual PUNC sources, this library should be made into an actual library")
endif()

add_library(punc ${SOURCES} ${EXTERNAL_HEADERS} ${INTERNAL_HEADERS})
target_link_libraries(punc ${PUNC_EXT_LIBS} ${PUNC_INT_LIBS})

get_target_property( SOURCE_TREE_INCLUDE_DIRS punc INCLUDE_DIRECTORIES )
target_include_directories( punc
    INTERFACE 
        "$<BUILD_INTERFACE:${SOURCE_TREE_INCLUDE_DIRS}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

install(FILES ${EXTERNAL_HEADERS} ${INTERNAL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS punc DESTINATION ${CMAKE_INSTALL_LIBDIR})
