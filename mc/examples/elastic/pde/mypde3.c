#include "mypde.h"

VEMBED(rcsid="$Id: mypde3.c,v 1.1 2008/04/23 22:56:41 fetk Exp $")

const int P_FRC=2; /* 0=internal force, 1=traction force, 2=int+tract         */
const int P_MAT=0; /* 0=linear material,         1=nonlinear material       */
const int P_GEO=1; /* 0=linear deformation,      1=nonlinear deformation    */

const int P_DIR=1; /* 0=zero Dirichlet, 1=nonzero Dirichlet     */
const int P_NEU=0; /* 0=standard Neumann, 1=Robin term also     */

VPRIVATE double flux[MAXV][3], ndotflux[MAXV], paramM, paramA, tcurv;
VPRIVATE double U[MAXV], dU[MAXV][3], ddU[MAXV][3], xq[3], curv[3];
VPRIVATE double UJUMP, FJUMP;
VPRIVATE double epsp, epsw, deps, beta, kappa;
VPRIVATE int fType, fID, vfType[MAXV], sType, ekey;
VPRIVATE TT *myt;
VPRIVATE Vmodel *model;

VPRIVATE double nvec[3], vx[4][3];
VPRIVATE double scalarA, scalarB, scalarDB, scalarC, scalarGN, scalarDN[3], scalarDA[3];
VPRIVATE double I[3][3], A[3][3][3][3], ET[3][3], ST[3][3], dST[3][3][3][3], trET;
VPRIVATE double FORCE[3], C[3], GN[3], homotopyPrm, YoungsM, PoissonR, mu, lambda;

VPRIVATE void   my_scalarD(int d, int m, int sType, double *x, double *f);
VPRIVATE double my_scalarA(int d, int m,  int sType,  double *x);
VPRIVATE void   my_scalarDA(int d, int m,  int sType, double *x, double *DA);
VPRIVATE double my_scalarB(int d, int m,  int sType, double A, double *DA, double *DN, double *x, double *u);
VPRIVATE double my_scalarDB(int d, int m,  int sType, double *x, double *u);
VPRIVATE double my_scalarC(int d, int m,  int sType, double *x);
VPRIVATE double my_scalarGN(int d, int m,  int sType, double A, double C, double *x);
VPRIVATE void   my_US(int d, int m,  int vDomain, double *x, double *f);

VPRIVATE double my_MU();
VPRIVATE double my_LAMBDA();
VPRIVATE void my_BodyForce(int d, int m, double *x, double *f, int sType);
VPRIVATE void my_SurfForce(int d, int m, double *x, double *nvec, double *f, int fType);
VPRIVATE void formST(int d, double A[][3][3][3], double ET[][3], double ST[][3], double dST[][3][3][3]);
VPRIVATE void formET(int d, double dU[][3], double ET[][3]);
VPRIVATE void my_C(int d, int m, double *x, double *f);

VPRIVATE void initAssemble(PDE *thee, int ip[], double rp[]) {
    int i, j, k, p, q;
 
    if(PDE_ID==1) {   /* regularized Poisson-Boltzmann equation */
       model = usr_getModel(ptPBEQ);
       epsp = model->epsp;
       epsw = model->epsw;
       beta = model->beta;
       kappa = model->kappa;
       deps  = epsw - epsp;
    } else if(PDE_ID == 2) {          /* Laplace equation */ 
       model = usr_getModel(ptPBEQ); 
       epsp = model->epsp;
       epsw = model->epsw;
       beta = model->beta;
       kappa = model->kappa;
       deps  = epsw - epsp;
    } else if(PDE_ID == 3) {

       YoungsM  = model->YoungsM;
       PoissonR = model->PoissonR;

       /* homotopy parameter */
        homotopyPrm = rp[0];

       /* form the identity */
        for (i=0; i<thee->dim; i++)
           for (j=0; j<thee->dim; j++)
              I[i][j] = 0.;
        for (i=0; i<thee->dim; i++)
           I[i][i] = 1.;

       /* get the lame constants */
        mu     = my_MU();
        lambda = my_LAMBDA();

       /* form the material coefficient matrix */
        for (i=0; i<thee->dim; i++)
           for (j=0; j<thee->dim; j++)
              for (p=0; p<thee->dim; p++)
	          for (q=0; q<thee->dim; q++)
	              A[i][j][p][q] = lambda * I[i][j] * I[p][q]
                                      + mu * ( I[i][p] * I[j][q] + I[i][q] * I[j][p] );
    } else {
       Vnm_print(2," Invalid PDE_ID \n");
       VASSERT(0);
    } 
}

VPRIVATE void initElement(PDE *thee, int elementType, int chart, double tvx[][3], void *data){
    int i, j;
    Vmodel *model = usr_getModel(ptPBEQ);
    Valist *alist = model->alist;
    int     natoms = alist->number;
    Vatom  *atomi;
  
    myt = (TT *)data;

    for (i=0; i<thee->dim+1; i++)
      for (j=0; j<thee->dim; j++)
          vx[i][j] = tvx[i][j];
    sType = elementType;
} 


VPRIVATE void initFace(PDE *thee, int face, int chart, double tnvec[]){

    int i;

    /* unit normal vector of this face */
    for (i=0; i<thee->dim; i++) nvec[i] = tnvec[i];

    fID   = face;
    fType = myt->ftype[face]; 
    for(i=0; i<thee->vec; i++) vfType[i] = thee->bmap[i][fType];
}

