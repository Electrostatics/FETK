add_build_items(
    TYPE SOURCES
    ITEMS 
        aprx.c 
        assem.c 
        bnode.c 
        estim.c 
        eval.c 
        io.c 
        node.c 
        parti.c 
        re.c
)

add_build_items(
    TYPE EXTERNAL_HEADERS
    ITEMS 
        mc/aprx.h
        mc/bnode.h
        mc/node.h
        mc/re.h
)

add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS 
        aprx_p.h
        bnode_p.h
        node_p.h
        re_p.h
)
