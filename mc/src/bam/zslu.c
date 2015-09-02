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
 * rcsid="$Id: zslu.c,v 1.4 2010/08/12 05:18:32 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     zslu.c
 *
 * Purpose:  Class Zslu: Wrapper class for a generic sparse direct solver.
 *           (THIS IS FOR SUPERLU 2.0 _OR_ SUPERLU 3.1)
 *
 * Notes:    Our current choice of a sparse direct solver is the excellent
 *           SuperLU code, which is a native ANSI-C code developed at
 *           UC Berkeley, LBL, and Xerox by J.W. Demmel, J.R. Gilbert,
 *           and X.S. Li.
 *
 *           In the past I had used YSMP extensively as a direct coarse
 *           solver in multilevel codes, but my understanding is that it is
 *           not freely distributable now.  In addition, it was a FORTRAN code
 *           that I usually converted to C using f2c, so that it was not
 *           as easy to work with in a C environment.
 *
 *           #undef  _USE_SUPERLU_31     (Use SuperLU 2.0)
 *           #define _USE_SUPERLU_31     (Use SuperLU 3.1)
 *
 * Author:   Michael Holst (this wrapper only)
 * ***************************************************************************
 */

#define _USE_SUPERLU_31
/* #undef _USE_SUPERLU_31 */


#include "zslu_p.h"
#include <punc/vsuperlu.h>

#if !defined(_USE_SUPERLU_31)
#include "dsp_defs.h"
#include "util.h"
#endif

VEMBED(rcsid="$Id: zslu.c,v 1.4 2010/08/12 05:18:32 fetk Exp $")

VPUBLIC Vmem *zsluVmem = VNULL;

/*
 * ***************************************************************************
 * Class Zslu: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_ZSLU)

#endif /* if !defined(VINLINE_ZSLU) */
/*
 * ***************************************************************************
 * Class Zslu: Non-inlineable methods
 * ***************************************************************************
 */

#define USE_DGSSV 0

