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
%%% rcsid="$Id: memchk.m,v 1.3 2010/08/12 05:17:11 fetk Exp $"
%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% File:     memchk.m
%%
%% Purpose:  Simple MATLAB script to perform a malloc analysis on MC.
%%
%% Notes:    Typing "memchk" in the MCshell will produce a MATLAB-compatible
%%           array containing the exact malloc profile of MC, broken into
%%           the major classes.  Cut-and-paste this array into MATLAB, and
%%           then run this script.  The result will be the exact byte count
%%           for the geometry and algebraic classes, presented as
%%           bytes/simplex, bytes/vertex, and number of equivalent N-vectors
%%           and L-vectors (N=#vertices, L=#simplicies).
%%
%% Author:   Michael Holst
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[rows,cols]=size(mc_memory);

xvec = - ones(rows,1);
xvec(rows) = 1;

acol = mc_memory(:,1);
bcol = mc_memory(:,3);
ccol = mc_memory(:,4);
columnchk   = norm( acol - (bcol - ccol) );
memorychk   = xvec' * mc_memory(:,1);
areachk     = xvec' * mc_memory(:,2);

fprintf(1,'----------------------------------------------------------------');
fprintf(1,'--------------\n');
fprintf(1,'accounting (should be zero): columnchk = %d\n', columnchk);
fprintf(1,'accounting (should be zero): memorychk = %d\n', memorychk);
fprintf(1,'accounting (should be zero): areachk   = %d\n', areachk);

vBytesV = ceil( mc_memory(2,1) / mc_vertex );
sBytesV = ceil( mc_memory(4,1) / mc_vertex );
vBytesS = ceil( mc_memory(2,1) / mc_simplex );
sBytesS = ceil( mc_memory(4,1) / mc_simplex );

fprintf(1,'----------------------------------------------------------------');
fprintf(1,'--------------\n');
fprintf(1,'N = vertex  count = %9d\n', mc_vertex);
fprintf(1,'L = simplex count = %9d\n', mc_simplex);

fprintf(1,'----------------------------------------------------------------');
fprintf(1,'--------------\n');
fprintf(1,'vertices:        %9d bytes/simplex (%9d double L-vectors)\n', ...
    vBytesS, ceil(vBytesS / 8));
fprintf(1,'simplices:       %9d bytes/simplex (%9d double L-vectors)\n', ...
    sBytesS, ceil(sBytesS / 8));
fprintf(1,'all geometry:    %9d bytes/simplex (%9d double L-vectors)\n', ...
    vBytesS+sBytesS, ceil( (vBytesS+sBytesS) / 8));

fprintf(1,'----------------------------------------------------------------');
fprintf(1,'--------------\n');
fprintf(1,'vertices:        %9d bytes/vertex  (%9d double N-vectors)\n', ...
    vBytesV, ceil(vBytesV / 8));
fprintf(1,'simplices:       %9d bytes/vertex  (%9d double N-vectors)\n', ...
    sBytesV, ceil(sBytesV / 8));
fprintf(1,'all geometry:    %9d bytes/vertex  (%9d double N-vectors)\n', ...
    vBytesV+sBytesV, ceil( (vBytesV+sBytesV) / 8));

fprintf(1,'----------------------------------------------------------------');
fprintf(1,'--------------\n');
aBytesV   = ceil( mc_memory(9,1) / mc_vertex );
fprintf(1,'fine space:      %9d bytes/vertex  (%9d double N-vectors)\n', ...
    aBytesV, ceil(aBytesV / 8));

numLevs = rows - 11;
xvec = ones(numLevs-1,1);
cbytes = xvec' * mc_memory(10:10+numLevs-2,1);
cBytesV = ceil( cbytes / mc_vertex );
fprintf(1,'coarse spaces:   %9d bytes/vertex  (%9d double N-vectors)\n', ...
    cBytesV, ceil(cBytesV / 8));

numLevs = rows - 10;
xvec = ones(numLevs,1);
abytes = xvec' * mc_memory(9:9+numLevs-1,1);
allBytesV = ceil( abytes / mc_vertex );
fprintf(1,'all spaces:      %9d bytes/vertex  (%9d double N-vectors)\n', ...
    allBytesV, ceil(allBytesV / 8));

fprintf(1,'----------------------------------------------------------------');
fprintf(1,'--------------\n');
total = mc_memory(rows,1);
totalV = ceil( total / mc_vertex );
fprintf(1,'total footprint: %9d bytes/vertex  (%9d double N-vectors)\n', ...
    totalV, ceil(totalV / 8));
fprintf(1,'----------------------------------------------------------------');
fprintf(1,'--------------\n');

