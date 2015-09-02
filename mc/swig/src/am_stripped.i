
typedef struct AM {


    Vmem       *vmem;        

    Aprx       *aprx;       
    Bmat       *P;       


    int        algExist;    

    Bmat       *A;   
    Bmat       *M;   

    Bvec       *f;  
    Bvec       *u;     
    Bvec       *ud;  
    Bvec       *ui;   
    Bvec       *ut;   
    Bvec       *r; 
    Bvec       *w0;     

  %extend{
    AM(Aprx *taprx){return AM_ctor(VNULL, taprx);}

    ~AM(){AM_dtor(&$self);}

VEXTERNC void create();

VEXTERNC void destroy();

VEXTERNC int markRefine( int key, int color,
    int bkey, double elevel);

VEXTERNC int refine( int rkey, int bkey, int pkey);

VEXTERNC int unRefine( int rkey, int pkey);

VEXTERNC int deform();

VEXTERNC int read( int key, Vio *sock);

VEXTERNC double assem(
    int evalKey, int energyKey, int residKey, int tangKey, int massKey,
    int bumpKey,
    Bvec *u, Bvec *ud, Bvec *f, int ip[], double rp[]);

VEXTERNC double evalJ();

VEXTERNC void evalFunc(
    int number, int block, int numPts, double *pts,
    double *vals, int *marks);

VEXTERNC void bndIntegral();

VEXTERNC double evalError( int pcolor, int key);

VEXTERNC void applyDiriZero( Bvec *which);

VEXTERNC void iniGuess( Bvec *which);

VEXTERNC int part( int pkey, int pwht, int ppow);

VEXTERNC int partSet( int pcolor);

VEXTERNC int partSmooth();

VEXTERNC void printJ();

VEXTERNC void printA();

VEXTERNC void printAnoD();

VEXTERNC void printAsp( char *fname);

VEXTERNC void printAspNoD( char *fname);

VEXTERNC void printP();

VEXTERNC void printPsp( char *fname);

VEXTERNC void printV( int num);

VEXTERNC void printVsp( int num, char *fname);

VEXTERNC void writeGEOM( Vio *sock,
    int defKey, int colKey, int chartKey, double gluVal, int fkey,
    int number, char *format);

VEXTERNC void writeSOL( Vio *sock, int number, char *format);

VEXTERNC void memChk();

VEXTERNC void lSolve( int prob,
    int meth, int itmax, double etol, int prec, int gues, int pjac);

VEXTERNC void hlSolve( int prob,
    int meth, int itmax, double etol, int prec, int gues, int pjac);
#if 0
VEXTERNC void hPbcg(int lev, int key, int flag, int itmax, double etol, int meth,
    int uu, int ff, int rr, int dd, int ut);
#endif


VEXTERNC void nSolve(int meth, int itmax, double etol,
    int lmeth, int litmax, double letol, int lprec, int gues, int pjac);

VEXTERNC void newton(int itmax, double etol,
    int lmeth, int litmax, double letol, int lprec, int pjac, double loadParm);

#if 0
VPUBLIC void homotopy(int itmax, double etol,
    int lmeth, int litmax, double letol, int lprec, int pjac);
#endif

  }

} AM;