/*
 * ***************************************************************************
 * Routine:  Zslu_ctor
 *
 * Purpose:  The Zslu constructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
#if defined(_USE_SUPERLU_31) /* Use SuperLU 3.1 */
VPUBLIC Zslu* Zslu_ctor(Vmem *vmem, int skey, int m, int n, int nnz,
    int *ia, int *ja, double *a)
{
    NCformat *Astore;
    SuperMatrix *AA;
    Zslu* thee = VNULL;

    VDEBUGIO("Zslu_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Zslu) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Zslu" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }
    zsluVmem = thee->vmem;

    /* settings */
    thee->statLU = 0;
    thee->skey   = skey;
    thee->m      = m;
    thee->n      = n;
    thee->nnz    = nnz;
    thee->nrhs   = 1;
    thee->lwork  = 0;

    /* arrays */
    thee->a  = a;
    thee->ia = ia;
    thee->ja = ja;

    VDEBUGIO("..done.\n");

    /* create permutation arrays and factorization work area */
    thee->pr   = Vmem_malloc( thee->vmem, thee->m, sizeof(int) );
    thee->pc   = Vmem_malloc( thee->vmem, thee->n, sizeof(int) );
    thee->et   = Vmem_malloc( thee->vmem, thee->n, sizeof(int) );
    thee->ferr = Vmem_malloc( thee->vmem, thee->nrhs, sizeof(double) );
    thee->berr = Vmem_malloc( thee->vmem, thee->nrhs, sizeof(double) );
    thee->rhsb = Vmem_malloc( thee->vmem, thee->m, sizeof(double) );
    thee->rhsx = Vmem_malloc( thee->vmem, thee->m, sizeof(double) );
    thee->R    = Vmem_malloc( thee->vmem, thee->m, sizeof(double) );
    thee->C    = Vmem_malloc( thee->vmem, thee->n, sizeof(double) );

    /* create supermatrices */
    thee->A    = Vmem_malloc( thee->vmem, 1, sizeof(SuperMatrix) );
    thee->L    = Vmem_malloc( thee->vmem, 1, sizeof(SuperMatrix) );
    thee->U    = Vmem_malloc( thee->vmem, 1, sizeof(SuperMatrix) );
    thee->B    = Vmem_malloc( thee->vmem, 1, sizeof(SuperMatrix) );
    thee->X    = Vmem_malloc( thee->vmem, 1, sizeof(SuperMatrix) );

    /* we only allow col-wise YSMP ordering (otherwise storage is doubled!) */
    VASSERT( thee->skey == 1 );

    /* create supermatrix A in the format expected by SuperLU */
    /* NOTE: this is a hand-off of <a,ia,ja> from caller; WE are then  */
    /* responsible for freeing the storage for <a,ia,ja> in destructor */
    dCreate_CompCol_Matrix(thee->A,
        thee->m,thee->n,thee->nnz, thee->a,thee->ja,thee->ia,
        SLU_NC,SLU_D,SLU_GE);
    AA = (SuperMatrix*)thee->A;
    Astore = AA->Store;
    printf("Dimension %dx%d; # nonzeros %d\n", AA->nrow, AA->ncol, Astore->nnz);
    dCreate_Dense_Matrix(thee->B, thee->m, thee->nrhs, thee->rhsb, thee->m,
        SLU_DN, SLU_D, SLU_GE);
    dCreate_Dense_Matrix(thee->X, thee->m, thee->nrhs, thee->rhsx, thee->m,
        SLU_DN, SLU_D, SLU_GE);

    /* malloc table for stats and initialize */
    thee->stat = Vmem_malloc( thee->vmem, 1, sizeof( SuperLUStat_t ) );
    StatInit(thee->stat);

    /* malloc table for options and initialize */
    /*
     * Set the default values for options argument:
     * options.Fact = DOFACT;
     * options.Equil = YES;
     * options.ColPerm = COLAMD;
     * options.DiagPivotThresh = 1.0;
     * options.Trans = NOTRANS;
     * options.IterRefine = NOREFINE;
     * options.SymmetricMode = NO;
     * options.PivotGrowth = NO;
     * options.ConditionNumber = NO;
     * options.PrintStat = YES;
     */
    thee->opts = Vmem_malloc( thee->vmem, 1, sizeof( superlu_options_t ) );
    set_default_options(thee->opts);

    /* return */
    return thee;
}
#else /* Use SuperLU 2.0 */
VPUBLIC Zslu* Zslu_ctor(Vmem *vmem, int skey, int m, int n, int nnz,
    int *ia, int *ja, double *a)
{
    int        panel_size, relax;
    static int statInit = 0;
    Zslu* thee = VNULL;

    VDEBUGIO("Zslu_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Zslu) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Zslu" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }
    zsluVmem = thee->vmem;

    /* settings */
    thee->statLU = 0;
    thee->skey   = skey;
    thee->m      = m;
    thee->n      = n;
    thee->nnz    = nnz;

    /* arrays */
    thee->a  = a;
    thee->ia = ia;
    thee->ja = ja;

    VDEBUGIO("..done.\n");

    /* create permutation arrays and factorization work area */
    thee->pr = Vmem_malloc( thee->vmem, thee->m, sizeof(int) );
    thee->pc = Vmem_malloc( thee->vmem, thee->n, sizeof(int) );
    thee->et = Vmem_malloc( thee->vmem, thee->n, sizeof(int) );

    /* create supermatrices */
    thee->A  = Vmem_malloc( thee->vmem, 1, sizeof(SuperMatrix) );
    thee->L  = Vmem_malloc( thee->vmem, 1, sizeof(SuperMatrix) );
    thee->U  = Vmem_malloc( thee->vmem, 1, sizeof(SuperMatrix) );
    thee->AC = Vmem_malloc( thee->vmem, 1, sizeof(SuperMatrix) );

    /* we only allow col-wise YSMP ordering (otherwise storage is doubled!) */
    VASSERT( thee->skey == 1 );

    /* create supermatrix A in the format expected by SuperLU */
    /* NOTE: this is a hand-off of <a,ia,ja> from caller; WE are then  */
    /* responsible for freeing the storage for <a,ia,ja> in destructor */
    dCreate_CompCol_Matrix(thee->A,
        thee->m,thee->n,thee->nnz, thee->a,thee->ja,thee->ia, NC,__D,GE);

    /* hmmm...malloc global table for stats; SuperLU segfaults otherwise... */
    panel_size = sp_ienv(1);
    relax = sp_ienv(2);
    if (!statInit) {
        statInit = 1;
        StatInit(panel_size, relax);  /* does some mallocs for the table */
    }

    /* return */
    return thee;
}
#endif

