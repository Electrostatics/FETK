# CMakeLists.txt for superlu
# Author: N.S. Oblath
#
# Builds superlu library

message(STATUS "Building superlu")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Prepare variables for the build
setup_for_build()

# Add header files
#add_build_items(
#    TYPE INTERNAL_HEADERS
#    ITEMS ...
#)

add_build_items(
    TYPE EXTERNAL_HEADERS
    ITEMS 
        punc/colamd.h
        punc/slu_cdefs.h
        punc/slu_Cnames.h
        punc/slu_dcomplex.h
        punc/slu_ddefs.h
        punc/slu_scomplex.h
        punc/slu_sdefs.h
        punc/slu_util.h
        punc/slu_zdefs.h
        punc/supermatrix.h
        punc/vsuperlu.h
)

# Add source files
# Commented labels were how the source files were organized in the original Makefile.am
### LAPACK 
set(LAAUX   lsame.c xerbla.c)
set(SLASRC  slacon.c )
set(DLASRC  dlacon.c)
set(CLASRC  clacon.c scsum1.c icmax1.c)
set(ZLASRC  zlacon.c dzsum1.c izmax1.c)
set(NOPTSRC slamch.c dlamch.c)

### SuperLU 
set(ALLAUX util.c memory.c get_perm_c.c mmd.c sp_coletree.c sp_preorder.c sp_ienv.c relax_snode.c heap_relax_snode.c colamd.c superlu_timer.c)
set(SLUSRC sgssv.c sgssvx.c ssp_blas2.c ssp_blas3.c sgscon.c slangs.c sgsequ.c slaqgs.c spivotgrowth.c sgsrfs.c sgstrf.c sgstrs.c scopy_to_ucol.c ssnode_dfs.c ssnode_bmod.c spanel_dfs.c spanel_bmod.c sreadhb.c scolumn_dfs.c scolumn_bmod.c spivotL.c spruneL.c smemory.c sutil.c smyblas2.c)
set(DLUSRC dgssv.c dgssvx.c dsp_blas2.c dsp_blas3.c dgscon.c dlangs.c dgsequ.c dlaqgs.c dpivotgrowth.c dgsrfs.c dgstrf.c dgstrs.c dcopy_to_ucol.c dsnode_dfs.c dsnode_bmod.c dpanel_dfs.c dpanel_bmod.c dreadhb.c dcolumn_dfs.c dcolumn_bmod.c dpivotL.c dpruneL.c dmemory.c dutil.c dmyblas2.c)
set(CLUSRC scomplex.c cgssv.c cgssvx.c csp_blas2.c csp_blas3.c cgscon.c clangs.c cgsequ.c claqgs.c cpivotgrowth.c cgsrfs.c cgstrf.c cgstrs.c ccopy_to_ucol.c csnode_dfs.c csnode_bmod.c cpanel_dfs.c cpanel_bmod.c creadhb.c ccolumn_dfs.c ccolumn_bmod.c cpivotL.c cpruneL.c cmemory.c cutil.c cmyblas2.c)
set(ZLUSRC dcomplex.c zgssv.c zgssvx.c zsp_blas2.c zsp_blas3.c zgscon.c zlangs.c zgsequ.c zlaqgs.c zpivotgrowth.c zgsrfs.c zgstrf.c zgstrs.c zcopy_to_ucol.c zsnode_dfs.c zsnode_bmod.c zpanel_dfs.c zpanel_bmod.c zreadhb.c zcolumn_dfs.c zcolumn_bmod.c zpivotL.c zpruneL.c zmemory.c zutil.c zmyblas2.c)

add_build_items(
    TYPE SOURCES
    ITEMS ${LAAUX} ${SLASRC} ${DLASRC} ${CLASRC} ${ZLASRC} ${NOPTSRC} ${ALLAUX} ${SLUSRC} ${DLUSRC} ${CLUSRC} ${ZLUSRC}
)

#message(STATUS "internal headers: ${INTERNAL_HEADERS}")
#message(STATUS "external headers: ${EXTERNAL_HEADERS}")
#message(STATUS "sources: ${SOURCES}")

add_library(superlu ${SOURCES} ${EXTERNAL_HEADERS} ${INTERNAL_HEADERS})
#target_link_libraries(superlu ${MALOC_EXT_LIBS})

install(FILES ${EXTERNAL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS superlu DESTINATION ${CMAKE_INSTALL_LIBDIR})
