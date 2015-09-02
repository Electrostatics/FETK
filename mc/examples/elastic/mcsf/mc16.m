%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% File:          mc16.m
%
% Dimension:     2
% Domain:        Two-dimensional bar occupying [0,1]x[-1/4,1/4]
% Boundary:      The left and right ends are Dirichlet (types 1 and 3, resp.).
%                The bottom and top are Neumann (types 2 and 4).
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

mcsf_begin=1;

      dim=2;         % intrinsic manifold dimension
    dimii=2;         % imbedding manifold dimension
 vertices=4;         % number of vertices
simplices=2;         % number of simplices

vert=[
%-------- ---- ------  ------
% Vert-ID Chrt X-Coor  Y-Coor
%-------- ---- ------  ------
0         0    0.0     0.0
1         0    1.0     0.0
2         0    0.0     1.0
3         0    1.0     1.0
];

simp=[
%-------- ---- ---- ------------------- ---------------------------------------
% Simp-ID Grp  Mat  Face-Types          Vertex-Numbers
%-------- ---- ---- ------------------- ---------------------------------------
0         0    0    0    1    1         0 1 2
1         0    0    2    0    4         1 3 2
];

mcsf_end=1;