VPRIVATE void initPoint(PDE *thee, int pointType, int chart, int sType, double txq[],
            double tU[], double tdU[][3], double phi[], double phix[][3]) {

    int i, j, k;   // usually i: thee->vec; j: thee->dim; k: basis function
    int PBEQ_vid[4];
    int enum_FF_Eles, enum_FF_PBEQ;
    double rad, rad3, fjump_vec[3], grad_pots[3], fdum, fjump_vecT[3];
   
    if(PDE_ID==1) {    // PBEQ

       for(j=0; j<thee->dim; j++) xq[j] = txq[j];
       for(i=0; i<thee->vec; i++) {
          U[i] = tU[i];
          for(j=0; j<thee->dim; j++) {
              dU[i][j] = tdU[i][j];
          }
       }
     
       rad  = sqrt(pow(txq[0],2) + pow(txq[1],2) + pow(txq[2],2));
       rad3 = pow(rad,3);
       
       /* interior form case */
       if (pointType == 0) {
           scalarA = my_scalarA(thee->dim, thee->vec, sType, xq);
           my_scalarDA(thee->dim, thee->vec, sType, xq, scalarDA);
           my_scalarD(thee->dim, thee->vec, sType, xq, scalarDN);
           scalarB  = my_scalarB(thee->dim, thee->vec, sType, scalarA, scalarDA, scalarDN, xq, U);
           scalarDB = my_scalarDB(thee->dim, thee->vec, sType, xq, U);

           if(KeyLinear == 1 && sType==1) scalarB  += epsw*pow(kappa,2)*(U[0]);
           if(KeyLinear == 1 && sType==1) scalarDB += epsw*pow(kappa,2);           

           if(KeyLinear == 0 && sType==1) scalarB  += epsw*pow(kappa,2)*sinh(U[0]);
           if(KeyLinear == 0 && sType==1) scalarDB += epsw*pow(kappa,2)*cosh(U[0]);    

       /* boundary form case */
       } else if(pointType < 5) { /* (pointType == 1) */

           scalarA  = my_scalarA(thee->dim, thee->vec, sType, xq);
           scalarC  = my_scalarC(thee->dim, thee->vec, sType, xq);
           scalarGN = my_scalarGN(thee->dim, thee->vec, sType, scalarA, scalarC, xq);
       /* interface form case */
       } else { /* (pointType == 1) */
          
          FJUMP = 0.0;
          if(sType > 1) {
 
             for(i=0; i<thee->dim; i++) fjump_vec[i] = 0.0;

             for(i=0; i<thee->dim; i++) 
                for(j=0; j<myt->dimV; j++) 
                   fjump_vec[i] += phix[j][i]*model->poth[myt->vid[j]];
 
             Grad_SingPot(grad_pots,xq);
             for(i=0; i<thee->dim; i++) fjump_vec[i] += grad_pots[i]; 

             for (j=0; j<myt->dimV; j++) FJUMP -= fjump_vec[j]*nvec[j];
             FJUMP =-FJUMP*epsp;
          }
       }
    } else if( PDE_ID == 2) {    // Laplace
       for(i=0; i<thee->vec; i++) {
          U[i] = tU[i];
          for(j=0; j<thee->dim; j++) {
             if(i==0) { 
                xq[j]   = txq[j]; 
             }
             dU[i][j]  = tdU[i][j];
             ddU[i][j] = 0.0;
          }
       }

       for(i=0; i<thee->vec; i++) {
          U[i]        = tU[i]; 
          ndotflux[i] = 0.0;
       }

       /* interior form case */
       if (pointType == 0) {
           scalarA  = 1.0;
           my_scalarDA(thee->dim, thee->vec, sType, xq, scalarDA);
           my_scalarD(thee->dim, thee->vec, sType, xq, scalarDN);
           scalarB  = 0.0;
           scalarDB = 0.0; 

       /* boundary form case */
       } else if(pointType < 5) { /* (pointType == 1) */
           scalarA  = 1.0;
           scalarC  = 0.0;
           scalarGN = 0.0;
       }
    }  else if(PDE_ID ==3 ) {
       /* the point, and the solution value and gradient at the point */
       for (i=0; i<thee->vec; i++) {
           U[i] = tU[i];
           for (j=0; j<thee->dim; j++) {
              if (i==0) xq[j] = txq[j];
	      dU[i][j] = tdU[i][j];
	   }
       }

       /* interior form case */
       if (pointType == 0) {
          //my_BodyForce(thee->dim, thee->vec, xq, FORCE, sType);
          // no body force if membrane is uncharged

          formET(thee->dim, dU, ET);
          formST(thee->dim, A, ET, ST, dST);

       /* boundary form case */
       } else { /* (pointType == 1) */
	   my_C(thee->dim, thee->vec, xq, C);

           /* surface traction interpolated from the forces at nodes */
           /* to be improved by directly using the mapping between membrane surface mesh and the
              PBEQ interface mesh */
        
           for(i=0; i<thee->dim; i++)  GN[i] = 0.0;

	   //my_SurfForce(thee->dim, thee->vec, xq, nvec, GN, fType);

           if(fType == 4) {
              for(j=0; j<myt->dimV; j++) PBEQ_vid[j] = model->vxElesChartInv[myt->vid[j]];
             
              for(j=0; j<myt->dimV; j++) {
                 for(i=0; i<thee->dim; i++) { 
                     GN[i] += model->SurfForcePlot[PBEQ_vid[j]][i]/3.0;
                 }
              }

              //Vnm_print(2," x  = %12.4e %12.4e %12.4e \n",txq[0], txq[1], txq[2]);
              //Vnm_print(2," GN = %12.4e %12.4e %12.4e \n",GN[0], GN[1], GN[2]);
              //getchar();
           }
       }
    } else {
       Vnm_print(2," invalid PDE_ID \n");
       VASSERT(0);
    }
}

