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
 * rcsid="$Id: node.c,v 1.4 2010/08/12 05:18:18 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     node.c
 *
 * Purpose:  Class Node: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "node_p.h"

VEMBED(rcsid="$Id: node.c,v 1.4 2010/08/12 05:18:18 fetk Exp $")

/*
 * ***************************************************************************
 * Class Node: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_BAM)

/*
 * ***************************************************************************
 * Routine:  Node_numR
 *
 * Purpose:  Return the number of nodes.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Node_numR(Node *thee)
{
    return thee->numR;
}

/*
 * ***************************************************************************
 * Routine:  Node_data
 *
 * Purpose:  Return a pointer to the node data.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC aNode* Node_data(Node *thee)
{
    return thee->data;
}

#endif /* if !defined(VINLINE_BAM) */
/*
 * ***************************************************************************
 * Class Node: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Node_ctor
 *
 * Purpose:  The node constructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Node* Node_ctor(Vmem *vmem, int pnumR)
{
    Node *thee = VNULL;

    VDEBUGIO("Node_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Node) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Node" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    VDEBUGIO("..done.\n");

    thee->numR = pnumR;
    thee->data = Vmem_malloc( thee->vmem, thee->numR, sizeof(aNode) );

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Node_dtor
 *
 * Purpose:  The node destructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Node_dtor(Node **thee)
{
    /* VASSERT( (*thee) != VNULL ); */
    if ((*thee) != VNULL) {

        Vmem_free( (*thee)->vmem, (*thee)->numR, sizeof(aNode),
            (void**)&((*thee)->data) );

        VDEBUGIO("Node_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Node), (void**)thee );
        VDEBUGIO("..done.\n"); 

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  Node_memChk
 *
 * Purpose:  Print the exact current malloc usage.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Node_memChk(Node *thee)
{
    if (thee->iMadeVmem) Vmem_print(thee->vmem);
}

