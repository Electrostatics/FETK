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
 * rcsid="$Id: slu.c,v 1.14 2010/08/12 05:18:30 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     slu.c
 *
 * Purpose:  Class Slu: Wrapper class for a generic sparse direct solver.
 *           UMFPACK 5.2.0
 *
 * Notes:    This wrapper contains function calls to the UMFPACK Library,
 *           developed by Timothy A. Davis at University of Florida.
 *
 *           UMFPACK uses the AMD Library, developed by Timothy A. Davis,
 *           Patrick R. Amestoy, and Iain S. Duff.
 *
 *           Please see the UMFPACK and AMD subdirectories for more
 *           specific licensing and authorship information.
 *
 * Author:   Michael Holst and Stephen Bond (this wrapper only)
 * ***************************************************************************
 */

#include "slu_p.h"
#include <punc/vumfpack.h>

VEMBED(rcsid="$Id: slu.c,v 1.14 2010/08/12 05:18:30 fetk Exp $")

/*
 * ***************************************************************************
 * Class Slu: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_SLU)

#endif /* if !defined(VINLINE_SLU) */
/*
 * ***************************************************************************
 * Class Slu: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Slu_ctor
 *
 * Purpose:  The Slu constructor.
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC Slu* Slu_ctor(Vmem *vmem, int skey, int m, int n, int nnz,
    int *ia, int *ja, double *a)
{
    Slu* thee = VNULL;

    VDEBUGIO("Slu_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Slu) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Slu" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    /* dimensions */
    thee->m = m;
    thee->n = n;

    /* storage key */
    thee->skey = skey;

    /* pointer to factors */
    thee->work = VNULL;

    /* arrays */
    thee->a  = a;
    thee->ia = ia;
    thee->ja = ja;

    VDEBUGIO("..done.\n");

    /* return */
    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Slu_dtor
 *
 * Purpose:  The Slu destructor.
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Slu_dtor(Slu **thee)
{
    VASSERT( (*thee) != VNULL );
    if ((*thee) != VNULL) {

        /* destroy the factorization */
        if( (*thee)->statLU == 1 ) {
            umfpack_di_free_numeric( &((*thee)->work) );
            (*thee)->statLU = 0;
        }

        /* finally destroy this container */
        VDEBUGIO("Slu_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Slu), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;

    }
}

/*
 * ***************************************************************************
 * Routine:  Slu_factor
 *
 * Purpose:  Sparse LU factor the system.
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC int Slu_factor(Slu *thee)
{
    int status;
    int n = thee->n, m = thee->m;
    int *Ap = thee->ia, *Ai = thee->ja;
    double *Ax = thee->a;

    void *Symbolic, *Numeric;

    VASSERT( thee != VNULL );

    if( thee->statLU == 1 ) {
        umfpack_di_free_numeric( thee->work );
        thee->statLU = 0;
    }

    status = umfpack_di_symbolic(n, m, Ap, Ai, Ax, &Symbolic, VNULL, VNULL);
    if (UMFPACK_OK != status) {
        return 0;
    }
    status = umfpack_di_numeric(Ap, Ai, Ax, Symbolic, &Numeric, VNULL, VNULL);
    umfpack_di_free_symbolic(&Symbolic);
    if (UMFPACK_OK != status) {
        return 0;
    }

    thee->work = Numeric;
    thee->statLU = 1;

    return 1;
}

/*
 * ***************************************************************************
 * Routine:  Slu_solve
 *
 * Purpose:  Use sparse LU factors to back/forward solve a linear system.
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC int Slu_solve(Slu *thee, int key, double *b, double *x)
{
    int status;
    int n = thee->n, m = thee->m, skey = thee->skey;
    int *Ap = thee->ia, *Ai = thee->ja;
    double *Ax = thee->a;
    void *Numeric = thee->work;

    VASSERT( thee != VNULL );
    VASSERT( thee->statLU );

    /* solve the system with the existing factors */

    if( (key == 0 && skey == 1) || (key == 1 && skey == 0) ) {
        status = umfpack_di_solve(UMFPACK_A, Ap, Ai, Ax, x, b, Numeric,
                                  VNULL, VNULL);
    } else {
        status = umfpack_di_solve(UMFPACK_At, Ap, Ai, Ax, x, b, Numeric,
                                  VNULL, VNULL);
    }

    /* return: 1=success, 0=failure */
    if ( UMFPACK_OK == status ) {
        return 1;
    } else {
        return 0;
    }
}

/*
 * ***************************************************************************
 * Routine:  Slu_lnDet
 *
 * Purpose:  Calculate the log of the determinant of a factored matrix.
 *
 * Notes:    UMFPACK has a built-in routine to compute the determinant,
 *           which returns both the mantissa and the exponent separately.
 *           This avoids most overflow and underflow problems.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC double Slu_lnDet(Slu *thee)
{
    int status;
    double Mx, Ex, lndet;
    void *Numeric = thee->work;

    VASSERT( thee != VNULL );
    VASSERT( thee->statLU );

    /* Determinant = Mx * 10^Ex */
    status = umfpack_di_get_determinant( &Mx, &Ex, Numeric, VNULL );

    /* LOG(DET) = LOG(Mantissa) + Exponent*LOG(10) */
    lndet = VLOG(VABS(Mx)) + Ex*VLOG(10);

    if (UMFPACK_OK == status) {
        Vnm_print(0, "Slu_lnDet:  ln(det(A)) = %g\n", lndet);
        return lndet;
    } else {
        Vnm_print(0, "Slu_lnDet:  Failed!  Returning 1.0\n");
        return 1.0;
    }
}
