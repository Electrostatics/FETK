%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% File:          mc17.m
%
% Dimension:     2
% Domain:        Two-dimensional bar occupying [0,1]x[-1/4,1/4]
% Boundary:      The left and right ends are Dirichlet (types 1 and 3, resp.).
%                The bottom and top are Neumann (types 2 and 4).
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

mcsf_begin=1;

      dim=2;    % intrinsic manifold dimension
    dimii=2;    % imbedding manifold dimension
 vertices=5;    % number of vertices
simplices=4;    % number of simplices

vert=[
%-------- ---- ----------------- ----------------- -----------------
% Vert-ID Chrt X0-Coordinate     X1-Coordinate     X2-Coordinate
%-------- ---- ----------------- ----------------- -----------------
0         0     0.0000000000e+00  0.0000000000e+00
1         0     1.0000000000e+00  0.0000000000e+00
2         0     0.0000000000e+00  1.0000000000e+00
3         0     1.0000000000e+00  1.0000000000e+00
4         0     5.0000000000e-01  5.0000000000e-01
];

simp=[
%-------- ---- ---- ------------------- ---------------------------------------
% Simp-ID Grp  Mat  Face-Types          Vertex-Numbers
%-------- ---- ---- ------------------- ---------------------------------------
0         0    0    0    1    0         1 4 0
1         0    0    0    2    0         2 4 3
2         0    0    0    0    1         2 0 4
3         0    0    0    0    4         1 3 4
];

mcsf_end=1;

