add_build_items(
    TYPE SOURCES
    ITEMS 
        bmat.c
        bsolv.c
        bvec.c
        mat.c
        matcopy.c
        matln.c
        mtool.c
        slu.c
        vec.c
        vec3.c
        zslu.c
)

add_build_items(
    TYPE EXTERNAL_HEADERS
    ITEMS 
        mc/bam.h
        mc/bmat.h
        mc/bvec.h
        mc/mat.h
        mc/mtool.h
        mc/slu.h
        mc/vec.h
        mc/vec3.h
        mc/zslu.h
)

add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS 
        bam_p.h
        bmat_p.h
        bvec_p.h
        mat_p.h
        mtool_p.h
        slu_p.h
        vec_p.h
        vec3_p.h
        zslu_p.h
)
