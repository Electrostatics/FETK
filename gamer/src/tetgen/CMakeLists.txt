add_build_items(
    TYPE SOURCES
    ITEMS 
        predicates.cpp
        tetgen.cpp
)

add_build_items(
    TYPE EXTERNAL_HEADERS
    ITEMS 
        gamer/tetgen.h
)

add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS 
        tetgen_p.h
)
