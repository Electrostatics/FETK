add_build_items(
    TYPE SOURCES
    ITEMS 
        maloc_base.c
)

add_build_items(
    TYPE EXTERNAL_HEADERS
    ITEMS 
        maloc/maloc.h
        maloc/maloc_base.h
)

add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS 
        maloc_base_p.h
)
