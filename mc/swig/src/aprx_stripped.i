typedef struct Aprx {

    int      numV;
    int      numE;
    int      numF;
    int      numS;

    Bnode    *B;         

    int      numBV[MAXV]; 
    int      *ibv[MAXV];  
    double   *bv[MAXV];    

    Bvec     *wev;        
    double   gerror;        

    int      numB;       

    int order;

  %extend{

    Aprx(Gem *tgm, PDE *tpde){return  Aprx_ctor(VNULL, tgm, tpde);}

    ~Aprx(){Aprx_dtor(&self);}

    VEXTERNC int read(int key, Vio *sock);

    VEXTERNC void reset();

    VEXTERNC void initNodes();

    VEXTERNC void buildNodes();

    VEXTERNC void evalTrace(Bvec *Wud, Bvec *Wui, Bvec *Wut);

    VEXTERNC int refine(int rkey, int bkey, int pkey);

    VEXTERNC int unRefine(int rkey, int pkey);

    VEXTERNC int deform(Bvec *deform);

    VEXTERNC void buildProlong(int numRc, int numR, int pkey);

    VEXTERNC void buildProlongBmat(Mat *p);

    VEXTERNC int nodeCount(Re *re);

    VEXTERNC void interact(Re *re, Re *reT,
			   int *numR, int *numO, int *numOYR, int **IJA, int **IJAYR);

    VEXTERNC void interactBlock( Re *re[MAXV], Re *reT[MAXV],
				 MATsym sym[MAXV][MAXV], MATmirror mirror[MAXV][MAXV], MATformat frmt[MAXV][MAXV],
				 int numR[MAXV], int numO[MAXV][MAXV], int *IJA[MAXV][MAXV]);

    VEXTERNC int nodeIndex (Re *re, int i, int dim, int q);

    VEXTERNC int nodeIndexTT (Re *re, TT *t, int idf);

    VEXTERNC void buildBRC(Bmat *A, Bmat *M);

    VEXTERNC void initSpace(int i, int r,
			    double phi[], double phix[][3], double V[], double dV[][3]);


    VEXTERNC void initEmat(int bumpKey, TT *t, Emat *em);

    VEXTERNC void quadEmat(int evalKey, int energyKey, int residKey, int tangKey, int massKey,
			   int bumpKey,
			   int face, TT *t, Emat *em,
			   Bvec *Wu, Bvec *Wud);

    VEXTERNC void fanEmat(int evalKey, int energyKey, int residKey, int tangKey, int massKey,
			  int bumpKey,
			  Emat *em,
			  Bmat *A, Bmat *M, Bvec *F);

    VEXTERNC void assemEmat(SS *sm,
			    int evalKey, int energyKey, int residKey, int tangKey, int massKey,
			    int bumpKey,
			    Emat *em,
			    Bvec *Wu, Bvec *Wud);

    VEXTERNC double assem(int evalKey, int energyKey, int residKey, int tangKey, int massKey,
			  int bumpKey,
			  int ip[], double rp[],
			  Bmat *A, Bmat *M, Bvec *F, Bvec *Wu, Bvec *Wud);

    VEXTERNC int markRefine(int key, int color,
			    int bkey, double elevel, Bvec *u, Bvec *ud, Bvec *f, Bvec *r);

    VEXTERNC int estRefine(int key, int color,
			   int bkey, double elevel, Bvec *u, Bvec *ud, Bvec *f, Bvec *r);

    VEXTERNC int markRefineFixed (int num2ref, int color); 

    VEXTERNC void evalFunc(Bvec *u, int block, int numPts, double *pts,
			   double *vals, int *marks);

    VEXTERNC void fe2fd(Bvec *u, int block,
			int nx, int ny, int nz,
			double x0, double y0, double z0, double dx, double dy, double dz,
			int derivs, int outTypeKey);

    VEXTERNC void bndIntegral(Bvec *u, Bvec *ud, Bvec *ut);

    VEXTERNC void admMass(Bvec *u, Bvec *ud, Bvec *ut, int block);

    VEXTERNC double evalError(int pcolor, int key,
			      Bvec *u, Bvec *ud, Bvec *ut);

    VEXTERNC double evalH1(SS *sm, Bvec *u, Bvec *ud, Bvec *ut);

    VEXTERNC void writeGEOM(Vio *sock,
			    int defKey, int colKey, int chartKey, double gluVal, int fkey,
			    Bvec *u, char *format);

    VEXTERNC void writeSOL(Vio *sock, Bvec *u, char *format);

    VEXTERNC int partSet(int pcolor);

    VEXTERNC int partSmooth();

    VEXTERNC int partInert(int pcolor,
			   int numC, double *evec, simHelper *simH);

    VEXTERNC int partSpect(int pcolor,
			   int numC, double *evec, simHelper *simH, int *ford, int *rord,
			   int general);

    VEXTERNC int part(int pkey, int pwht, int ppow);

    VEXTERNC int partOne(int pkey, int pwht, int pcolor, int poff);


  }
} Aprx;

