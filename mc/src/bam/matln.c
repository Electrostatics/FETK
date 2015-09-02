/*
 * ***************************************************************************
 * MC = < Manifold Code >
 * Copyright (C) 1994-- Michael Holst 
 *
 * This library is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public 
 * License as published by the Free Software Foundation; either  
 * version 2.1 of the License, or (at your option) any later version. 
 *
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details. 
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library; if not, write to the Free Software  
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA   
 * 
 * rcsid="$Id: matln.c,v 1.6 2010/08/12 05:18:28 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     matln.c
 *
 * Purpose:  Class Mat: linked list data structures.
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */

#include "mat_p.h"

VEMBED(rcsid="$Id: matln.c,v 1.6 2010/08/12 05:18:28 fetk Exp $")

/*
 * ***************************************************************************
 * Class Mat: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_BAM)

#endif /* if !defined(VINLINE_BAM) */
/*
 * ***************************************************************************
 * Class Mat: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Mat_initStructureLN
 *
 * Purpose:  Initialize the nonzero structure given structure information.
 *
 * Notes:    This routine actually does the storage creation for all
 *           internal Vset, link arrays, and link pointer arrays.
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_initStructureLN(Mat *thee, MATformat frmt, MATsym sym)
{
    int i, sizeA;
    LinkA *mt;
    LinkRCS *mtX;

    /* use an upperbound for the maximum size of the Vset */
    sizeA = (thee->numR)*LN_MAX_ENTRIES_PER_ROW;

    /* build framework from input */
    thee->format = frmt;
    thee->sym    = sym;

    /* initialize the state */
    thee->state  = ZERO_STATE;

    /* Format-dependent consistency checks and setup */
    switch (thee->format) {

      /* RLN consistency checks and setup */
      case RLN_FORMAT:

        /* RLN valid for nonsymmetry */
        VASSERT( thee->sym==ISNOT_SYM );

        thee->lnkU = Vset_ctor( thee->vmem, "U", sizeof(LinkA), sizeA, 0 );

        /* create an empty entry to start each row of the matrix */
        for (i=0; i<(thee->numR); i++) {
            mt=(LinkA*)Vset_create(thee->lnkU);
            mt->idx  = -1;
            mt->val  = 0.;
            mt->next = VNULL;
        }

        thee->numO = 0;

        break;

      /* CLN consistency checks and setup */
      case CLN_FORMAT:

        /* RLN valid for nonsymmetry */
        VASSERT( thee->sym==ISNOT_SYM );

        thee->lnkL = Vset_ctor( thee->vmem, "L", sizeof(LinkA), sizeA, 0 );

        /* create an empty entry to start each column of the matrix */
        for (i=0; i<(thee->numC); i++) {
            mt=(LinkA*)Vset_create(thee->lnkL);
            mt->idx  = -1;
            mt->val  = 0.;
            mt->next = VNULL;
        }

        thee->numO = 0;

        break;

      /* XLN consistency checks and setup */
      case XLN_FORMAT:

          switch( sym ) {
            case IS_SYM:
              thee->lnkU = Vset_ctor( thee->vmem,"X",sizeof(LinkRCS),sizeA,0 );
              thee->numA = thee->numR;
              thee->xln = Vmem_malloc( thee->vmem,thee->numA,sizeof(LinkRCS) );

              /* create a zero entries to start the diagonal of the matrix */
              for (i=0; i<(thee->numR); i++) {
                  mtX = &( ((LinkRCS*) (thee->xln))[i] );
                  mtX->idxT = i;
                  mtX->idx = i;
                  mtX->nxtT = VNULL;
                  mtX->next = VNULL;
                  mtX->val = 0.;
              }
              break;
            case STRUC_SYM:
              thee->lnkU = Vset_ctor( thee->vmem,"X",sizeof(LinkRCN),sizeA,0 );
              thee->numA = thee->numR;
              thee->xln = Vmem_malloc( thee->vmem,thee->numA,sizeof(LinkRCS) );

              /* create a zero entries to start the diagonal of the matrix */
              for (i=0; i<(thee->numR); i++) {
                  mtX = &( ((LinkRCS*) (thee->xln))[i] );
                  mtX->idxT = i;
                  mtX->idx = i;
                  mtX->nxtT = VNULL;
                  mtX->next = VNULL;
                  mtX->val = 0.;
              }
              break;
            case ISNOT_SYM:
              thee->lnkU = Vset_ctor( thee->vmem,"X",sizeof(LinkRCS),sizeA,0 );
              thee->numA = thee->numR + thee->numC;
              thee->xln = Vmem_malloc( thee->vmem,thee->numA,sizeof(LinkRC*) );
              thee->xlnt = (void*) &( ((LinkRC**) (thee->xln))[thee->numR] );
              break;
            default:
              VASSERT(0);
              break;
        }

        thee->numO = 0;

        break;
      default:
        VASSERT(0);
        break;
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_killStructureLN
 *
 * Purpose:  Kill the nonzero structure and structure information.
 *
 * Notes:    This routine does the reverse of Mat_initStructureLN
 *           (or Mat_copyStructureLN).  It leaves only the information
 *           about the number of blocks, number of rows, and number of
 *           columns per block.  I.e., what is left is only what was
 *           present after the initial call to Mat_ctor.
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_killStructureLN(Mat *thee)
{
    if (thee != VNULL) {
        if (thee->state != NULL_STATE) {

            /* Format-dependent destruction */
            switch (thee->format) {

              case RLN_FORMAT:
                if (thee->lnkU != VNULL) {
                    Vset_dtor( &(thee->lnkU) );
                }
                break;

              case CLN_FORMAT:
                if (thee->lnkL != VNULL) {
                    Vset_dtor( &(thee->lnkL) );
                }
                break;

              case XLN_FORMAT:
                if (thee->lnkU != VNULL)
                    Vset_dtor( &(thee->lnkU) );

                if (thee->xln != VNULL) {
                    if ( Mat_sym(thee) == ISNOT_SYM ) {
                        Vmem_free( thee->vmem, thee->numA, sizeof(LinkRC*),
                                   (void**)&(thee->xln));
                    } else {
                        Vmem_free( thee->vmem, thee->numA, sizeof(LinkRCS),
                                   (void**)&(thee->xln));
                    }
                }

                thee->numA = 0;
                break;

              default:
                VASSERT(0);
                break;
            }

            /* initialize the state */
            thee->state = NULL_STATE;

        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_accessXLN
 *
 * Purpose:  Access the first element in the ROW or COL of an XLN.
 *
 *   Notes:  key==0 ==> return a ROW pointer
 *           key==1 ==> return a COL pointer
 *
 *           In the symmetric cases, we are just returning a pointer
 *           to the diagonal.  In the nonsymmetric case, we are returning
 *           a pointer to the first element in the row or column.  In
 *           the symmetric cases the columns are linked in reverse index
 *           ordering to save the storage of an additional pointer array.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC LinkRC* Mat_accessXLN(Mat *thee, int idx, int key)
{
    if ( thee->sym != ISNOT_SYM /* && ( key == 0 || key == 1 ) */ ) {

        return (LinkRC*) &(((LinkRCS*) (thee->xln))[idx]);

    } else if ( key == 0 /* && thee->sym == ISNOT_SYM */ ) {

        return ((LinkRC**) (thee->xln))[idx];

    } else /* if (key == 1 && thee->sym == ISNOT_SYM ) */ {

        return ((LinkRC**) (thee->xlnt))[idx];
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_contribXLN
 *
 * Purpose:  Set or add a value to a doubly linked matrix entry array.
 *
 *   Notes:  key==0 ==> Set the value
 *           key==1 ==> Add the value
 *
 *           This is a doubly linked variant of mContrib.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_contribXLN(Mat *thee, int key, int i, int j, double val)
{
    switch (thee->sym) {
      case IS_SYM:
        Mat_contribSYMXLN( thee, key, i, j, val );
        break;
      case STRUC_SYM:
        Mat_contribSSYMXLN( thee, key, i, j, val );
        break;
      case ISNOT_SYM:
        Mat_contribNSYMXLN( thee, key, i, j, val );
        break;
      default:
        VASSERT( 0 );
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_contribNSYMXLN
 *
 * Purpose:  Set or add a value to a NOTSYM XLN matrix.
 *
 *   Notes:  key==0 ==> Set the value
 *           key==1 ==> Add the value
 *
 *           This is a doubly linked variant of mContrib.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_contribNSYMXLN(Mat *thee, int key, int i, int j, double val)
{
    int flag = 0, done = 0;
    LinkRC *curr = VNULL, *prev = VNULL, *mnew = VNULL;

    VASSERT( thee->sym == ISNOT_SYM );

    /* STEP 1:  Traverse rowwise to the location for insert/set/contrib */
    curr = ((LinkRC**) (thee->xln))[i];
    prev = VNULL;
    done = 0;
    flag = 0;
    while (!done) {
        if (curr == VNULL) {
            /* first guy in row is "NULL", fill him with the info */
            mnew = (LinkRC*)Vset_create(thee->lnkU);
            mnew->idxT  = i;
            mnew->idx  = j;
            mnew->nextT  = VNULL;
            mnew->next  = VNULL;
            ((LinkRCS*) mnew)->val = val;
            ((LinkRC**) (thee->xln))[i] = mnew;
            thee->numO++;
            done = 1;
            flag = 1;
        } else if (curr->idx > j) {
            /* not in the list; insert new link between curr and prev */
            mnew = (LinkRC*)Vset_create(thee->lnkU);
            mnew->idxT  = i;
            mnew->idx  = j;
            mnew->nextT  = VNULL;
            mnew->next  = VNULL;
            ((LinkRCS*) mnew)->val = val;
            if (prev == VNULL) {
                ((LinkRC**) (thee->xln))[i] = mnew;
                mnew->next = curr;
            } else {
                prev->next = mnew;
                mnew->next = curr;
            }
            thee->numO++;
            done = 1;
            flag = 1;
        } else if (curr->idx == j) {
            /* found the position; just add the contribution */
            mnew = (LinkRC*)curr;
            if (key == 0)
                ((LinkRCS*) mnew)->val  = val;
            else
                ((LinkRCS*) mnew)->val += val;
            done = 1;
            flag = 0;
        } else if (curr->next == VNULL) {
            /* not found; no one left, append on the end */
            mnew = (LinkRC*)Vset_create(thee->lnkU);
            mnew->idxT  = i;
            mnew->idx  = j;
            ((LinkRCS*) mnew)->val = val;
            mnew->next  = VNULL;
            curr->next  = (LinkRC*)mnew;
            thee->numO++;
            done  = 1;
            flag  = 1;
            /* not found yet; still hope */
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    if (flag == 0) {
        /* exit now if no new links were inserted */
        return;
    }

    /* STEP 2:  Traverse colwise to find the location for insertion */
    curr = ((LinkRC**) (thee->xlnt))[j];
    prev = VNULL;
    done = 0;
    while (!done) {
        if (curr == VNULL) {
            /* first guy in col is "NULL", set to point to new link */
            ((LinkRC**) (thee->xlnt))[j] = mnew;
            done = 1;
        } else if (curr->idxT > i) {
            /*  not in the list; insert new link between curr and prev */
            if (prev == VNULL) {
                ((LinkRC**) (thee->xlnt))[j] = mnew;
                mnew->nextT = curr;
            } else {
                prev->nextT = mnew;
                mnew->nextT = curr;
            }
            done = 1;
        } else if (curr->nextT == VNULL) {
            /* not found; no one left; set the last pointer to new link */
            curr->nextT = mnew;
            done = 1;
            /* not found yet; still hope */
        } else {
            prev = curr;
            curr = curr->nextT;
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_contribSSYMXLN
 *
 * Purpose:  Set or add a value to a STRUC_SYM XLN matrix.
 *
 *   Notes:  key==0 ==> Set the value
 *           key==1 ==> Add the value
 *
 *           This is a doubly linked variant of mContrib.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_contribSSYMXLN(Mat *thee, int key, int i, int j, double val)
{
    int ii = i, jj = j, flag = 0, done = 0, contribTYPE = 0;
    LinkRC *curr = VNULL, *prev = VNULL, *mnew = VNULL;

    VASSERT( thee->sym == STRUC_SYM );

    if ( i > j ) {
        ii = j;
        jj = i;
        contribTYPE = 1;
    }

    /* STEP 1:  Traverse rowwise to the location for insert/set/contrib */
    curr = (LinkRC*) &(((LinkRCS*) (thee->xln))[ii]);
    prev = VNULL;
    done = 0;
    flag = 0;
    while (!done) {
        if (curr->idx > jj) {
            /* not in the list; insert new link between curr and prev */
            mnew = (LinkRC*)Vset_create(thee->lnkU);
            mnew->idxT  = ii;
            mnew->idx  = jj;
            if ( contribTYPE == 0) {
                ((LinkRCN*) mnew)->val = val;
                ((LinkRCN*) mnew)->valT = 0.0;
            } else {
                ((LinkRCN*) mnew)->val = 0.0;
                ((LinkRCN*) mnew)->valT = val;
            }
            mnew->nextT  = VNULL;
            mnew->next  = VNULL;
            prev->next = mnew;
            mnew->next = curr;
            thee->numO++;
            done = 1;
            flag = 1;
        } else if (curr->idx == jj) {
            /* found the position; just add the contribution */
            mnew = (LinkRC*)curr;
            if ( contribTYPE == 0 ) {
                if (key == 0)
                    ((LinkRCS*) mnew)->val  = val;
                else
                    ((LinkRCS*) mnew)->val += val;
            } else {
                if (key == 0)
                    ((LinkRCN*) mnew)->valT  = val;
                else
                    ((LinkRCN*) mnew)->valT += val;
            }
            done = 1;
            flag = 0;
        } else if (curr->next == VNULL) {
            /* not found; no one left, append on the end */
            mnew = (LinkRC*)Vset_create(thee->lnkU);
            mnew->idxT  = ii;
            mnew->idx  = jj;
            if ( contribTYPE == 0) {
                ((LinkRCN*) mnew)->val = val;
                ((LinkRCN*) mnew)->valT = 0.0;
            } else {
                ((LinkRCN*) mnew)->val = 0.0;
                ((LinkRCN*) mnew)->valT = val;
            }
            mnew->next  = VNULL;
            curr->next  = (LinkRC*)mnew;
            thee->numO++;
            done  = 1;
            flag  = 1;
            /* not found yet; still hope */
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    if (flag == 0) {
        /* exit now if no new links were inserted */
        return;
    }

    /* STEP 2:  Traverse colwise to find the location for insertion */
    curr = (LinkRC*) &(((LinkRCS*) (thee->xln))[jj]);
    prev = VNULL;
    done = 0;
    while (!done) {
        if (curr->idxT < ii) {
            /*  not in the list; insert new link between curr and prev */
            prev->nextT = mnew;
            mnew->nextT = curr;
            done = 1;
        } else if (curr->nextT == VNULL) {
            /* not found; no one left; set the last pointer to new link */
            curr->nextT = mnew;
            done = 1;
            /* not found yet; still hope */
        } else {
            prev = curr;
            curr = curr->nextT;
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_contribSYMXLN
 *
 * Purpose:  Set or add a value to a SYM XLN Matrix.
 *
 *   Notes:  key==0 ==> Set the value
 *           key==1 ==> Add the value
 *
 *           This is a doubly linked variant of mContrib.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_contribSYMXLN(Mat *thee, int key, int i, int j, double val)
{
    int flag = 0, done = 0;
    LinkRC *curr = VNULL, *prev = VNULL, *mnew = VNULL;

    VASSERT( thee->sym == IS_SYM );
    VASSERT( i <= j );

    /* STEP 1:  Traverse rowwise to the location for insert/set/contrib */
    curr = (LinkRC*) &(((LinkRCS*) (thee->xln))[i]);
    prev = VNULL;
    done = 0;
    flag = 0;
    while (!done) {
        if (curr->idx > j) {
            /* not in the list; insert new link between curr and prev */
            mnew = (LinkRC*)Vset_create(thee->lnkU);
            mnew->idxT  = i;
            mnew->idx  = j;
            mnew->nextT  = VNULL;
            mnew->next  = VNULL;
            ((LinkRCS*) mnew)->val = val;
            VASSERT(prev != VNULL);
            prev->next = mnew;
            mnew->next = curr;
            thee->numO++;
            done = 1;
            flag = 1;
        } else if (curr->idx == j) {
            /* found the position; just add the contribution */
            mnew = (LinkRC*)curr;
            if (key == 0)
                ((LinkRCS*) mnew)->val  = val;
            else
                ((LinkRCS*) mnew)->val += val;
            done = 1;
            flag = 0;
        } else if (curr->next == VNULL) {
            /* not found; no one left, append on the end */
            mnew = (LinkRC*)Vset_create(thee->lnkU);
            mnew->idxT  = i;
            mnew->idx  = j;
            ((LinkRCS*) mnew)->val = val;
            mnew->next  = VNULL;
            curr->next  = (LinkRC*)mnew;
            thee->numO++;
            done  = 1;
            flag  = 1;
            /* not found yet; still hope */
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    if (flag == 0) {
        /* exit now if no new links were inserted */
        return;
    }

    /* STEP 2:  Traverse colwise to find the location for insertion */
    curr = (LinkRC*) &(((LinkRCS*) (thee->xln))[j]);
    prev = VNULL;
    done = 0;
    while (!done) {
        if (curr->idxT < i) {
            /*  not in the list; insert new link between curr and prev */
            prev->nextT = mnew;
            mnew->nextT = curr;
            done = 1;
        } else if (curr->nextT == VNULL) {
            /* not found; no one left; set the last pointer to new link */
            curr->nextT = mnew;
            done = 1;
            /* not found yet; still hope */
        } else {
            prev = curr;
            curr = curr->nextT;
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_printLN
 *
 * Purpose:  Print an LN format matrix as a DENSE matrix in MATLAB format.
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_printLN(Mat *thee)
{
    int i, j;
    int numR, numC;
    char rn[80];
    const int MaxRows = 30;
    const int MaxCols = 30;
    double matrix[30][30];
    LinkA *mt;
    LinkRC *mtX;

    numR = thee->numR;
    numC = thee->numC;

    strncpy(rn,"Mat_printLN:",80);

    /* some i/o */
    Vnm_print(0, "%s printing <%s>" " [dim=(%dx%d),sym=%d,numA=%d]\n",
        rn, thee->name, numR, numC, thee->sym, thee->numA);

    /* size check */
    if ((numR > MaxRows) || (numC > MaxCols)) {
        Vnm_print(0, "%smatrix too large to view....skipping.\n", rn);
        return;
    }

    /* make a dense matrix first */
    for (i=0; i<numR; i++)
        for (j=0; j<numC; j++)
            matrix[i][j] = 0.0;

    if (thee->state != NULL_STATE) {

        switch (thee->format) {

          case RLN_FORMAT:
            for (i=0; i<numR; i++) {
                for (mt=(LinkA*)Vset_access(thee->lnkU,i);
                     mt!=VNULL; mt=mt->next) {
                    if (mt->idx >= 0) {
                        j = mt->idx;
                        matrix[i][j] = mt->val;
                    }
                }
            }
            break;

          case CLN_FORMAT:
            for (j=0; j<numC; j++) {
                for (mt=(LinkA*)Vset_access(thee->lnkL,j);
                     mt!=VNULL; mt=mt->next) {
                    if (mt->idx >= 0) {
                        i = mt->idx;
                        matrix[i][j] = mt->val;
                    }
                }
            }
            break;

          case XLN_FORMAT:
            for (i=0; i<numR; i++) {
                if ( thee->sym == ISNOT_SYM ) {
                    mtX = ((LinkRC**) thee->xln)[i];
                } else {
                    mtX = (LinkRC*) &( ((LinkRCS*) thee->xln)[i] );
                    matrix[i][i] = ((LinkRCS*) mtX)->val;
                    mtX = mtX->next;
                }
                for ( /* no-op */ ; mtX!=VNULL; mtX=mtX->next) {
                    j = mtX->idx;
                    if (j < numC) {
                        if ( thee->sym == ISNOT_SYM ) {
                            matrix[i][j] = ((LinkRCS*) mtX)->val;
                        } else if ( thee->sym == IS_SYM ) {
                            matrix[i][j] = ((LinkRCS*) mtX)->val;
                            matrix[j][i] = ((LinkRCS*) mtX)->val;
                        } else {
                            matrix[i][j] = ((LinkRCN*) mtX)->val;
                            matrix[j][i] = ((LinkRCN*) mtX)->valT;
                        }
                    }
                }
            }
            break;
          default:
            Vnm_print(0,
              "%smatrix not in correct format to print....skipping.\n", rn);
            break;
        }
    }

    /* print the matrix */
    Vnm_print(0, "%s = [\n", thee->name);
    for (i=0; i<numR; i++) {
        for (j=0; j<numC; j++) {
            if (VABS(matrix[i][j]) < 0.0001) {
                Vnm_print(0, "  0.0  ");
            } else {
                Vnm_print(0, "%7.3f", matrix[i][j]);
            }
        }
        Vnm_print(0, "\n");
    }
    Vnm_print(0, "];\n");
}

/*
 * ***************************************************************************
 * Routine:  Mat_printLNSp
 *
 * Purpose:  Print an LN format matrix as a SPARSE matrix in MATLAB format.
 *
 *   Notes:  flag==0 ==> write
 *           flag==1 ==> append
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_printLNSp(Mat *thee, char *fname, int pflag)
{
    int i, j;
    int numR, numC;
    char rn[80];
    FILE *fp;
    LinkA *mt;
    LinkRC *mtX;

    numR = thee->numR;
    numC = thee->numC;

    strncpy(rn,"Mat_printSp:",80);

    if (pflag == 0) {
      fp=fopen(fname,"w");
    } else if (pflag == 1) {
      fp=fopen(fname,"a");
    } else {
      fp=VNULL;
    }

    if (fp==VNULL) {
        Vnm_print(2, "%s problem opening file <%s>\n", rn, fname);
        return;
    }

    Vnm_print(0,"%s printing <%s> [dim=(%dx%d)] to file <%s>..",
        rn,thee->name,numR,numC,fname);

    /* print the matrix in matlab sparse format */
    fprintf(fp,"%% %s matrix <%s> [dim=(%dx%d)]\n",
        rn, thee->name, numR, numC);
    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp, "fprintf('Defining %s_IJA..');", thee->name);
    fprintf(fp, "\n%s_IJA = [\n", thee->name);

    if (thee->state != NULL_STATE) {

        switch (thee->format) {

          case RLN_FORMAT:
            for (i=0; i<numR; i++) {
                for (mt=(LinkA*)Vset_access(thee->lnkU,i);
                     mt!=VNULL; mt=mt->next) {
                    if (mt->idx >= 0) {
                        j = mt->idx;
                        fprintf(fp, "    %d    %d    %15.8e\n",
                            i+1, j+1, mt->val);
                    }
                }
            }
            break;

          case CLN_FORMAT:
            for (j=0; j<numC; j++) {
                for (mt=(LinkA*)Vset_access(thee->lnkL,j);
                     mt!=VNULL; mt=mt->next) {
                    if (mt->idx >= 0) {
                        i = mt->idx;
                        fprintf(fp, "    %d    %d    %15.8e\n",
                            i+1, j+1, mt->val);
                    }
                }
            }
            break;

          case XLN_FORMAT:
            for (i=0; i<numR; i++) {
                if ( thee->sym == ISNOT_SYM ) {
                    mtX = ((LinkRC**) thee->xln)[i];
                } else {
                    mtX = (LinkRC*) &( ((LinkRCS*) thee->xln)[i] );
                    fprintf(fp, "    %d    %d    %15.8e\n",
                        i+1, i+1, ((LinkRCS*) mtX)->val );
                    mtX = mtX->next;
                }
                for ( /* no-op */ ; mtX!=VNULL; mtX=mtX->next) {
                    j = mtX->idx;
                    if (j < numC) {
                        if ( thee->sym == ISNOT_SYM ) {
                            fprintf(fp, "    %d    %d    %15.8e\n",
                                i+1, j+1, ((LinkRCS*) mtX)->val );
                        } else if ( thee->sym == IS_SYM ) {
                            fprintf(fp, "    %d    %d    %15.8e\n",
                                i+1, j+1, ((LinkRCS*) mtX)->val );
                            fprintf(fp, "    %d    %d    %15.8e\n",
                                j+1, i+1, ((LinkRCS*) mtX)->val );
                        } else {
                            fprintf(fp, "    %d    %d    %15.8e\n",
                                i+1, j+1, ((LinkRCN*) mtX)->val );
                            fprintf(fp, "    %d    %d    %15.8e\n",
                                j+1, i+1, ((LinkRCN*) mtX)->valT );
                        }
                    }
                }
            }
            break;
          default:
            Vnm_print(0,
              "%smatrix not in correct format to print....skipping.\n", rn);
            break;
        }
    }

    fprintf(fp, "];\n\n");
    fprintf(fp, "fprintf('..done.\\n');\n");
    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp,"%% Matlab code to generate sparse matrix.\n");
    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp,
      "%s = sparse(%s_IJA(:,1),%s_IJA(:,2),%s_IJA(:,3),%d,%d);\n",
      thee->name, thee->name, thee->name, thee->name, numR, numC);
    fprintf(fp,"%% ----------------------------------------\n");

    Vnm_print(0,"..done.\n");

    /* close file and return */
    fclose(fp);
}