VPRIVATE void Fu(PDE *thee, int key, double F[]) { 
    int i, j;

    if(PDE_ID == 1 || PDE_ID == 2) { 
       /* element residual case */
       if (key == 0) {
          for (j=0; j<thee->vec; j++) F[j] = 0.;

        /* neumann face residual case */
       } else if (key == 1) {
          for (j=0; j<thee->vec; j++)  F[j] = scalarC * U[j] - scalarGN;
          for (i=0; i<thee->dim; i++)
          for (j=0; j<thee->vec; j++)  F[j] += dU[j][i] * nvec[i];

         /* interior face residual case */
       } else if (key == 5) {
          for (j=0; j<thee->vec; j++) F[j] = 0.;
       }
    } else if(PDE_ID ==3) {   // elasticity equation
      /* element residual case */
       if (key == 0) {
          for (i=0; i<thee->vec; i++) F[i] = 0.;

      /* neumann face residual case */
       } else if (key == 1) {
          for (i=0; i<thee->vec; i++) {
             F[i] = C[i] * U[i] - GN[i];
             for (j=0; j<thee->dim; j++)
                 F[i] += dU[i][j] * nvec[j];
          }

      /* interior face residual case */
       } else { /* (key == 2) */
          for (i=0; i<thee->vec; i++) {
              F[i] = 0.;
              for (j=0; j<thee->dim; j++)
                  F[i] += dU[i][j] * nvec[j];
          }
       }
    } else {
       Vnm_print(2," Invalid PDE_ID \n");
       VASSERT(0);
    } 
}

VPRIVATE double Ju(PDE *thee, int key) { 
    int i, j;
    double value=0;

    if(PDE_ID == 1 || PDE_ID == 2) {
       switch(key) {
       case 0:                 /* surface flux */
           if (fType == IB_RD) for (j=0; j<thee->vec; j++) value += ndotflux[j];
           break;
       case 1:                 /* surface area */
           if (fType == IB_RD) value = 1;
           break;
       case 2:                 /* total quantity */
           if (fType == 0) for (j=0; j<thee->vec; j++) value += U[j];
           break;
       case 3:                 /* volume */
           if (fType == 0) value = 1.0;
           break;
       case 4:                 /* Flux evaluated throught volume integral */
           for (i=0; i<thee->dim; i++)
              for (j=0; j<thee->vec; j++) value -= dU[j][i]*flux[j][i];
           break;
       default:
           value = 0.0;
           break;
       }
    } else if(PDE_ID == 3) {
       /* interior form case */
        if (key == 0) {
           value = 0.;
       /* boundary form case */
        } else if (key == 1) {
          value = 0.;
        } else { VASSERT(0); }
    } else {
       Vnm_print(2," Invalid PDE_ID \n");
       VASSERT(0);
    }
    return value;
}

VPRIVATE double Fu_v(PDE *thee, int key, double V[], double dV[][3]) {

    double value = 0.;
    int i, j, k;

    if(PDE_ID == 1) { // PBEQ 
       /* interior form case */
       if (key == 0) {
           value = scalarB * V[0];
           for (i=0; i<thee->dim; i++)
               value += ( scalarA * dU[0][i] * dV[0][i] + scalarDN[i] * dU[0][i] * V[0] );
       /* boundary form case */
       } else if (key == 1) {
           value = (scalarC * U[0] - scalarGN) * V[0];

       /* interface form case */
       } else if (key == 5) {
           value = FJUMP*V[0]; 

       /* DUAL: interior form case */
       } else if (key == 2) {
           value = 0.0;

       /* DUAL: boundary form case */
       } else if (key == 3) {
           value = 0.0;

       } else { VASSERT(0); }
    } else if(PDE_ID==2) {    // Laplace 
	if (key==0) {
           for (j=0; j<thee->vec; j++) {
              value += scalarB * V[j];
              for (i=0; i<thee->dim; i++)
                  value += scalarA * dU[j][i] * dV[j][i];
           }
 	} else if (key == 1) {
           for(j=0; j<thee->vec; j++)
              value += (scalarC * U[j] - scalarGN) * V[j];
	} else { }
    } else if(PDE_ID == 3) {
      /* interior form case */
       if (key == 0) {
          for (i=0; i<thee->vec; i++) {
             value -= (homotopyPrm * FORCE[i] * V[i]);
             for (j=0; j<thee->dim; j++) {
                value += ST[i][j] * dV[i][j];
            }
          }
      /* boundary form case */
       } else if (key == 1) {
          for (i=0; i<thee->vec; i++)
              value += ( (C[i] * U[i] - GN[i]) * V[i] );

      /* DUAL: interior form case */
       } else if (key == 2) {
          value = 0.0;

      /* DUAL: boundary form case */
       } else if (key == 3) {
          value = 0.0;

       } else if (key == 5) {
          value = 0.0;
       } else { 
          VASSERT(0); 
       }
    } else  {
       Vnm_print(2," Invalid PDE_ID \n");
       VASSERT(0);
    }
    return value;
}

