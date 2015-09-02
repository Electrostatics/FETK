%GO  Controlling driver script for using the MCLite package
%
% Usage: go
%
% Author:   Michael Holst
% rcsid="$Id: go.m,v 1.2 2008/03/12 06:23:07 fetk Exp $"

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%% global variables: prolongators for all levels
global level P_12 P_23 P_34 P_45 P_56 P_67 P_78 P_89; 

%%% setup the MCLite library paths
setpath

%%% visualization parameters
igenPS   = 0;    %%% MATLAB generate postscript (0=no,1=yes)
gv       = 0;    %%% MCsg/Geomview plot of manifold mesh (0=none,1=yes)
gvs      = 0;    %%% MCsg/Geomview plot of solution mesh (0=none,1=yes)
socktype = 1;    %%% UNIX domain or INET sockets (0=UNIX domain, 1=INET)

%%% geometry and solver parameters
chkkey   = 0;    %%% conformity check mesh (0=no,1=yes--check is slow)
levels   = 7;    %%% num of refinements plus one
solkey   = 1;    %%% solve key (0=no, 1=yes)

%%% error estimation parameters
estkey   = 2;    %%% estimator type (0=mark all,1=geom,2=a posteriori)
esttol   = 0.1;  %%% estimator tolerance (if exceeded then refine)

%%% refinement parameters
%%%
%%% NOTES:  Here are some refinement parameter combinations of importance:
%%%
%%%   Algorithm                                       refkey closeKey  markKey
%%%   ---------                                       ------ --------  -------
%%%   Rivara/Joe-Liu/Mitchell/etc (recursive bisection)    0        2        0
%%%   Regular+bisection (regular + recursive bisection)    1        2        0
%%%   Bank/Bey/etc (regular + pure green closure)          1        1        0
%%%   Burak's restricted r/g (restricted regular + green)  1        1        1
%%%   Mike's bordered r/g (bordered regular + green)       2        1        2
%%%

refkey   = 2;    %%% refinement type
                 %%%   0=bisection (bisect marked guys by longest edge)
                 %%%   1=quadrasection-pure (quadrasect marked guys)
                 %%%   2=quadrasection-patch (quadrasect marked + 1-rings)

closekey = 1;    %%% closure type
                 %%%   0=none (i.e., red refinement)
                 %%%   1=green (pure green closure via quad-/tri-/bi-section)
                 %%%   2=recursive bisection (by longest edge)

markkey  = 2;    %%% marking type (has meaning really only for quadrasection)
                 %%%   0=no restriction on marking for refinement
                 %%%   1=mark ONLY elements where were created as the
                 %%%     INTERIOR child in a quadrasection in the 
                 %%%     previous level. 
                 %%%   2=mark ONLY elements which were created as 
                 %%%     ANY child in a quadrasection in the 
                 %%%     next previous level.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%% clear the graphics window
clf;

