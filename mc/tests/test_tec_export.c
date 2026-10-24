#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mc/gem.h>

int main(int argc, char **argv)
{
    Gem gem = {0};
    SS *simplex;
    VV *vertices[4];
    Vio *sock;
    double field[4] = {10, 20, 30, 40};
    double *fields[MAXV] = {field};
    char filename[64], line[512], expected[128];
    FILE *file;
    int dim, i, axis, connection, failures = 0;
    double value;

    if (argc != 2 || (strcmp(argv[1], "2") && strcmp(argv[1], "3")))
        return 2;
    dim = atoi(argv[1]);
    gem.dim = dim;
    gem.dimII = 3;
    gem.dimVV = dim + 1;
    gem.vertices = Vset_ctor(VNULL, "VV", sizeof(VV), 4, 0);
    gem.simplices = Vset_ctor(VNULL, "SS", sizeof(SS), 1, 0);
    for (i = 0; i <= dim; ++i) {
        vertices[i] = (VV *)Vset_create(gem.vertices);
        VV_init(vertices[i], dim, i);
        for (axis = 0; axis < 3; ++axis)
            VV_setCoord(vertices[i], axis, i == axis + 1 ? 1.0 : 0.0);
    }
    simplex = (SS *)Vset_create(gem.simplices);
    SS_init(simplex, dim, 0);
    for (i = 0; i <= dim; ++i)
        SS_setVertex(simplex, i, vertices[i]);

    snprintf(filename, sizeof(filename), "tec-export-%d.dat", dim);
    Vio_start();
    sock = Vio_ctor("FILE", "ASC", VNULL, filename, "w");
    if (sock == VNULL || Vio_connect(sock, 0) < 0)
        return 2;
    Gem_writeTEC(&gem, sock, 1, fields);
    Vio_connectFree(sock);
    Vio_dtor(&sock);
    Vio_stop();

    file = fopen(filename, "r");
    if (file == NULL)
        return 2;
    do {
        if (fgets(line, sizeof(line), file) == NULL)
            return 1;
    } while (strncmp(line, "ZONE ", 5));
    snprintf(expected, sizeof(expected),
             "ZONE T=\"%s\", N=%d, E=1, F=FEPOINT, ET=\"%s\"\n",
             dim == 2 ? "TRIANGLES" : "TETRAHEDRA", dim + 1,
             dim == 2 ? "TRIANGLE" : "TETRAHEDRON");
    if (strcmp(line, expected))
        ++failures;
    for (i = 0; i <= dim; ++i) {
        for (axis = 0; axis < dim; ++axis) {
            if (fscanf(file, "%lf", &value) != 1 ||
                value != (i == axis + 1 ? 1.0 : 0.0))
                ++failures;
        }
        if (fscanf(file, "%lf", &value) != 1 || value != field[i])
            ++failures;
    }
    for (i = 0; i <= dim; ++i)
        if (fscanf(file, "%d", &connection) != 1 || connection != i + 1)
            ++failures;
    fclose(file);
    remove(filename);
    Vset_dtor(&gem.simplices);
    Vset_dtor(&gem.vertices);
    if (failures)
        fprintf(stderr, "TEC export: %d output mismatches\n", failures);
    return failures ? 1 : 0;
}