VPRIVATE double DFu_wv(PDE *thee, int key, double W[], double dW[][3], double V[], double dV[][3]) {

    int i, j, k, p, q, r;
    double value = 0., value2[MAXV];
    double UW[3][3], ST1[3][3], ST2[3][3], trUW;
    double tmp1, tmp2, tmp3;
    
    if(PDE_ID==1) {   // PBEQ
       /* interior form case */
       if (key == 0) {
           value = scalarDB * W[0] * V[0];
           for (i=0; i<thee->dim; i++)
               value += ( scalarA * dW[0][i] * dV[0][i] + scalarDN[i] * dW[0][i] * V[0] );

       /* boundary form case */
       } else if (key == 1) {
           value = scalarC * W[0] * V[0];

       /* interface form case */
       } else if (key == 5) {
           value = 0.0;

       /* DUAL: interior form case */
       } else if (key == 2) {
           value = 0.0;

       /* DUAL: boundary form case */
       } else if (key == 3) {
           value = 0.0;

       } else { VASSERT(0); }
    } else if(PDE_ID == 2)  {       // Laplace
       /* interior form case */
       if (key == 0) {
           for(j=0; j<thee->vec; j++)  {
              value += scalarDB * W[j] * V[j];
              for (i=0; i<thee->dim; i++)
                  value += scalarA * dW[j][i] * dV[j][i];
           }

       /* boundary form case */
       } else if (key == 1) {
           for(j=0; j<thee->vec; j++) 
              value += scalarC * W[j] * V[j];

       /* interface form case */
       } else if (key == 5) {
           value = 0.0;

       /* DUAL: interior form case */
       } else if (key == 2) {
           value = 0.0;

       /* DUAL: boundary form case */
       } else if (key == 3) {
           value = 0.0;
       } else { VASSERT(0); }
    } else if (PDE_ID == 3) {
      /* interior form case */
       if (key == 0) {
           for (i=0; i<thee->dim; i++) {
              for (j=0; j<thee->dim; j++) {
                 UW[i][j]  = 0.0;
                 ST1[i][j] = 0.0;
                 ST2[i][j] = 0.0;
              }
           }

           for (i=0; i<thee->vec; i++) {
               for (j=0; j<thee->dim; j++) {
                  UW[i][j] = 0.5*(dW[j][i] + dW[i][j]);
                  for (q=0; q<thee->dim; q++) 
                     UW[i][j] += 0.5*(dU[q][i]*dW[q][j] + dW[q][i]*dU[q][j]);
               }
           }

           trUW = 0.0;
           for(i=0; i<thee->dim; i++) trUW += UW[i][i];

           for (i=0; i<thee->vec; i++) {
               for (j=0; j<thee->dim; j++) {
                  for (q=0; q<thee->dim; q++) {
                     ST1[i][j] += (I[i][q] + dU[i][q])*(lambda*trUW*I[q][j] + 2.0*mu*UW[q][j]);
                     ST2[i][j] += dW[i][q]*(lambda*trET*I[q][j] + 2.0*mu*ET[q][j]);
                  }
               }
           }

           for (i=0; i<thee->dim; i++) {
               for (j=0; j<thee->dim; j++) {
                    value += (ST1[i][j] + ST2[i][j])*dV[i][j];
               }
           }
        /* boundary form case */
         } else if (key == 1) {
             for (i=0; i<thee->vec; i++)
                 value += ( C[0] * W[i] * V[i] );

        /* DUAL: interior form case */
         } else if (key == 2) {
             value = 0.0;

        /* DUAL: boundary form case */
         } else if (key == 3) {
             value = 0.0;

         } else if (key == 5) {
             value = 0.0;
       } else { VASSERT(0); }
    } else {
       Vnm_print(2," Invalid PDE_ID \n");
       VASSERT(0);
    }
    return value;
}

VPRIVATE double p_wv(PDE *thee, int key, double W[], double V[]) {
    
    int i, j;
    double value = 0.;
    
    if(PDE_ID==1) {
	/* PRIMAL: interior form case */
	if (key == 0) {
	    for (j=0; j<thee->vec; j++) value = W[j] * V[j];
	/* PRIMAL: boundary form case */
	} else if (key == 1) {
	    value = 0.0;
	/* DUAL: interior form case */
	} else if (key == 2) {
	    value = 0.0;
	/* DUAL: boundary form case */
	} else if (key == 3) {
	    value = 0.0;
	} else { VASSERT(0); }
    } else if(PDE_ID == 2) {
       /* interior form case */
       if (key == 0) {
           for(j=0; j<thee->vec; j++)
              value = W[j] * V[j];

       /* boundary form case */
       } else if (key == 1) {
           value = 0.0;

       /* interface form case */
       } else if (key == 1) {
           value = 0.0;

       /* DUAL: interior form case */
       } else if (key == 5) {
           value = 0.0;

       /* DUAL: boundary form case */
       } else if (key == 3) {
           value = 0.0;

       } else { VASSERT(0); }

    } else if(PDE_ID == 3) {
       /* interior form case */
        if (key == 0) {
            for(j=0; j<thee->vec; j++)
               value = W[0] * V[0];

        /* boundary form case */
        } else if (key == 1) {
            value = 0.0;

        /* DUAL: interior form case */
        } else if (key == 2) {
            value = 0.0;

        /* DUAL: boundary form case */
        } else if (key == 3) {
            value = 0.0;

        } else { VASSERT(0); }
    } else {
       Vnm_print(2," Invalid PDE_ID \n");
       VASSERT(0);
    }
    return value;
}

