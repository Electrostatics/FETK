#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <mc/gem.h>

static void one_chart(int dim, int dimII, int type, int chart[],
                      double coordinates[][3], int count)
{
    /* All test vertices already share one Cartesian chart. */
    (void)dim;
    (void)dimII;
    (void)type;
    (void)chart;
    (void)coordinates;
    (void)count;
}

static int check_edge(Gem *gem, SS *simplex, int face, int longest)
{
    int p, q, i, j, axis, high, low, best_high = -1, best_low = -1;
    int expected = -1, actual, count = face < 0 ? gem->dim + 1 : 3;
    double squared, best_squared = -1.0, length;

    for (q = 1; q < count; ++q) {
        for (p = 0; p < q; ++p) {
            VV *first, *second;
            i = face < 0 ? p : vmapF[face][p];
            j = face < 0 ? q : vmapF[face][q];
            first = SS_vertex(simplex, i);
            second = SS_vertex(simplex, j);
            squared = 0.0;
            for (axis = 0; axis < 3; ++axis) {
                double difference = VV_coord(first, axis)
                                  - VV_coord(second, axis);
                squared += difference * difference;
            }
            high = VMAX2(VV_id(first), VV_id(second));
            low = VMIN2(VV_id(first), VV_id(second));
            if (expected < 0
                || (longest ? squared > best_squared : squared < best_squared)
                || (squared == best_squared
                    && (longest
                        ? (high < best_high
                           || (high == best_high && low < best_low))
                        : (high > best_high
                           || (high == best_high && low > best_low))))) {
                expected = vmapE[i][j];
                best_squared = squared;
                best_high = high;
                best_low = low;
            }
        }
    }
    actual = longest ? Gem_longestEdge(gem, simplex, face, &length)
                     : Gem_shortestEdge(gem, simplex, face, &length);
    if (actual != expected || fabs(length - sqrt(best_squared)) > 1e-12) {
        fprintf(stderr,
                "%s: dim=%d face=%d ids=[%d,%d,%d,%d] "
                "expected edge=%d (%d,%d), got=%d length=%.17g\n",
                longest ? "longest" : "shortest", gem->dim, face,
                VV_id(SS_vertex(simplex, 0)), VV_id(SS_vertex(simplex, 1)),
                VV_id(SS_vertex(simplex, 2)),
                gem->dim == 3 ? VV_id(SS_vertex(simplex, 3)) : -1,
                expected, best_high, best_low, actual, length);
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    const int ids[][4] = {
        {0, 1, 2, 3},
        {1, 2, 21, 22},
        {100, 101, 102, 103},
        {INT_MAX - 3, INT_MAX - 2, INT_MAX - 1, INT_MAX}
    };
    /* Squared lengths are exact integers: ties are exact, not near-ties. */
    const double coordinates[4][3] = {
        {1, 1, 1}, {1, -1, -1}, {-1, 1, -1}, {-1, -1, 1}
    };
    PDE pde = {0};
    Gem gem = {0};
    int longest, dim, group, stretch, a, b, c, d, vertex, axis, face;
    int failures = 0, checks = 0;
    VV *vertices[4];
    SS *simplex;

    if (argc != 2
        || (strcmp(argv[1], "longest") && strcmp(argv[1], "shortest"))) {
        fprintf(stderr, "Usage: test_edge_order longest|shortest\n");
        return 2;
    }
    longest = !strcmp(argv[1], "longest");
    pde.oneChart = one_chart;
    gem.pde = &pde;
    gem.dimII = 3;
    for (dim = 2; dim <= 3; ++dim) {
        gem.dim = dim;
        simplex = SS_ctor(dim, 0);
        for (vertex = 0; vertex <= dim; ++vertex) {
            vertices[vertex] = VV_ctor(dim, vertex);
        }
        for (group = 0; group < 4; ++group) {
            for (stretch = 1; stretch <= 2; ++stretch) {
                for (vertex = 0; vertex <= dim; ++vertex) {
                    VV_setId(vertices[vertex], ids[group][vertex]);
                    for (axis = 0; axis < 3; ++axis) {
                        VV_setCoord(vertices[vertex], axis,
                                    coordinates[vertex][axis]
                                    * (axis == 0 ? stretch : 1));
                    }
                }
                for (a = 0; a <= dim; ++a)
                    for (b = 0; b <= dim; ++b)
                        for (c = 0; c <= dim; ++c)
                            for (d = 0; d <= dim; ++d) {
                                if (a == b || a == c || b == c) continue;
                                if (dim == 2 && d != 0) continue;
                                if (dim == 3
                                    && (d == a || d == b || d == c)) continue;
                                SS_setVertex(simplex, 0, vertices[a]);
                                SS_setVertex(simplex, 1, vertices[b]);
                                SS_setVertex(simplex, 2, vertices[c]);
                                if (dim == 3)
                                    SS_setVertex(simplex, 3, vertices[d]);
                                for (face = -1; face < (dim == 3 ? 4 : 0);
                                     ++face) {
                                    failures += check_edge(
                                        &gem, simplex, face, longest);
                                    ++checks;
                                }
                            }
            }
        }
        SS_dtor(&simplex);
        for (vertex = 0; vertex <= dim; ++vertex) VV_dtor(&vertices[vertex]);
    }
    printf("%s: %d checks, %d failures (sizeof(long)=%lu)\n",
           argv[1], checks, failures, (unsigned long)sizeof(long));
    return failures ? 1 : 0;
}
