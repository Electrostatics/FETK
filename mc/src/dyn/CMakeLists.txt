add_build_items(
    TYPE SOURCES
    ITEMS 
        dyn.c 
        svio.c
)

add_build_items(
    TYPE EXTERNAL_HEADERS
    ITEMS 
        mc/dyn.h
)

add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS 
        dyn_p.h
        svio_p.h
)
