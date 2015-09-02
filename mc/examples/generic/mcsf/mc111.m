%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% File:          mc111.m
%
% Dimension:     3
% Domain:        Octahedron volume, made from eight tetrahedra
% Boundary:      Dirichlet
%
% rcsid="$Id: mc111.m,v 1.4 2010/08/12 05:17:19 fetk Exp $"
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
%%% rcsid="$Id: mc111.m,v 1.4 2010/08/12 05:17:19 fetk Exp $"
%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

mcsf_begin=1;

      dim=3;         % intrinsic manifold dimension
    dimii=3;         % imbedding manifold dimension
 vertices=7;         % number of vertices
simplices=8;         % number of simplices

vert=[
%-------- ---- ----------------- ----------------- -----------------
% Vert-ID Chrt X-Coordinate      Y-Coordinate      Z-Coordinate
%-------- ---- ----------------- ----------------- -----------------
0         0     0.0000000000e+00  0.0000000000e+00  0.0000000000e+00
1         0     0.0000000000e+00  0.0000000000e+00  1.0000000000e+02
2         0     0.0000000000e+00  0.0000000000e+00 -1.0000000000e+02
3         0     1.0000000000e+02  0.0000000000e+00  0.0000000000e+00
4         0     0.0000000000e+00  1.0000000000e+02  0.0000000000e+00
5         0    -1.0000000000e+02  0.0000000000e+00  0.0000000000e+00
6         0     0.0000000000e+00 -1.0000000000e+02  0.0000000000e+00
];

simp=[
%-------- ---- ---- ------------------- ---------------------------------------
% Simp-ID Grp  Mat  Face-Types          Vertex-Numbers
%-------- ---- ---- ------------------- ---------------------------------------
0         0    0    1    0    0    0    0 3 4 1
1         0    0    1    0    0    0    0 6 3 1
2         0    0    1    0    0    0    0 4 5 1
3         0    0    1    0    0    0    0 5 6 1
4         0    0    1    0    0    0    0 4 3 2
5         0    0    1    0    0    0    0 3 6 2
6         0    0    1    0    0    0    0 5 4 2
7         0    0    1    0    0    0    0 6 5 2
];

mcsf_end=1;