VPRIVATE void u_D(PDE *thee, int type, int chart, double txq[], double F[]) { 

    Vmodel *model;
    double value, conc;
    double charge;
    Vmgrid *mgrid;
    
    double dist2, cut, v1[3],concini, Pot;

    if(PDE_ID == 1 || PDE_ID == 2) {
       model = usr_getModel(ptPBEQ);
       conc  = model->conc;
       epsp  = model->epsp;
       epsw  = model->epsw;
       beta  = model->beta;
       kappa = model->kappa;
    }

    my_US(thee->dim, thee->vec, chart, txq, F); 
}

VPRIVATE void u_T(PDE *thee, int type, int chart, double txq[], double F[])
{  
    Vmodel *model;
    double value, conc;
    double charge;
    Vmgrid *mgrid;

    double dist2, cut, v1[3],concini, Pot;

    if(PDE_ID == 1 || PDE_ID == 2) {
       model = usr_getModel(ptPBEQ);
       conc  = model->conc;
       epsp  = model->epsp;
       epsw  = model->epsw;
       beta  = model->beta;
       kappa = model->kappa;
    }
    my_US(thee->dim, thee->vec, chart, txq, F);
}

VPRIVATE void delta(PDE *thee, int type, int chart, double txq[], void *user, double F[])
{  
  F[0] = 0.0;
}

VPRIVATE void bisectEdge(int dim, int dimII, int edgeType, int chart[], 
        double vx[][3]) {
    int i;
    for (i=0; i<dimII; i++) vx[2][i] = .5 * (vx[0][i] + vx[1][i]);
}

VPRIVATE int markSimplex(int dim, int dimII, int simplexType, int faceType[4], 
  int vertexType[4], int chart[], double vx[][3], void *data) 
{ 
   int i = 0;
   double dist;
   myt = (TT *)data;
   return 1;
}

VPRIVATE void oneChart(int dim, int dimII, int objType, int chart[],
        double vx[][3], int dimV) {}

VPRIVATE void mapBoundary(int dim, int dimII, int vertexType, int chart, double vx[3]){}

VPUBLIC PDE* myPDE_ctor( ) {

    PDE *thee = VNULL;
    int i;

    /* Create some space for the pde object */
    thee = Vmem_malloc(VNULL, 1, sizeof(PDE) );
    /* PDE-specific parameters and function pointers */
    thee->initAssemble = initAssemble;  /* once-per-assembly initialization */
    thee->initElement  = initElement;   /* once-per-element initialization  */
    thee->initFace     = initFace;      /* once-per-face initialization     */
    thee->initPoint    = initPoint;     /* once-per-point initialization    */
    thee->Fu           = Fu;            /* nonlinear strong form            */
    thee->Ju           = Ju;            /* nonlinear energy functional      */
    thee->Fu_v         = Fu_v;          /* nonlinear weak form              */
    thee->DFu_wv       = DFu_wv;        /* bilinear linearization weak form */
    thee->p_wv         = p_wv;          /* bilinear mass density form       */
    thee->delta        = delta;         /* delta function source term       */
    thee->u_D          = u_D;           /* dirichlet func and initial guess */
    thee->u_T          = u_T;           /* analytical soln for testing      */
    thee->vec          = 1;             /* unknowns per spatial point;      */
    thee->sym[0][0]    = 0;             /* symmetries of bilinear form      */
    thee->est[0]       = 1.0;           /* error estimator weights          */
    for (i=0; i<VMAX_BDTYPE; i++)       /* boundary type remappings         */
        thee->bmap[0][i] = i;

    /* Manifold-specific function pointers */
    thee->bisectEdge  = bisectEdge;  /* edge bisection rule                 */
    thee->mapBoundary = mapBoundary; /* boundary recovery rule              */
    thee->markSimplex = markSimplex; /* simplex marking rule                */
    thee->oneChart    = oneChart;    /* coordinate transformations          */

    /* apbs stuff */
     thee->user = VNULL;

    /* return the new pde object */
    return thee;
}

VPUBLIC PDE* myPBEQ_ctor( ) {

    PDE *thee = VNULL;
    Vusr *usrSMOL;
    int i;

    /* Create some space for the pde object */
    thee = Vmem_malloc(VNULL, 1, sizeof(PDE) );
    /* PDE-specific parameters and function pointers */
    thee->initAssemble = initAssemble;  /* once-per-assembly initialization */
    thee->initElement  = initElement;   /* once-per-element initialization  */
    thee->initFace     = initFace;      /* once-per-face initialization     */
    thee->initPoint    = initPoint;     /* once-per-point initialization    */
    thee->Fu           = Fu;            /* nonlinear strong form            */
    thee->Ju           = Ju;            /* nonlinear energy functional      */
    thee->Fu_v         = Fu_v;          /* nonlinear weak form              */
    thee->DFu_wv       = DFu_wv;        /* bilinear linearization weak form */
    thee->p_wv         = p_wv;          /* bilinear mass density form       */
    thee->delta        = delta;         /* delta function source term       */
    thee->u_D          = u_D;           /* dirichlet func and initial guess */
    thee->u_T          = u_T;           /* analytical soln for testing      */
    thee->vec          = 1;             /* unknowns per spatial point;      */
    thee->sym[0][0]    = 0;             /* symmetries of bilinear form      */
    thee->est[0]       = 1.0;           /* error estimator weights          */
    for (i=0; i<VMAX_BDTYPE; i++)       /* boundary type remappings         */
        thee->bmap[0][i] = i;

    /* Manifold-specific function pointers */
    thee->bisectEdge  = bisectEdge;  /* edge bisection rule                 */
    thee->mapBoundary = mapBoundary; /* boundary recovery rule              */
    thee->markSimplex = markSimplex; /* simplex marking rule                */
    thee->oneChart    = oneChart;    /* coordinate transformations          */

    /* apbs stuff */
    thee->user = usr_ctorPBEQ();

    /* return the new pde object */
    return thee;
}


