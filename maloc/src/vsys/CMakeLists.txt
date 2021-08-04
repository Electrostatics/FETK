add_build_items(
    TYPE SOURCES
    ITEMS 
        vio.c
        viofb.c
        vmem.c
        vnm.c
        vnmfb.c
        vpred.c
        vset.c
        ziofb.c
)

add_build_items(
    TYPE EXTERNAL_HEADERS
    ITEMS 
        maloc/vio.h
        maloc/vmem.h
        maloc/vnm.h
        maloc/vset.h
        maloc/vsys.h
        maloc/vpred.h
)

add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS 
        vio_p.h
        vmem_p.h
        vnm_p.h
        vpred_p.h
        vset_p.h
)

