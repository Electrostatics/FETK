
    fprintf('MAIN: defining the mesh..\n');
    [VERT,SIMP] = read(0);
    [N,eight]     = size(VERT);
    [L,seventeen] = size(SIMP);

    %%% plot the mesh
    fprintf('MAIN: plotting the mesh..\n');
    subplot(2,2,1);
    draw(VERT,SIMP);       
    title('Finite element mesh');
    %%% draw1(VERT,SIMP);
    %%% draw2(VERT,SIMP);

    %%% get mass matrix
    fprintf('MAIN: getting mass matrix. [N=%g,L=%g]\n',N,L);
    assKey = 4;
    parm = zeros(10,1);
    U  = zeros(N,1);
    Ug = zeros(N,1);
    [M,F]=assem(assKey, parm, U, Ug, VERT, SIMP);

    %%% graph the matrix
    fprintf('MAIN: graphing matrix..\n');
    subplot(2,2,3);
    NODES = [];
    for i=1:N
        NODES = [ NODES ; VERT(:,1:2) ];
    end;
    subplot(2,2,3);
    gplot(M,NODES,'r'); axis('equal'); axis('off');
    title('Graph of mass matrix');

    %%% show matrix structure 
    fprintf('MAIN: showing nonzero structure..\n');
    subplot(2,2,4);
    spy(M,'r');
    title('Nonzero structure of mass matrix');

    %%% eigenstructure 
    eigs = eig(M);
    xmin = min(eigs);
    xmax = max(eigs);
    fprintf('MAIN: spectrum = [%g,%g]\n',xmin,xmax);
    