VPUBLIC void myPDE_dtor(PDE *thee) {

    VASSERT( (thee) != VNULL );
    if ((thee) != VNULL) {
        usr_dtor(thee->user);
        Vmem_free(VNULL, 1, sizeof(PDE), (void **)&thee);
        thee = VNULL;
    }
}

VPUBLIC PDE* myEles_ctor(void)
{
    int i;
    PDE *thee = VNULL;

    /* create some space for the pde object */
    thee = Vmem_malloc( VNULL, 1, sizeof(PDE) );

    /* PDE-specific parameters and function pointers */
    thee->initAssemble = initAssemble;  /* once-per-assembly initialization */
    thee->initElement  = initElement;   /* once-per-element initialization  */
    thee->initFace     = initFace;      /* once-per-face initialization     */
    thee->initPoint    = initPoint;     /* once-per-point initialization    */
    thee->Fu           = Fu;            /* nonlinear strong form            */
    thee->Ju           = Ju;            /* nonlinear energy functional      */
    thee->Fu_v         = Fu_v;          /* nonlinear weak form              */
    thee->DFu_wv       = DFu_wv;        /* bilinear linearization weak form */
    thee->p_wv         = p_wv;          /* bilinear mass density form       */
    thee->delta        = delta;         /* delta function source term       */
    thee->u_D          = u_D;           /* dirichlet func and initial guess */
    thee->u_T          = u_T;           /* analytical soln for testing      */
    thee->vec          = 3; /* FIX! */  /* unknowns per spatial point;      */
    thee->sym[0][0]    = 1;             /* symmetries of bilinear form      */
    thee->sym[1][1]    = 1;
    thee->sym[2][2]    = 1;
    thee->sym[0][1]    = 0;
    thee->sym[0][2]    = 0;
    thee->sym[1][2]    = 0;
    thee->sym[1][0]    = 2;
    thee->sym[2][0]    = 2;
    thee->sym[2][1]    = 2;
    thee->est[0]       = 1.0;           /* error estimator weights          */
    thee->est[1]       = 1.0;
    thee->est[2]       = 1.0;
    for (i=0; i<VMAX_BDTYPE; i++) {     /* boundary type remappings         */
        thee->bmap[0][i] = i;
        thee->bmap[1][i] = i;
        thee->bmap[2][i] = i;
    }

    /* Manifold-specific function pointers */
    thee->bisectEdge  = bisectEdge;  /* edge bisection rule                 */
    thee->mapBoundary = mapBoundary; /* boundary recovery rule              */
    thee->markSimplex = markSimplex; /* simplex marking rule                */
    thee->oneChart    = oneChart;    /* coordinate transformations          */

    /* Element-specific function pointers */
    thee->simplexBasisInit = simplexBasisInit; /* initialization of bases   */
    thee->simplexBasisForm = simplexBasisForm; /* form trial & test bases   */

    /* user defined construction functions */
    thee->user = VNULL;
  
    /* return the new pde object */
    return thee;
}

VPUBLIC double PDE_getTime(PDE *thee)
{
    if( thee->user != VNULL ) {
        return ((VlinesPDE *)(thee->user))->time;
    } else {
        return 0.0;
    }
}

VPUBLIC Vusr* usr_ctor(){
    Vusr *thee; 

    thee = Vmem_malloc(VNULL,1,sizeof(Vusr));
    thee->model = model_ctor();
    thee->lparam= lparam_ctor();

    return thee;
}

VPUBLIC Vusr* usr_ctorSMOL(){
    Vusr *thee; 

    thee = Vmem_malloc(VNULL,1,sizeof(Vusr));
    thee->model = model_ctor();
    thee->lparam= lparam_ctor();

    return thee;
}

VPUBLIC Vusr* usr_ctorPBEQ(){
    Vusr *thee; 

    thee = Vmem_malloc(VNULL,1,sizeof(Vusr));
    thee->model = model_ctor();
    thee->lparam= lparam_ctor();

    return thee;
}


VPUBLIC void usr_dtor(Vusr *thee){
    model_dtor(thee->model);
    lparam_dtor(thee->lparam);
    Vmem_free(VNULL, 1, sizeof(Vusr), (void **)(&(thee)));
    thee = VNULL;
} 

VPUBLIC Vmodel* model_ctor(){
    Vmodel *thee;
    thee = Vmem_malloc( VNULL, 1, sizeof(Vmodel) );
    return thee;
}

VPUBLIC void model_dtor(Vmodel *thee){
    Vmem_free(VNULL, 1, sizeof(Vmodel), (void **)(&(thee)));
}


