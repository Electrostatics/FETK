add_build_items(
    TYPE SOURCES
    ITEMS 
        psh.c
        vcom.c
        vmp.c
        vmpi.c
)

add_build_items(
    TYPE EXTERNAL_HEADERS
    ITEMS 
        maloc/psh.h
        maloc/vcom.h
        maloc/vmp.h
        maloc/vmpi.h
)

add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS 
        psh_p.h
        vcom_p.h
        vmpi_p.h
        vmp_p.h
)
