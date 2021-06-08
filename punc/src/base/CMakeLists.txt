add_build_items(
    TYPE SOURCES
    ITEMS punc_base.c
)

add_build_items(
    TYPE EXTERNAL_HEADERS
    ITEMS punc/punc.h punc/punc_base.h
)

add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS punc_base_p.h
)