VPUBLIC double UU(int d, int m, int vDomain, double *x) {
    double rad, phis=0.0, ax, ay, az, acharge;
    Vmodel *model = usr_getModel(ptPBEQ);
    Valist *alist = model->alist;
    int     natoms = alist->number, i;
    Vatom  *atomi;

/* exact solution/Dirichlet boundary condition for potential, x 332.0716 to get kcal/mol/e */

    for(i=0; i < natoms; i++) {
       atomi = Valist_getAtom(alist,i);       
       ax = atomi->position[0];
       ay = atomi->position[1];
       az = atomi->position[2];
       acharge = atomi->charge;

       rad = sqrt(pow(x[0]-ax,2) + pow(x[1]-ay,2) + pow(x[2]-az,2));
       if(rad < 1.e-6) rad = 1.e-6;

       if(PDE_ID==1) {  // PBEQ
	  phis += acharge*exp(-kappa*rad)/(epsw*rad)*332.0716*beta; 
       } else {         // Laplace
	  phis -= acharge/(epsp*rad)*332.0716*beta;   // -G as the boundary condition
       }
    }
    return phis;
}


VPUBLIC double SingPot(double *x) {
    double rad, pot, ax, ay, az, acharge;
    Vmodel *model = usr_getModel(ptPBEQ);
    Valist *alist = model->alist;
    int     natoms = alist->number, i;
    Vatom  *atomi;

    pot = 0.0;
    for(i=0; i < natoms; i++) {
       atomi = Valist_getAtom(alist,i);       
       ax = atomi->position[0];
       ay = atomi->position[1];
       az = atomi->position[2];
       acharge = atomi->charge;

       rad = sqrt(pow(x[0]-ax,2) + pow(x[1]-ay,2) + pow(x[2]-az,2));
       if(rad < 1.e-6) rad = 1.e-6;

       pot += acharge/(epsp*rad)*332.0716*beta;
    }
    return pot;
}

VPUBLIC double SingPot_atoms(int indx_atom) {
    double x[3], rad, pot, ax, ay, az, acharge;
    Vmodel *model = usr_getModel(ptPBEQ);
    Valist *alist = model->alist;
    int     natoms = alist->number, i, j;
    Vatom  *atomi;

    atomi = Valist_getAtom(alist,indx_atom);       
    for(j=0; j<3; j++) x[j] = atomi->position[j];

    pot = 0.0;
    for(i=0; i < natoms; i++) {
       if( i != indx_atom) {
	  atomi = Valist_getAtom(alist,i);       
	  ax = atomi->position[0];
	  ay = atomi->position[1];
	  az = atomi->position[2];
	  acharge = atomi->charge;

	  rad = sqrt(pow(x[0]-ax,2) + pow(x[1]-ay,2) + pow(x[2]-az,2));
	  if(rad < 1.e-6) rad = 1.e-6;

	  pot += acharge/(epsp*rad)*332.0716*beta;
       }
    }
    return pot;
}

VPUBLIC void Grad_SingPot(double *grad_pots,double *x) {
    double rad, rad3, pot, axyz[3], acharge;
    Vmodel *model = usr_getModel(ptPBEQ);
    Valist *alist = model->alist;
    int     natoms = alist->number, i, j;
    Vatom  *atomi;

    for(j=0; j<3; j++) grad_pots[j] = 0.0;

    for(i=0; i < natoms; i++) {
       atomi = Valist_getAtom(alist,i);       
       for(j=0; j<3; j++) axyz[j] = atomi->position[j];
       acharge = atomi->charge;

       rad  = sqrt(pow(x[0]-axyz[0],2) + pow(x[1]-axyz[1],2) + pow(x[2]-axyz[2],2));
       if(rad < 1.e-6) rad = 1.e-6;
       rad3 = pow(rad,3);

       for(j=0; j<3; j++) grad_pots[j] -= acharge*(x[j] - axyz[j])/(epsp*rad3)*332.0716*beta;
    }
}

VPUBLIC void Grad_SingPot_atoms(double *grad_pots, int indx_atom) {
    double rad, rad3, pot, axyz[3], x[3], acharge;
    Vmodel *model = usr_getModel(ptPBEQ);
    Valist *alist = model->alist;
    int     natoms = alist->number, i, j;
    Vatom  *atomi;

    atomi = Valist_getAtom(alist,indx_atom);       
    for(j=0; j<3; j++) x[j] = atomi->position[j];
    
    for(j=0; j<3; j++) grad_pots[j] = 0.0;

    for(i=0; i < natoms; i++) {
       if(i != indx_atom) {
          atomi = Valist_getAtom(alist,i);       
          for(j=0; j<3; j++) axyz[j] = atomi->position[j];
          acharge = atomi->charge;

          rad  = sqrt(pow(x[0]-axyz[0],2) + pow(x[1]-axyz[1],2) + pow(x[2]-axyz[2],2));
          rad3 = pow(rad,3);

          for(j=0; j<3; j++) grad_pots[j] -= acharge*(x[j] - axyz[j])/(epsp*rad3)*332.0716*beta;
       }
    }
}

VPRIVATE void my_scalarD(int d, int m,  int sType, double *x, double *f) {
    f[0] = 0.0;
    f[1] = 0.0;
    f[2] = 0.0;
}

VPRIVATE double my_scalarA(int d, int m,  int sType, double *x) { 
    if(sType !=1 )  return epsp;
    else            return epsw;
}

VPRIVATE void my_scalarDA(int d, int m,  int sType, double *x, double *DA) { 
    scalarDA[0] = 0.e0; 
    scalarDA[1] = 0.e0; 
    scalarDA[2] = 0.e0; 
}

VPRIVATE double my_scalarB(int d, int m,  int sType, double scalarA, 
                           double *scalarDA, double *scalarDN, double *x, double *u) {
    double SRC;

    SRC = 0.0; 
    return SRC;
}

