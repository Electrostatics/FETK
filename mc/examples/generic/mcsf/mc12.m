%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% File:          mc12.m
%
% Dimension:     2 (imbedded in 3)
% Domain:        Two small Octahedrons, unit normals pointing IN
%                imbedded in one large Octahedron, unit normals pointing OUT
% Boundary:      ?
%
% rcsid="$Id: mc12.m,v 1.4 2010/08/12 05:17:20 fetk Exp $"
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% MC = < Manifold Code >
%%% Copyright (C) 1994-- Michael Holst 
%%%
%%% This library is free software; you can redistribute it and/or 
%%% modify it under the terms of the GNU Lesser General Public 
%%% License as published by the Free Software Foundation; either  
%%% version 2.1 of the License, or (at your option) any later version. 
%%%
%%% This library is distributed in the hope that it will be useful, 
%%% but WITHOUT ANY WARRANTY; without even the implied warranty of             
%%% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
%%% Lesser General Public License for more details. 
%%%
%%% You should have received a copy of the GNU Lesser General Public 
%%% License along with this library; if not, write to the Free Software  
%%% Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA   
%%%
%%% rcsid="$Id: mc12.m,v 1.4 2010/08/12 05:17:20 fetk Exp $"
%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

mcsf_begin=1;

      dim=2;         % intrinsic manifold dimension
    dimii=3;         % imbedding manifold dimension
 vertices=18;        % number of vertices
simplices=24;        % number of simplices

vert=[
%-------- ---- ----------------- ----------------- -----------------
% Vert-ID Chrt X-Coordinate      Y-Coordinate      Z-Coordinate
%-------- ---- ----------------- ----------------- -----------------
0         0     0.0000000000e+00  0.0000000000e+00 -4.0000000000e+00
1         0     0.0000000000e+00  0.0000000000e+00 -6.0000000000e+00
2         0     7.0710680000e-01  7.0710680000e-01 -5.0000000000e+00
3         0    -7.0710680000e-01  7.0710680000e-01 -5.0000000000e+00
4         0    -7.0710680000e-01 -7.0710680000e-01 -5.0000000000e+00
5         0     7.0710680000e-01 -7.0710680000e-01 -5.0000000000e+00
6         0     0.0000000000e+00  0.0000000000e+00  6.0000000000e+00
7         0     0.0000000000e+00  0.0000000000e+00  4.0000000000e+00
8         0     7.0710680000e-01  7.0710680000e-01  5.0000000000e+00
9         0    -7.0710680000e-01  7.0710680000e-01  5.0000000000e+00
10        0    -7.0710680000e-01 -7.0710680000e-01  5.0000000000e+00
11        0     7.0710680000e-01 -7.0710680000e-01  5.0000000000e+00
12        0     0.0000000000e+00  0.0000000000e+00  2.0000000000e+01
13        0     0.0000000000e+00  0.0000000000e+00 -2.0000000000e+01
14        0     1.4000000000e+01  1.4000000000e+01  0.0000000000e+00
15        0    -1.4000000000e+01  1.4000000000e+01  0.0000000000e+00
16        0    -1.4000000000e+01 -1.4000000000e+01  0.0000000000e+00
17        0     1.4000000000e+01 -1.4000000000e+01  0.0000000000e+00
];

simp=[
%-------- ---- ---- ------------------- ---------------------------------------
% Simp-ID Grp  Mat  Face-Types          Vertex-Numbers
%-------- ---- ---- ------------------- ---------------------------------------
0         0    0    0    0    0         0 2 3
1         0    0    0    0    0         0 3 4
2         0    0    0    0    0         0 4 5
3         0    0    0    0    0         0 5 2
4         0    0    0    0    0         1 2 3
5         0    0    0    0    0         1 3 4
6         0    0    0    0    0         1 4 5
7         0    0    0    0    0         1 5 2
8         0    0    0    0    0         6 8 9
9         0    0    0    0    0         6 9 10
10        0    0    0    0    0         6 10 11
11        0    0    0    0    0         6 11 8
12        0    0    0    0    0         7 8 9
13        0    0    0    0    0         7 9 10
14        0    0    0    0    0         7 10 11
15        0    0    0    0    0         7 11 8
16        0    0    0    0    0         12 14 15
17        0    0    0    0    0         12 15 16
18        0    0    0    0    0         12 16 17
19        0    0    0    0    0         12 17 14
20        0    0    0    0    0         13 14 15
21        0    0    0    0    0         13 15 16
22        0    0    0    0    0         13 16 17
23        0    0    0    0    0         13 17 14
];

mcsf_end=1;

