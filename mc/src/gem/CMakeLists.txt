add_build_items(
    TYPE SOURCES
    ITEMS 
        vel.c 
        ves.c 
        gem.c 
        gemchk.c 
        gemdisp.c 
        gemg.c 
        gemgen.c 
        gemio.c 
        gemref.c 
        gemunref.c 
        gemcube.c
)

add_build_items(
    TYPE EXTERNAL_HEADERS
    ITEMS 
        mc/gem.h
        mc/vel.h
        mc/ves.h
)

add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS 
        gem_p.h
        vel_p.h
        ves_p.h
)