VPRIVATE double my_scalarDB(int d, int m,  int sType, double *x, double *u) {
    return 0.0;
}

VPRIVATE double my_scalarC(int d, int m,  int sType, double *x) {
    if (P_NEU==0) return 0.0; /* neumann condition */
    else          return 1.0; /* robin condition */
}

VPRIVATE double my_scalarGN(int d, int m,  int sType, double scalarA, double scalarC, double *x) {
    double value;
    value = 0.0;
    return value;
}

VPRIVATE void my_DA(int d, int m,  int sType, double *x, double *DA) { 
    DA[0] = 0.e0; 
    DA[1] = 0.e0; 
    DA[2] = 0.e0; 
}


VPRIVATE void my_C(int d, int m, double x[], double f[])
{
    int i;
    for (i=0; i<d; i++) f[i] = 0.;
}

VPRIVATE void my_D(int d, int m,  int sType, double *x, double *f) {
    f[0] = 0.0;
    f[1] = 0.0;
    f[2] = 0.0;
}

VPRIVATE void my_BodyForce(int d, int m, double x[], double f[], int sType)
{
    int i;
    for (i=0; i<d; i++)  f[i] = 0.0; 
    if ((P_FRC==0) || (P_FRC==2)) {
        //if (sType == 1)  f[1] = 0.2;
    }
}

VPRIVATE void my_SurfForce(int d, int m, double x[], double nvec[], double f[], int fType)
{
    int i;
    for (i=0; i<d; i++) f[i] = 0.;
    if ((P_FRC==1) || (P_FRC==2)) {
        if (fType == 4) f[2] = 0.005; 
    }
}

VPRIVATE void my_US(int d, int m, int vDomain, double *x, double *f) 
{
    int i;    

    for (i=0; i<d; i++) f[i] = 0.;
    if(PDE_ID == 1 || PDE_ID == 2) f[0] = UU(d,m,vDomain,x);
}


/*
 * Elasticity parameters:  specify (E,nu) to yield (lambda,mu)
 *    E      = 21.                                 Young's modulus; dimensional of stress (Pa or GPa)
 *    nu     = .28                                 Poisson ratio
 *    lambda = (E * nu) / ( (1+nu) * (1-2*nu) )    3D relationships    Lame constant
 *    mu     = E / ( 2 * (1+nu) )                  3D relationships    Shear modulus
 *    lambda = (E * nu) / ( 1-nu^2 )               2D relationships    Lame constant
 *    mu     = E / ( 2 * (1+nu) )                  2D relationships    Shear modulus
 *
 * alternate elasticity parameters:  specify (lambda,mu) to yield (E,nu)
 *    lambda = 1.
 *    mu     = 1.
 *    E      = mu * (2 * mu + 3 * lambda) / ( lambda + mu )
 *    nu     = lambda / (2 * (lambda + mu) )
 */

VPRIVATE double my_E(void)
{
    //double E = 1.0;       /* rubber: 0.37 Gpa, kind of large? Wiki shows 0.01~0.1 Gpa */
    //double E = 2.0;       /* membrane:  0.1 GPa; 1GPa = 10 pN / A^2 */
    //double E = 2100.;     /* steel:     210 GPa; 1GPa = 10 pN / A^2 */
    return YoungsM;
}

VPRIVATE double my_NU(void)
{
    //double nu = .485;    /* rubber   */
    //double nu = .30;     /* membrane */
    //double nu = .28;     /* steel    */
    return PoissonR;
}

VPRIVATE double my_LAMBDA(void)
{
    double E  = my_E();
    double nu = my_NU();
    double lambda = 1.;
    lambda = (E * nu) / ( (1+nu) * (1-2*nu) );
    return lambda;
}

VPRIVATE double my_MU(void)
{
    double E  = my_E();
    double nu = my_NU();
    double mu = 1.;
    mu = E / ( 2 * (1+nu) );
    return mu;
}

VPRIVATE void formET(int d, double dU[3][3], double ET[3][3])
{
    int i, j, k;

    /* form the strain tensor */
    for (i=0; i<d; i++) {
        for (j=0; j<d; j++) {
            ET[i][j] = dU[i][j] + dU[j][i];
            if (P_GEO==1) {
                for (k=0; k<d; k++)
                    ET[i][j] += ( dU[k][i] * dU[k][j] );
            }
            ET[i][j] *= .5;
        }
    }
}

VPRIVATE void formST(int d, double A[3][3][3][3], double ET[3][3],
    double ST[3][3], double dST[3][3][3][3])
{
    /* form the strain tensor for linear material, possibly nonlinear deformation */
    int i, j, p, q;
    double TU[3][3], IU[3][3];

    /* trace of the (nonlinear) strain tensor */
    
    trET = 0.0;
    for(i=0; i<d; i++) trET += ET[i][i];

    if (P_MAT==0) {
        for (i=0; i<d; i++) {
            for (j=0; j<d; j++) {
                TU[i][j] = lambda*trET*I[i][j] + 2.0*mu*ET[i][j];
                IU[i][j] = I[i][j] + dU[i][j];
                ST[i][j] = 0.0;
            }
        }
        for (i=0; i<d; i++) {
            for (j=0; j<d; j++) {
               for(q=0; q<3; q++) ST[i][j] += IU[i][q]*TU[q][j];
            }
        }
    } else {
        Vnm_print(2, "formST: Nonlinear stress-strain relation not defined!\n");
    }
}
