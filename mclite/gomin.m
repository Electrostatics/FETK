%GOMIN  A minimal driver script for using the MCLite package
%
% Usage: gomin
%
% Author:   Michael Holst
% rcsid="$Id: gomin.m,v 1.1.1.1 2007/04/27 08:28:05 hrg Exp $"

   %%% initialize
   clf;

   %%% create the mesh
   [VERT,SIMP]   = read(0);
   [N,eight]     = size(VERT);
   [L,seventeen] = size(SIMP);

   %%% plot the mesh
   subplot(2,2,1);
   draw(VERT,SIMP);
   title('Finite element mesh');

   %%% initialize the dirichlet function
   Ugg = u_d( VERT(1:N,1), VERT(1:N,2), VERT(1:N,6) );
   [NN,n] = size(Ugg);
   diriMask = vdiri(VERT(1:N,6));
   theMask = [];
   for i=1:n
      theMask = [ theMask , diriMask ];
   end
   Ugg = Ugg .* theMask;
   Ug = reshape( Ugg, N*n, 1 );

   %%% initialize the solution
   U = zeros(N*n,1);

   %%% assemble the discrete system
   parm = zeros(10,1);
   assKey = 2;
   [A,F]=assem(assKey, parm, U, Ug, VERT, SIMP);

   %%% build matrix copy with small entries dropped (for display only)
   tolZero = 1.0e-5;
   AA=A .* ( (A > tolZero) | (A < -tolZero) );

   %%% graph the matrix
   NODES = [];
   for i=1:n
      NODES = [ NODES ; VERT(:,1:2) ];
   end;
   subplot(2,2,3);
   gplot(AA,NODES,'r'); axis('equal'); axis('off');
   title('Graph of stiffness matrix');

   %%% show matrix structure
   [mm,nn] = size(A);
   subplot(2,2,4);
   spy(AA,'r');
   title('Nonzero structure of stiffness matrix');

   %%% solution of system
   U = A \ F;

   %%% plot the solution
   subplot(2,2,2);
   if (n==2)
      drawd(VERT,SIMP,U);
   else
      drawf(VERT,SIMP,U);
   end
   title('Finite element solution');

