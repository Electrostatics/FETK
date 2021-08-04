add_build_items(
    TYPE SOURCES
    ITEMS 
        CorrectNormals.C
        GenerateSphereMesh.C
        MarchingCube.C
        PDB2Mesh.C
        PDB2Volume.C
        ReadLattice.C
        ReadPDB.C
        ReadWriteMesh.C
        RegionGrowing.C
        SurfaceMesh.C
        SurfExtract.C
        SurfRefine.C
        SurfSmooth.C
)

add_build_items(
    TYPE EXTERNAL_HEADERS
    ITEMS 
        gamer/biom.h
)

add_build_items(
    TYPE INTERNAL_HEADERS
    ITEMS 
        MarchingCube.h
        PDB2Volume.h
)
