# CMakeLists.txt for blas
# Author: N.S. Oblath
#
# Builds BLAS library

message(STATUS "Building blas")

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
    ITEMS vblas.h
)

# Add source files
# Commented labels were how the source files were organized in the original Makefile.am
set(ALLBLAS lsame.c xerbla.c)

set(SBLAS1 isamax.c sasum.c saxpy.c scopy.c sdot.c snrm2.c srot.c srotg.c sscal.c sswap.c)
set(DBLAS1 idamax.c dasum.c daxpy.c dcopy.c ddot.c dnrm2.c drot.c drotg.c dscal.c dswap.c)
set(CBLAS1 scasum.c scnrm2.c icamax.c caxpy.c ccopy.c cdotc.c cdotu.c csscal.c crotg.c cscal.c cswap.c)
set(ZBLAS1 dcabs1.c dzasum.c dznrm2.c izamax.c zaxpy.c zcopy.c zdotc.c zdotu.c zdscal.c zrotg.c zscal.c zswap.c)
# CB1AUX  = isamax.c sasum.c saxpy.c scopy.c snrm2.c sscal.c
# ZB1AUX  = idamax.c dasum.c daxpy.c dcopy.c dnrm2.c dscal.c

set(SBLAS2 sgemv.c sgbmv.c ssymv.c ssbmv.c sspmv.c strmv.c stbmv.c stpmv.c strsv.c stbsv.c stpsv.c sger.c ssyr.c sspr.c ssyr2.c sspr2.c)
set(DBLAS2 dgemv.c dgbmv.c dsymv.c dsbmv.c dspmv.c dtrmv.c dtbmv.c dtpmv.c dtrsv.c dtbsv.c dtpsv.c dger.c dsyr.c dspr.c dsyr2.c dspr2.c)
set(CBLAS2 cgemv.c cgbmv.c chemv.c chbmv.c chpmv.c ctrmv.c ctbmv.c ctpmv.c ctrsv.c ctbsv.c ctpsv.c cgerc.c cgeru.c cher.c chpr.c cher2.c chpr2.c)
set(ZBLAS2 zgemv.c zgbmv.c zhemv.c zhbmv.c zhpmv.c ztrmv.c ztbmv.c ztpmv.c ztrsv.c ztbsv.c ztpsv.c zgerc.c zgeru.c zher.c zhpr.c zher2.c zhpr2.c)

set(SBLAS3 sgemm.c ssymm.c ssyrk.c ssyr2k.c strmm.c strsm.c )
set(DBLAS3 dgemm.c dsymm.c dsyrk.c dsyr2k.c dtrmm.c dtrsm.c)
set(CBLAS3 cgemm.c csymm.c csyrk.c csyr2k.c ctrmm.c ctrsm.c chemm.c cherk.c cher2k.c)
set(ZBLAS3 zgemm.c zsymm.c zsyrk.c zsyr2k.c ztrmm.c ztrsm.c zhemm.c zherk.c zher2k.c)

set(EXTRA sdsdot.c dsdot.c srotm.c srotmg.c drotm.c drotmg.c csrot.c zdrot.c)

add_build_items(
    TYPE SOURCES
    ITEMS ${ALLBLAS} ${SBLAS1} ${DBLAS1} ${CBLAS1} ${ZBLAS1} ${SBLAS2} ${DBLAS2} ${CBLAS2} ${ZBLAS2} ${SBLAS3} ${DBLAS3} ${CBLAS3} ${ZBLAS3} ${EXTRA}
)

#message(STATUS "internal headers: ${INTERNAL_HEADERS}")
#message(STATUS "external headers: ${EXTERNAL_HEADERS}")
#message(STATUS "sources: ${SOURCES}")

add_library(blas ${SOURCES} ${EXTERNAL_HEADERS} ${INTERNAL_HEADERS})
#target_link_libraries(pmg ${MALOC_EXT_LIBS})

install(FILES ${EXTERNAL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS blas DESTINATION ${CMAKE_INSTALL_LIBDIR})
