#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <gamer/tetgen.h>

static int expect_rejected(int bytecount, int itemcount)
{
    try {
        tetgenmesh::memorypool pool(bytecount, itemcount,
                                    tetgenmesh::POINTER, 0);
    } catch (int) {
        return 0;
    }
    fprintf(stderr, "pool(%d, %d) was not rejected\n", bytecount, itemcount);
    return 1;
}

/* Allocate across several blocks and use every byte of every item. */
static int pool_rollover()
{
    tetgenmesh::memorypool pool(40, 3, tetgenmesh::POINTER, 0);
    unsigned char *items[10];
    int i, j;

    for (i = 0; i < 10; ++i) {
        items[i] = (unsigned char *) pool.alloc();
        memset(items[i], i + 1, pool.itembytes);
    }
    for (i = 0; i < 10; ++i)
        for (j = 0; j < pool.itembytes; ++j)
            if (items[i][j] != i + 1)
                return 1;
    pool.dealloc(items[4]);
    return pool.alloc() == items[4] && pool.items == 10 ? 0 : 1;
}

static void unit_tetrahedron(tetgenio *in, int attributes)
{
    static const REAL coordinates[] = {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1};
    in->numberofpoints = 4;
    in->pointlist = new REAL[12];
    memcpy(in->pointlist, coordinates, sizeof(coordinates));
    in->numberofpointattributes = attributes;
}

static int mesh_with_attribute()
{
    tetgenio in, out;
    char switches[] = "Q";
    int i;

    unit_tetrahedron(&in, 1);
    in.pointattributelist = new REAL[4];
    for (i = 0; i < 4; ++i)
        in.pointattributelist[i] = 10.0 * (i + 1);
    /* Attribute-sized point records are allocated and filled during meshing;
       this TetGen mode does not copy unchanged attributes to the output. */
    tetrahedralize(switches, &in, &out);
    if (out.numberofpoints != 4 || out.numberoftetrahedra != 1)
        return 1;
    for (i = 0; i < 12; ++i)
        if (out.pointlist[i] != in.pointlist[i])
            return 1;
    return 0;
}

static int mesh_rejects_attribute_count()
{
    tetgenio in, out;
    char switches[] = "Q";

    unit_tetrahedron(&in, INT_MAX / 4);
    try {
        tetrahedralize(switches, &in, &out);
    } catch (int) {
        return 0;
    }
    fprintf(stderr, "oversized attribute count was not rejected\n");
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 2;
    if (!strcmp(argv[1], "rollover"))
        return pool_rollover();
    if (!strcmp(argv[1], "invalid"))
        return expect_rejected(0, 4) + expect_rejected(16, 0)
               + expect_rejected(-8, 4) + expect_rejected(INT_MAX - 4, 2);
    if (!strcmp(argv[1], "mesh"))
        return mesh_with_attribute();
    if (!strcmp(argv[1], "attribute-limit"))
        return mesh_rejects_attribute_count();
    return 2;
}
