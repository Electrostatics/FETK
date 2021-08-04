add_build_items(
    TYPE SOURCES
    ITEMS 
        whb.c 
        bvechb.c 
        hbtools.c 
        rcmat.c 
        brcmat.c 
        subopt.c
)

add_build_items(
    TYPE EXTERNAL_HEADERS
    ITEMS 
        mc/whb.h
)

add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS 
        brcmat_p.h
        bvechb_p.h
        cholesky_p.h
        hbtools_p.h
        rcmat_p.h
        subopt_p.h
        whb_p.h
)
