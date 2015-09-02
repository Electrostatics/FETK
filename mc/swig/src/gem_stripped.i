#define VMAXSQ 2

typedef struct Gem{

    int     dim;     
    int     dimII;  
    int     dimVV; 
    int     dimEE; 

    int     numVV0; 
    int     numVV;  
    int     numEE; 
    int     numFF; 
    int     numSS; 
    int     numBV;  
    int     numBF;  

    Vmem     *vmem;   
    int      iMadeVmem;    

    Vset     *vertices;
    Vset     *edges;   
    Vset     *simplices; 

    Vset     *sQueM[VMAXSQ];

    int      iMadePDE; 
    PDE      *pde;   

    int xUpFlag;
    void (*xUp)(SS **sms, int numS);

  %extend{

    Gem(PDE *tpde){return Gem_ctor(VNULL, tpde);};

    ~Gem(){Gem_dtor(&$self);}

    VEXTERNC void reset(int dim, int dimII);

    VEXTERNC VV* createAndInitVV();

    VEXTERNC EE* createAndInitEE();

    VEXTERNC SS* createAndInitSS();

    VEXTERNC SS* SQ(int currentQ, int i);

    VEXTERNC void appendSQ(int currentQ, SS *qsm);

    VEXTERNC void createSimplexRings();

    VEXTERNC void destroySimplexRings();

    VEXTERNC EE* findOrCreateEdge(VV *v0, VV *v1, int *iDid);

    VEXTERNC void createEdges();

    VEXTERNC void destroyEdges();

    VEXTERNC void countChk();

    VEXTERNC void countFaces();

    VEXTERNC void clearEdges();

    VEXTERNC void countEdges();

    VEXTERNC void formFix(int key);

    VEXTERNC void simplexInfo(SS *sm, TT *t);

    VEXTERNC void buildVolumeTrans(SS *sm, TT *t);

    VEXTERNC void buildSurfaceTrans(int iface, TT *t);

    VEXTERNC double edgeLength(VV *v0, VV *v1);

    VEXTERNC int newestVertex(SS *sm, int face, double *len);

    VEXTERNC int longestEdge(SS *sm, int face, double *len);

    VEXTERNC int shortestEdge(SS *sm, int face, double *len);

    VEXTERNC double shapeMeasure(SS *sm, double *f, double *g);

    VEXTERNC void shapeMeasureGrad(SS *sm, int vmap[], double dm[]);

    VEXTERNC double edgeRatio(SS *sm);

    VEXTERNC double simplexVolume(SS *sm);

    VEXTERNC void shapeChk();

    VEXTERNC void markEdges();

    VEXTERNC void reorderSV();

    VEXTERNC void smoothMeshLaplace();

    VEXTERNC void smoothMesh();

    VEXTERNC void smoothMeshBnd();

    VEXTERNC void smoothMeshOpt();

    VEXTERNC void buildCharts();

    VEXTERNC void clearCharts();

    VEXTERNC void memChk();

    VEXTERNC void memChkVV(int *num,
			   int *size, int *vecUse, int *vecMal, int *vecOhd);

    VEXTERNC void memChkEE(int *tnum,
			   int *size, int *vecUse, int *vecMal, int *vecOhd);

    VEXTERNC void memChkSS(int *tnum,
			   int *size, int *vecUse, int *vecMal, int *vecOhd);

    VEXTERNC void memChkSQ(int currentQ,
			   int *tnum, int *tsize, int *tVecUse, int *tVecMal, int *tVecOhd);

    VEXTERNC void memChkMore();

    VEXTERNC void speedChk();

    VEXTERNC void formChk(int key);

    VEXTERNC void contentChk();

    VEXTERNC void ramClear(int key);

    VEXTERNC void makeBnd(int btype);

    VEXTERNC void makeBndExt(int key);

    VEXTERNC void delaunay();

    VEXTERNC void flip(VV *vx);

    VEXTERNC SS* findSimplex(VV *vx);

    VEXTERNC void predinit();

    VEXTERNC int orient(SS *sm);

    VEXTERNC int inSphere(SS *sm, int sm_facet, VV *vx, VV *vxnb);

    VEXTERNC int pointInSimplex(SS *sm, double x[]);

    VEXTERNC int pointInSimplexVal(SS *sm, double x[],
				   double phi[], double phix[][3]);

    VEXTERNC int deform(int dimX, double *defX[MAXV]);

    VEXTERNC int markRefine(int key, int color);

    VEXTERNC int refine(int rkey, int bkey, int pkey);

    VEXTERNC void refineEdge(int currentQ,
			     SS *sm, VV *v[4], VV **vAB, int A, int B);

    VEXTERNC void octsect(SS *sm, int currentQ);

    VEXTERNC void bisectLE(SS *sm, int currentQ);

    VEXTERNC void bisectNV(SS *sm, int currentQ);

    VEXTERNC void bisectNP(SS *sm, int currentQ);

    VEXTERNC int unRefine(int rkey, int pkey);

    VEXTERNC void delSimplex(SS *sm, int currentQ);

    VEXTERNC void unHangVertices();

    VEXTERNC int read(int key, Vio *sock);

    VEXTERNC void write(int key, Vio *sock, int fkey);

    VEXTERNC void writeFace3d(Vio *sock);

    VEXTERNC int readEdge(Vio *sock);

    VEXTERNC void writeEdge(Vio *sock);

    VEXTERNC void buildSfromE();

    VEXTERNC void writeBrep(Vio *sock);

    VEXTERNC void writeBrep2(Vio *sock);

    VEXTERNC void writeBrep3(Vio *sock);

    VEXTERNC void writeBrep2to3(Vio *sock);

    VEXTERNC void writeGEOM(Vio *sock,
			    int defKey, int colKey, int chartKey, double gluVal, int fkey,
			    double *defX[MAXV], char *format);

    VEXTERNC void writeSOL(Vio *sock,
			   int fldKey,
			   double *defX[MAXV], char *format);

    VEXTERNC void writeVolHeaderOFF(Vio *sock);

    VEXTERNC void writeBndHeaderOFF(Vio *sock);

    VEXTERNC void writeTrailerOFF(Vio *sock);

    VEXTERNC void writeGV(Vio *sock,
			  int defKey, int colKey, int chartKey, double gluVal, int fkey,
			  double *defX[MAXV]);

    VEXTERNC void writeFace2dGV(Vio *sock,
				int defKey, int colKey, int chartKey, double gluVal,
				double *defX[MAXV]);

    VEXTERNC void writeFace3dGV(Vio *sock,
				int defKey, int colKey, int chartKey, double gluVal,
				double *defX[MAXV]);

    VEXTERNC void writeHeaderMATH(Vio *sock);

    VEXTERNC void writeTrailerMATH(Vio *sock);

    VEXTERNC void writeMATH(Vio *sock,
			    int defKey, int colKey, int chartKey, double gluVal, int fkey,
			    double *defX[MAXV]);

    VEXTERNC void writeGMV(Vio *sock,
			   int fldKey, double *defX[MAXV]);

    VEXTERNC void writeUCD(Vio *sock,
			   int fldKey, double *defX[MAXV]);


    VEXTERNC void writeDX(Vio *sock,
			  int fldKey, double *defX[MAXV]);

    VEXTERNC void writeTEC(Vio *sock,
			   int fldKey, double *defX[MAXV]);



    VEXTERNC void makeCube();

    VEXTERNC void makeOctahedron();

    VEXTERNC void makeIcosahedron();
  }
} Gem;
