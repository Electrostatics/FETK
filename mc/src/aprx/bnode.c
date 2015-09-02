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
 * rcsid="$Id: bnode.c,v 1.15 2010/08/12 05:18:16 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     bnode.c
 *
 * Purpose:  Class Bnode: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "bnode_p.h"

VEMBED(rcsid="$Id: bnode.c,v 1.15 2010/08/12 05:18:16 fetk Exp $")

/*
 * ***************************************************************************
 * Class Bnode: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_BAM)

/*
 * ***************************************************************************
 * Routine:  Bnode_numB
 *
 * Purpose:  Return the number of blocks.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bnode_numB(Bnode *thee)
{
    return thee->numB;
}

#endif /* if !defined(VINLINE_BAM) */
/*
 * ***************************************************************************
 * Class Bnode: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Bnode_ctor
 *
 * Purpose:  The Block node constructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Bnode* Bnode_ctor(Vmem *vmem, int pnumB, int pnumR[MAXV])
{
    int i;
    Bnode *thee = VNULL;

    VDEBUGIO("Bnode_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Bnode) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Bnode" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    VDEBUGIO("..done.\n");

    thee->numB   = pnumB;
    for (i=0; i<thee->numB; i++) {
        thee->ND[i] = Node_ctor(vmem, pnumR[i]);
    }

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Bnode_dtor
 *
 * Purpose:  The Block node destructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bnode_dtor(Bnode **thee)
{
    int i;

    /* VASSERT( (*thee) != VNULL ); */
    if ((*thee) != VNULL) {

        for (i=0; i<(*thee)->numB; i++) {
            Node_dtor( (&(*thee)->ND[i]) );
        }

        VDEBUGIO("Bnode_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Bnode), (void**)thee );
        VDEBUGIO("..done.\n"); 

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  Bnode_numRT
 *
 * Purpose:  Return the total number of nodes.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bnode_numRT(Bnode *thee)
{
    int i, numRT;

    numRT = 0;
    for (i=0; i<thee->numB; i++) {
        numRT += Bnode_numR(thee,i);
    }
    
    return numRT;
}

/*
 * ***************************************************************************
 * Routine:  Bnode_numR
 *
 * Purpose:  Return the number of nodes in a block.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bnode_numR(Bnode *thee, int i)
{
    return Node_numR(thee->ND[i]);
}

/*
 * ***************************************************************************
 * Routine:  Bnode_nodes
 *
 * Purpose:  Return the nodes in one block.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Node *Bnode_nodes(Bnode *thee, int i)
{
    return thee->ND[i];
}

/*
 * ***************************************************************************
 * Routine:  Bnode_data
 *
 * Purpose:  Return the actual nodes in one block.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC aNode *Bnode_data(Bnode *thee, int i)
{
    return Node_data(thee->ND[i]);
}

/*
 * ***************************************************************************
 * Routine:  Bnode_memChk
 *
 * Purpose:  Print the exact current malloc usage.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bnode_memChk(Bnode *thee)
{
    if (thee->iMadeVmem) Vmem_print(thee->vmem);
}