%%% construct operators for the nested sequence of spaces
for level = 1 : levels
    fprintf('MAIN: -------\n');
    fprintf('MAIN: LEVEL %g\n',level);
    fprintf('MAIN: -------\n');

    if (level == 1)
        %%% create the initial coarse mesh
        fprintf('MAIN: defining the mesh..');
        t0 = clock;
        [VERT,SIMP] = read(0);
        the_time = etime(clock,t0);
        [N,eight]     = size(VERT);
        [L,seventeen] = size(SIMP);
        fprintf('..done.  [N=%g,L=%g]  [time=%g]\n',N,L,the_time);
    else
        %%% build the simplex rings (BOTH mark and refin need them)
        [VERT,SIMP] = bldsring(VERT,SIMP);

        %%% error estimate and the mark mesh (some uniform refinements first)
        fprintf('MAIN: marking  the mesh..');
        t0 = clock;
        [SIMP,QUE]    = mark(VERT,SIMP,U,Ug,markkey,level-1,estkey,esttol);
        the_time = etime(clock,t0);
        [N,eight]     = size(VERT);
        [L,seventeen] = size(SIMP);
        fprintf('..done.  [N=%g,L=%g]  [time=%g]\n',N,L,the_time);

        %%% adaptively refine the mesh based on the marking
        fprintf('MAIN: refining the mesh..');
        t0 = clock;
        [VERT,SIMP,P,ONER] = refin(VERT,SIMP,QUE,refkey,closekey);
        eval(['P_' num2str(level-1) num2str(level) ' = P;']);
        the_time = etime(clock,t0);
        [N,eight]     = size(VERT);
        [L,seventeen] = size(SIMP);
        fprintf('..done.  [N=%g,L=%g]  [time=%g]\n',N,L,the_time);

        %%% kill the simplex rings (ONLY mark and refin need them)
        [VERT,SIMP] = kilring(VERT,SIMP);
    end;

    %%% check the mesh for "correctness"
    if (chkkey > 0)
        %%% simplex rings get created and then destroyed by chkmesh
        chkmesh(VERT,SIMP);
    end

    %%% plot the mesh
    if (gv > 0)
        writeoff(socktype,2,VERT,SIMP);
    end;
    fprintf('MAIN: plotting the mesh..');
    subplot(2,2,1);
    draw(VERT,SIMP);       
    title('Finite element mesh');
    %%% draw1(VERT,SIMP);
    %%% draw2(VERT,SIMP);
    if (igenPS > 0)
        print -depsc mesh.eps
    end
    fprintf('..done.  [N=%g,L=%g]\n',N,L);

    %%% solve discrete system?
    if (solkey > 0)

        %%% solve discrete system
        fprintf('MAIN: algebraic solve starting.  [N=%g,L=%g]\n',N,L);
        t0 = clock;
        [U,Ug,A,F]=nsolve(VERT,SIMP);
        [Nn,one] = size(U);
        n = Nn / N;
        the_time = etime(clock,t0);
        fprintf('MAIN: algebraic solve finished.  [time=%g]\n',the_time);

        %%% discretization error test
        U_tt = u_t( VERT(1:N,1), VERT(1:N,2), VERT(1:N,6) );
        U_t  = reshape(U_tt,Nn,1);
        normUt = norm(U_t);
        if (normUt == 0.0)
            normUt = 1.0;
        end;
        error = norm(U_t - (U+Ug)) / normUt;
        fprintf('MAIN: discretization error is = %g\n',error); 

        %%% build matrix copy with small entries dropped (for display only)
        tolZero = 1.0e-5;
        AA=A .* ( (A > tolZero) | (A < -tolZero) );

        %%% graph the matrix
        fprintf('MAIN: graphing matrix..');
        subplot(2,2,3);
        NODES = [];
        for i=1:n
            NODES = [ NODES ; VERT(:,1:2) ];
        end;
        subplot(2,2,3);
        gplot(AA,NODES,'r'); axis('equal'); axis('off');
        title('Graph of stiffness matrix');
        if (igenPS > 0)
            print -depsc gplot.eps
        end
        fprintf('..done.  [N=%g,L=%g]\n',N,L);

        %%% show matrix structure 
        fprintf('MAIN: showing nonzero structure..');
        subplot(2,2,4);
        spy(AA,'r');
        title('Nonzero structure of stiffness matrix');
        if (igenPS > 0)
            print -depsc spy.eps
        end
        fprintf('..done.  [N=%g,L=%g]\n',N,L);

        %%% plot the solution
        if (gvs > 0)
            writeoffs(socktype,2,VERT,SIMP,(U+Ug));
        end;
        fprintf('MAIN: plotting FEM solution..');
        subplot(2,2,2);
        if (n==2)
            drawd(VERT,SIMP,(U+Ug));
        else
            drawf(VERT,SIMP,(U+Ug));
        end
        title('Finite element solution');
        if (igenPS > 0)
            print -depsc sol.eps
        end
        fprintf('..done.  [N=%g,L=%g]\n',N,L);

    else
        [u_size,dummy] = size(VERT);
        U  = zeros(u_size,1);
        Ug = zeros(u_size,1);
    end; %%% solve discrete system

    %%% pause before starting a new refinement level
    mypaus; 

end; %%% solve-estimate-refine loop

