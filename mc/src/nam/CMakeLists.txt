add_build_items(
    TYPE SOURCES
    ITEMS 
        am.c 
        lsolv.c 
        nsolv.c
)

add_build_items(
    TYPE EXTERNAL_HEADERS
    ITEMS 
        mc/am.h
        mc/nam.h
)

add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS 
        am_p.h
        nam_p.h
)
