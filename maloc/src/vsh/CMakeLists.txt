add_build_items(
    TYPE SOURCES
    ITEMS 
        vlex.c
        vpars.c
        vpup.c
        vsh.c
        vyacc.c
)

add_build_items(
    TYPE EXTERNAL_HEADERS
    ITEMS 
        maloc/vsh.h
)

add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS 
        vpup.h
        vsh_p.h
        vyacc.h
)