/*
 * ***************************************************************************
 * Routine:  Zslu_dtor
 *
 * Purpose:  The Zslu destructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
#if defined(_USE_SUPERLU_31) /* Use SuperLU 3.1 */
VPUBLIC void Zslu_dtor(Zslu **thee)
{
    VASSERT( (*thee) != VNULL );
    if ((*thee) != VNULL) {

        /*
         * NOTE: due to a change in the Slu API, the input arrays <a,ia,ja>
         *       are NOT malloc'd or free'd by the Zslu ctor/dtor; any
         *       storage associated with those pointers is now handled
         *       by code which calls Zslu_ctor and Zslu_dtor.
         */

        /* destroy the primary supermatrix storage areas */
        Destroy_SuperMatrix_Store((*thee)->A);
        Destroy_SuperMatrix_Store((*thee)->B);
        Destroy_SuperMatrix_Store((*thee)->X);
        if ( (*thee)->lwork >= 0 ) {
            Destroy_SuperNode_Matrix((*thee)->L);
            Destroy_CompCol_Matrix((*thee)->U);
        }

        /* destroy supermatrix structures themselves */
        Vmem_free( (*thee)->vmem, 1, sizeof(SuperMatrix),
            (void**)&((*thee)->A) );
        Vmem_free( (*thee)->vmem, 1, sizeof(SuperMatrix),
            (void**)&((*thee)->L) );
        Vmem_free( (*thee)->vmem, 1, sizeof(SuperMatrix),
            (void**)&((*thee)->U) );
        Vmem_free( (*thee)->vmem, 1, sizeof(SuperMatrix),
            (void**)&((*thee)->B) );
        Vmem_free( (*thee)->vmem, 1, sizeof(SuperMatrix),
            (void**)&((*thee)->X) );

        /* free the permutation and other work areas */
        Vmem_free( (*thee)->vmem, (*thee)->m, sizeof(int),
            (void**)&((*thee)->pr) );
        Vmem_free( (*thee)->vmem, (*thee)->n, sizeof(int),
            (void**)&((*thee)->pc) );
        Vmem_free( (*thee)->vmem, (*thee)->n, sizeof(int),
            (void**)&((*thee)->et) );
        Vmem_free( (*thee)->vmem, (*thee)->nrhs, sizeof(double),
            (void**)&((*thee)->ferr) );
        Vmem_free( (*thee)->vmem, (*thee)->nrhs, sizeof(double),
            (void**)&((*thee)->berr) );
        Vmem_free( (*thee)->vmem, (*thee)->m, sizeof(double),
            (void**)&((*thee)->rhsb) );
        Vmem_free( (*thee)->vmem, (*thee)->m, sizeof(double),
            (void**)&((*thee)->rhsx) );
        Vmem_free( (*thee)->vmem, (*thee)->m, sizeof(double),
            (void**)&((*thee)->R) );
        Vmem_free( (*thee)->vmem, (*thee)->n, sizeof(double),
            (void**)&((*thee)->C) );

        /* free stat and opts */
        Vmem_free( (*thee)->vmem, 1, sizeof(SuperLUStat_t),
            (void**)&((*thee)->stat) );
        Vmem_free( (*thee)->vmem, 1, sizeof(superlu_options_t),
            (void**)&((*thee)->opts) );

        /* finally destroy this container */
        VDEBUGIO("Zslu_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Zslu), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;

        zsluVmem = VNULL;
    }
}
#else /* Use SuperLU 2.0 */
VPUBLIC void Zslu_dtor(Zslu **thee)
{
    VASSERT( (*thee) != VNULL );
    if ((*thee) != VNULL) {

        /*
         * NOTE: due to a change in the Zslu API, the input arrays <a,ia,ja>
         *       are NOT malloc'd or free'd by the Zslu ctor/dtor; any
         *       storage associated with those pointers is now handled
         *       by code which calls Zslu_ctor and Zslu_dtor.
         */

        /* destroy the primary supermatrix storage areas */
        Destroy_SuperMatrix_Store((*thee)->A);
        Destroy_SuperNode_Matrix((*thee)->L);  /* free L */
        Destroy_CompCol_Matrix((*thee)->U);    /* free U */
        Destroy_CompCol_Permuted((*thee)->AC); /* free AC (the permuted A) */

        /* destroy supermatrix structures themselves */
        Vmem_free( (*thee)->vmem, 1, sizeof(SuperMatrix),
            (void**)&((*thee)->A) );
        Vmem_free( (*thee)->vmem, 1, sizeof(SuperMatrix),
            (void**)&((*thee)->L) );
        Vmem_free( (*thee)->vmem, 1, sizeof(SuperMatrix),
            (void**)&((*thee)->U) );
        Vmem_free( (*thee)->vmem, 1, sizeof(SuperMatrix),
            (void**)&((*thee)->AC) );

        /* free the permutation and other work areas */
        Vmem_free( (*thee)->vmem, (*thee)->m, sizeof(int),
            (void**)&((*thee)->pr) );
        Vmem_free( (*thee)->vmem, (*thee)->n, sizeof(int),
            (void**)&((*thee)->pc) );
        Vmem_free( (*thee)->vmem, (*thee)->n, sizeof(int),
            (void**)&((*thee)->et) );

        /* Can't free single global "stat"; other Zslu guys may need it... */
        /* StatFree(); */  /* this would free the SuperLU stat table mallocs */

        /* finally destroy this container */
        VDEBUGIO("Zslu_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Zslu), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;

        zsluVmem = VNULL;
    }
}
#endif

/*
 * ***************************************************************************
 * Routine:  Zslu_factor
 *
 * Purpose:  Sparse LU factor the system.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
#if defined(_USE_SUPERLU_31) /* Use SuperLU 3.1 */
VPUBLIC int Zslu_factor(Zslu *thee)
{
    int   info;
    mem_usage_t mem_usage;
    double rpg, rcond;
    NCformat *Ustore;
    SCformat *Lstore;
    SuperMatrix *BB;
    superlu_options_t *oopts;

    VASSERT( thee != VNULL );

    oopts = (superlu_options_t*)thee->opts;

    /* is this first-time factorization or a refactor */
    if ( thee->statLU == 0 ) {
        /* this is a first-time factorization */
        oopts->Fact = DOFACT;
    } else {
        /* this is a re-factorization */
        oopts->Fact = DOFACT;
    }
    thee->statLU = 1;

    /* factorization of the matrix "A" */
    BB = (SuperMatrix*)thee->B;
    BB->ncol = 0;  /* Indicate not to solve the system */
#if USE_DGSSV
    dgssv(thee->opts, thee->A, thee->pc, thee->pr, thee->L, thee->U, thee->B,
          thee->stat, &info);
#else
    dgssvx(thee->opts, thee->A, thee->pc, thee->pr, thee->et, thee->equed,
           thee->R, thee->C, thee->L, thee->U,
           thee->work, thee->lwork, thee->B, thee->X, &rpg, &rcond,
           thee->ferr, thee->berr, &mem_usage, thee->stat, &info);
    oopts->Fact = FACTORED;
#endif

    /* some i/o */
    if ( info == 0 || info == (thee->n)+1 ) {

        if ( oopts->PivotGrowth ) printf("Recip. pivot growth = %e\n", rpg);
        if ( oopts->ConditionNumber )
            printf("Recip. condition number = %e\n", rcond);
        Lstore = (SCformat *) ((SuperMatrix*)thee->L)->Store;
        Ustore = (NCformat *) ((SuperMatrix*)thee->U)->Store;
        printf("No of nonzeros in factor L = %d\n", Lstore->nnz);
        printf("No of nonzeros in factor U = %d\n", Ustore->nnz);
        printf("No of nonzeros in L+U = %d\n",
            Lstore->nnz + Ustore->nnz - thee->n);
        printf("L\\U MB %.3f\ttotal MB needed %.3f\texpansions %d\n",
            mem_usage.for_lu/1e6, mem_usage.total_needed/1e6,
            mem_usage.expansions);
        fflush(stdout);

    } else if ( info > 0 && thee->lwork == -1 ) {
        printf("** Estimated memory: %d bytes\n", info - (thee->n));
    }

    if ( oopts->PrintStat ) StatPrint(thee->stat);
    StatFree(thee->stat);

    /* return: 1=success, 0=failure */
    if (info == 0) return 1;
    else           return 0;
}
#else /* Use SuperLU 2.0 */
VPUBLIC int Zslu_factor(Zslu *thee)
{
    int   i, pspec, info, panel_size, relax;
    char  refact[1];

    VASSERT( thee != VNULL );

    /* setup for the factorization */
    panel_size = sp_ienv(1);
    relax = sp_ienv(2);

    /* is this first-time factorization or a refactor */
    if ( thee->statLU == 0 ) {
        /* this is a first-time factorization */
        *refact = 'N';

        /* initial orderings */
        for (i=0; i<thee->m; i++) {
            thee->pr[i] = i;
        }
        for (i=0; i<thee->n; i++) {
            thee->pc[i] = i;
        }

        /*
         * Get column permutation vector pc[], according to pspec:
         *   pspec = 0: use the natural ordering
         *   pspec = 1: use minimum degree ordering on structure of A'*A
         *   pspec = 2: use minimum degree ordering on structure of A'+A
         *
         *   NOTE: pspec=2 makes most sense here, since our upper and
         *         lower triangles always have the same nonzero structure.
         */
#if 0
        pspec = 2;
#else
        pspec = 3; /* Burak debugs */
#endif
        get_perm_c(pspec, thee->A, thee->pc);


        /* post-multiply by this permutation matrix; produces "AC" */
        sp_preorder(refact, thee->A, thee->pc, thee->et, thee->AC);

    } else {
        /* this is a re-factorization */
        *refact = 'Y';
    }
    thee->statLU = 1;

    /* factorization of the permuted matrix "AC" */
    dgstrf(refact, thee->AC, 1.0, 0.0, relax, panel_size, thee->et,
        NULL, 0, thee->pr, thee->pc, thee->L, thee->U, &info);

    /* return: 1=success, 0=failure */
    if (info == 0) return 1;
    else           return 0;
}
#endif

/*
 * ***************************************************************************
 * Routine:  Zslu_solve
 *
 * Purpose:  Use sparse LU factors to back/forward solve a linear system.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
#if defined(_USE_SUPERLU_31) /* Use SuperLU 3.1 */
VPUBLIC int Zslu_solve(Zslu *thee, int key, double *b, double *x)
{
    SuperMatrix *BB;
    mem_usage_t mem_usage;
    double      rpg, rcond;
    int         i, info;
    superlu_options_t *oopts;

    VASSERT( thee != VNULL );
    VASSERT( thee->statLU );

    BB = (SuperMatrix*)thee->B;
    oopts = thee->opts;

    /* form the rhs */
    for (i=0; i<thee->m; i++) thee->rhsb[i] = b[i];

    /* solve the system with the existing factors */
    BB->ncol = thee->nrhs;  /* Set the number of right-hand sides */
    StatInit(thee->stat);
    if ( key == 0 ) {
        oopts->Trans = NOTRANS;
    } else {
        oopts->Trans = TRANS;
    }

#if USE_DGSSV
    oopts->Fact = DOFACT;
    dgssv(oopts, thee->A, thee->pc, thee->pr, thee->L, thee->U,
           thee->B, thee->stat, &info);
#else
    dgssvx(thee->opts, thee->A, thee->pc, thee->pr, thee->et, thee->equed,
           thee->R, thee->C, thee->L, thee->U,
           thee->work, thee->lwork, thee->B, thee->X, &rpg, &rcond,
           thee->ferr, thee->berr, &mem_usage, thee->stat, &info);
#endif

    printf("Triangular solve: dgssvx() returns info %d\n", info);
    if ( info == 0 || info == (thee->n)+1 ) {
        printf("No-op\n");
    } else if ( info > 0 && thee->lwork == -1 ) {
        printf("** Estimated memory: %d bytes\n", info - (thee->n));
    }
    if ( oopts->PrintStat ) StatPrint(thee->stat);
    StatFree(thee->stat);

    /* copy solution into x for the return */
#if USE_DGSSV
    for (i=0; i<thee->n; i++) x[i] = thee->rhsb[i];
#else
    for (i=0; i<thee->n; i++) x[i] = thee->rhsx[i];
#endif

    /* return: 1=success, 0=failure */
    if (info == 0) return 1;
    else           return 0;
}
#else /* Use SuperLU 2.0 */
VPUBLIC int Zslu_solve(Zslu *thee, int key, double *b, double *x)
{
    SuperMatrix B;
    double      *pb;
    int         i, info;
    char        trans[1];

    VASSERT( thee != VNULL );
    VASSERT( thee->statLU );

    /* create a malloc area for the rhs */
    pb = Vmem_malloc( thee->vmem, thee->m, sizeof(double) );

    /* create a supermatrix for the rhs; make a copy to preserve original */
    for (i=0; i<thee->m; i++) pb[i] = b[i];
    dCreate_Dense_Matrix(&B, thee->m, 1, pb, thee->m, DN, __D, GE);

    /* factor and solve the system */
    /*
     * dgssv(thee->A, thee->pc, thee->pr, thee->L, thee->U, &B, &info);
     */
    if ( key == 0 )
        *trans = 'N';
    else
        *trans = 'T';
    dgstrs(trans, thee->L, thee->U, thee->pr, thee->pc, &B, &info);

    /* copy solution into x for the return */
    for (i=0; i<thee->n; i++) x[i] = pb[i];

    /* destroy the supermatrix for the rhs */
    Destroy_SuperMatrix_Store(&B);  /* free B */

    /* destroy rhs malloc area */
    Vmem_free( thee->vmem, thee->m, sizeof(double), (void**)&pb );

    /* return: 1=success, 0=failure */
    if (info == 0) return 1;
    else           return 0;
}
#endif

/*
 * ***************************************************************************
 * Routine:  Zslu_memChk
 *
 * Purpose:  Print the exact current malloc usage.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Zslu_memChk(Zslu *thee)
{
    if (thee->iMadeVmem) Vmem_print(thee->vmem);
}

/*
 * ***************************************************************************
 * Routine:  Zslu_lnDet
 *
 * Purpose:  Calculate the log of the determinant of a SuperLU matrix.
 *
 * Notes:    Uses SLU factorization and will be very slow for large matrices.
 *
 * According to Sherry Li, author of SuperLU:
 *
 *   The diagonal blocks of both L and U are stored in the L matrix,
 *   which is returned from dgstrf().  The L matrix is a supernodal matrix,
 *   its structure is called SCformat in supermatrix.h.  This is also
 *   illustrated by a small 5x5 example in Section 2.3 of the Users' Guide,
 *   see Figures 2.1 and 2.3.   This example is in the code
 *   EXAMPLE/superlu.c.  Since L is unit-diagonal, so the ones are not
 *   stored. Instead, the diagonal stored in L is really the diagonal for U.
 *   Therefore, you only need to extract those diagonal elements.  One
 *   routine that you can hack to get the diagonal is
 *   dPrint_SuperNode_Matrix() in dutil.c.  Another tricky part is the sign
 *   of the determinant. Since I am doing the following factorization Pr*A*Pc
 *   = LU, i.e., both row and column permutations may be applied, they are
 *   called perm_r and perm_c in the code. Their determinants will be 1 or
 *   -1, but you need to find out the sign by going through these
 *   permutations.
 *
 * Author:   Nathan Baker (some restructuring by Michael Holst)
 * ***************************************************************************
 */
VPUBLIC double Zslu_lnDet(Zslu *thee)
{
    double lndet;
    SuperMatrix *L;
    SCformat *Astore;
    int i, j, k, c, d, nsup;
    double Lii, *dp;
    int *sup_to_col, *rowind, *rowind_colptr;

    VASSERT( thee != VNULL );
    VASSERT( thee->statLU );

    L = (SuperMatrix *)(thee->L);
    /* Stolen from dPrint_SuperNode_Matrix (SuperLU 2.0) */
    Vnm_print(1, "Zslu_lnDet:  Forming log determinant (assuming SPD!)...\n");
    /* n = L->ncol; */
    Astore = (SCformat *)(L->Store);
    dp = (double *) Astore->nzval;
    /* col_to_sup = Astore->col_to_sup; */
    sup_to_col = Astore->sup_to_col;
    rowind_colptr = Astore->rowind_colptr;
    rowind = Astore->rowind;
    lndet = 0;
    /* det = 1; */
    for (k = 0; k <= Astore->nsuper+1; ++k) {
        c = sup_to_col[k];
        nsup = sup_to_col[k+1] - c;
        for (j = c; j < c + nsup; ++j) {
            d = Astore->nzval_colptr[j];
            for (i = rowind_colptr[c]; i < rowind_colptr[c+1]; ++i) {
                if (rowind[i] == j) {
                    Lii = dp[d++];
                    lndet += log(VABS(Lii));
                } else d++;
            }
        }
    }
    Vnm_print(0, "Zslu_lnDet:  ln(det(A)) = %g\n", lndet);

    return lndet;
}

