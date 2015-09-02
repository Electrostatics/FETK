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
 * rcsid="$Id: conform_mesh.c,v 1.4 2010/08/12 05:18:17 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     conform_mesh.c
 *
 * Purpose:  Here we have routines that may be used to pack, send and 
 *           examine buffers to communicate with neighboring processors to 
 *           determine whether the locally-refined meshes are conforming, 
 *           and if not, to set up a conforming mesh.
 *
 * Author:   Daniel Reynolds & Michael Holst
 * ***************************************************************************
 */

#include "conform_mesh.h"

VEMBED(rcsid="")



/*
 * ***************************************************************************
 * Routine:  packBuffers
 *
 * Purpose:  Fill in buffers of inter-processor face information to share 
 *           with neighbor processors in generation of a globally-conforming
 *           mesh.
 *
 * Author:   Daniel Reynolds and Michael Holst
 * ***************************************************************************
 */
void packBuffers(int **send_buffers, void **sbuff_simplices, 
		 int *nbor_list, int *buff_len, int *num_neighbors)
{

  /* All arguments are designed for output.  Their descriptions are:
       send_buffers - array of buffers containing boundary face 
                      information for this proc.
       sbuff_simplices - array of simplex pointers corresp. to 
                      boundary faces in send buffers
       nbor_list - list of neighbor IDs adjacent to each send buffer 
                      (indices align with first index in send_buffers)
       buff_len - length of each send buffer (indices also align 
                      with first index in send_buffers)
       num_neighbors - integer number of neighbors adjacent to this 
                      processor (total number of send buffers) */

  /* initialize num_neighbors */
  *num_neighbors = 0;

  /*** allocate nbor_list as a vector ***/
  

  /*** allocate buff_len as a vector ***/
  

  /* temporary variables */
  int Nbor, test, buffID, i, j;


  /* iterate over all simplices on this processor */
  /*** for () ***/
  {
    
    /* iterate over all potential boundary faces on this simplex */
    for (i=0; i<4; i++) {

      /* only do something if this simplex/face is filled in 
	 (i.e. it exists on an inter-processor boundary) */
      if (fPtr[i] != NULL) {

	/* get neighbor ID for this face */
	Nbor = (fPtr[i]->d).gID;
	
	/* check whether this neighbor is in the neighbor list */
	test = 0;
	for (j=0; j<num_neighbors; j++) {
	  if (nbor_list[j] == Nbor) {
	    test = 1;
	    buffID = j;
	    break;
	  } /* end if (nbor_list[j] == Nbor) */
	} /* end loop over j */

	/* if there are no buffers yet allocated for this 
	   neighbor, set them up using the first available slot. */
	if (test == 0) {
	  /*** allocate send_buffers[num_neighbors] as an integer vector 
	       (will eventually be of length 2*buff_len[num_neighbors], 
	        though we do not know the eventual value of that buffer 
	        length just yet) ***/


	  /*** allocate sbuff_simplices[num_neighbors] as an integer vector 
	       (will eventually be of length buff_len[num_neighbors], 
	        though we do not know the eventual value of that buffer 
	        length just yet) ***/


	  /* set this neighbor into neighbor list */
	  nbor_list[num_neighbors] = Nbor;

	  /* initialize buffer length to zero */
	  buff_len[num_neighbors] = 0;

	  /* set buffID, and increment the total number of neighbors */
	  buffID = num_neighbors;
	  num_neighbors++;
	}
	
	/* set uid and rhist into send buffer */
	send_buffers[buffID][2*buff_len[buffID]] = (fPtr->g).uid;
	send_buffers[buffID][2*buff_len[buffID]+1] = (fPtr->d).rhist;

	/* set simplex pointer into simplex buffer */
	sbuff_simplices[buffID][buff_len[buffID]] = (fPtr->d).sPtr;

	/* increment buffer length */
	buff_len[buffID] += 1;

      } /* end if (fPtr[i] != NULL) */
    } /* end loop over i */
  } /* end loop over all simplices on processor */

  /* sort each send buffer and simplex buffer first according to 
     uid and second according to rhist */
  for (i=0; i<num_neighbors; i++) {

    /* shortcuts to appropriate buffers */
    int *buff = send_buffers[i];
    int *simp = sbuff_simplices[i];

    /*** sort buff (first according to uid, second according to rhist;
	 reorder simp with same ordering as buff so that corresponding 
	 buffers and simplices have the same index ***/


  }

  /* At this point we should have the following variables ready to go:
     - int num_neighbors, containing the total number of processors 
       adjacent to this processor.
     - int *send_buffers[num_neighbors], each of length 2*buff_len[i], 
       containing the (uid,rhist) integer pair for every boundary face
       owned by this processor that is adjacent to a given processor 
       neighbor.
     - void *sbuff_simplices[num_neighbors], each of length buff_len[i],
       containing pointers to the simplices on this processor that own 
       each of the relevant faces in the corresponding send_buffer.
     - int buff_len[num_neighbors] contains the number of faces on this 
       processor contributing information to send_buffers and 
       sbuff_simplices.
     - int nbor_list[num_neighbors] contains the ID corresponding to the 
       processor neighbor associated with a given send_buffer.
  */

  /* return successfully */
  return;

}



/*
 * ***************************************************************************
 * Routine:  exchangeBuffers
 *
 * Purpose:  Exchanges buffers of inter-processor face information with 
 *           neighbor processors in generation of a globally-conforming mesh.  
 *           This routine uses asynchronous MPI communication to allow for 
 *           overlapping communication with all neighbor processors.
 *
 * Author:   Daniel Reynolds and Michael Holst
 * ***************************************************************************
 */
void exchangeBuffers(int **send_buffers, int *nbor_list, int *buff_len, 
		     int num_neighbors, int *nbor_bufflen, int **recv_buffers)
{

  /* The following are input arguments:
       send_buffers - array of buffers containing boundary face 
                      information for this proc.
       nbor_list - list of neighbor IDs adjacent to each send buffer 
                      (indices align with first index in send_buffers)
       buff_len - length of each send buffer (indices align with 
                      first index in send_buffers)
       num_neighbors - integer number of neighbors adjacent to this 
                      processor (total number of send buffers)

     The remaining two arguments are for output:
       nbor_bufflen - length of each recv buffer for neighbor 
                      information
       recv_buffers - array of buffers containing boundary face 
                      information for neighbor procs */

  /* local variables */
  int i, j;

  /*** allocate storage for neighbor buffer sizes: set nbor_bufflen 
       to be an integer array of length num_neighbors ***/
  
  /*** allocate storage for neighbor buffers: set recv_buffers to 
       be a (buffer vector) array of length num_neighbors ***/

  /* allocate MPI send and receive request handles for each neighbor */
  MPI_Request *recv_handle[num_neighbors];
  MPI_Request *send_handle[num_neighbors];

  /* open receive buffers for each neighbor's send buffer size */
  /*   NOTE: the message tag used here equals the sending processor tag, 
       since each processor will be receiving numerous messages, this 
       way they will be unique on the receiving end. 
       Also, I use the default MPI communicator here, which can be 
       replaced by whatever convention is typically used in FETk. */
  for (i=0; i<num_neighbors; i++) {
    if (MPI_Irecv(&nbor_bufflen[i], 1, MPI_INT, nbor_list[i], 
		  nbor_list[i], MPI_COMM_WORLD, recv_handle[i]) != 0) {
      printf("exchangeBuffers MPI_Irecv error (nbor_bufflen %i)!\n",i);
      return;
    }
  } /* end loop over i */

  /* send buffer lengths to neighbors, using my processor ID as the 
     message tag. */
  int myID;   MPI_Comm_rank(MPI_COMM_WORLD, &myID);
  for (i=0; i<num_neighbors; i++) {
    if (MPI_Isend(buff_len[i], 1, MPI_INT, nbor_list[i], 
		  myID, MPI_COMM_WORLD, send_handle[i]) != 0) {
      printf("exchangeBuffers MPI_Isend error (buff_len %i)!\n",i);
      return;
    }
  } /* end loop over i */

  /* wait to ensure that all messages were sent and received successfully */
  MPI_Status status;
  for (i=0; i<num_neighbors; i++) {
    if (MPI_Wait(&recv_handle[i], &status) != 0) {
      printf("exchangeBuffers MPI_Wait error (nbor_bufflen %i recv)!\n",i);
      return;
    }
    if (MPI_Wait(&send_handle[i], &status) != 0) {
      printf("exchangeBuffers MPI_Wait error (buff_len %i send)!\n",i);
      return;
    }
  } /* end loop over i */


  /* allocate receive buffers for all neighbors */
  for (i=0; i<num_neighbors; i++) {

    /*** allocate recv_buffers[i] to be an integer array of length
	 2*nbor_bufflen[i] ***/
    
  } /* end loop over i */


  /* open receive buffers for neighbor information */
  /*   NOTE: the message tag used here again equals the sending processor 
       tag, since each processor will be receiving numerous messages, 
       this way they will be unique on the receiving end. 
       Also, I use the default MPI communicator here, which should be 
       replaced by whatever convention is typically used in FETk. 
       Lastly, the buffer length is bufflen*2, since we receive two 
       values for each inter-processor face */
  for (i=0; i<num_neighbors; i++) {
    if (MPI_Irecv(recv_buffers[i], 2*nbor_bufflen[i], MPI_INT, nbor_list[i], 
		  nbor_list[i], MPI_COMM_WORLD, recv_handle[i]) != 0) {
      printf("exchangeBuffers MPI_Irecv error (recv_buffers %i)!\n",i);
      return;
    }
  } /* end loop over i */

  /* send face buffers to neighbors */
  for (i=0; i<num_neighbors; i++) {
    if (MPI_Isend(send_buffers[i], 2*buff_len[i], MPI_INT, nbor_list[i], 
		  myID, MPI_COMM_WORLD, send_handle[i]) != 0) {
      printf("exchangeBuffers MPI_Isend error (send_buffers %i)!\n",i);
      return;
    }
  } /* end loop over i */

  /* wait to ensure that all messages were sent and received successfully */
  for (i=0; i<num_neighbors; i++) {
    if (MPI_Wait(&recv_handle[i], &status) != 0) {
      printf("exchangeBuffers MPI_Wait error (recv_buffers %i recv)!\n",i);
      return;
    }
    if (MPI_Wait(&send_handle[i], &status) != 0) {
      printf("exchangeBuffers MPI_Wait error (send_buffers %i send)!\n",i);
      return;
    }
  } /* end loop over i */

  /* At this point we should have the following variables ready to go:
     - int nbor_bufflen[num_neighbors], containing the number of 
       inter-processor faces on each neighbor that are adjacent to 
       my processor.
     - int *recv_buffers[num_neighbors], each of length 
       2*nbor_bufflen[i], containing the (uid,rhist) integer pair for 
       every boundary face owned by the neighbor that is adjacent to 
       this processor.
  */

  /* return successfully */
  return;
}



/*
 * ***************************************************************************
 * Routine:  examineBuffers
 *
 * Purpose:  Examines buffers of inter-processor face information to mark 
 *           local processor simplices for refinement in generation of a 
 *           globally-conforming mesh.
 *
 * Author:   Daniel Reynolds and Michael Holst
 * ***************************************************************************
 */
void examineBuffers(int **send_buffers, void **sbuff_simplices, 
		    int *nbor_list, int *buff_len, int num_neighbors, 
		    int *nbor_bufflen, int **recv_buffers)
{
  /* The following are input arguments:
       send_buffers - array of buffers containing boundary face 
                      information for this proc.
       sbuff_simplices - array of buffers, each of length buff_len[i],
                      containing pointers to the simplices on this 
		      processor that own each of the relevant faces 
		      in the corresponding send_buffer.
       nbor_list - list of neighbor IDs adjacent to each send buffer 
                      (indices align with first index in send_buffers)
       buff_len - length of each send buffer (indices also align with 
                      first index in send_buffers)
       num_neighbors - integer number of neighbors adjacent to this 
                      processor (total number of send/recv buffers)
       nbor_bufflen - length of each recv buffer for neighbor 
                      information
       recv_buffers - array of buffers containing boundary face 
                      information for neighbor procs  */


  /* local variables */
  int i, j, m_loc, y_loc, m_uid, y_uid, m_rhist, y_rhist;

  /* iterate over processor neighbors */
  for (i=0; i<num_neighbors; i++) {

    /* initialize local variables for this neighbor */
    m_loc = 0;    /* pointer for location in send_buffers array (mine)  */
    y_loc = 0;    /* pointer for location in recv_buffers array (yours) */

    /* iterate over total possible combined face length */
    for (j=0; j<(buff_len[i]+nbor_bufflen[i]); j++) {

      /* initialize local variables for this face pair */
      m_uid = send_buffers[i][2*m_loc];     /* my uid (ID of coarse face)   */
      y_uid = recv_buffers[i][2*y_loc];     /* your uid (ID of coarse face) */
      m_rhist = send_buffers[i][2*m_loc+1]; /* my rhist (refinement ID)     */
      y_rhist = recv_buffers[i][2*y_loc+1]; /* your rhist (refinement ID)   */

      /* Only need to mark my own simplices for refinement if the neighbor 
	 face is more refined than I am */
      /* NOTE: IF LEFT/RIGHT REFINEMENT FOR CHILDREN IS REVERSED ON THE 
	 OTHER SIDE OF THE INTERFACE, WE MAY NEED TO DO SOME BIT 
	 MANIPULATION ON Y_RHIST TO REVERSE THE REFINEMENT HISTORY */
      if ((m_uid > y_uid) || (m_uid == y_uid  && m_rhist > y_rhist)){

	/*** Mark sbuff_simplices[i][m_loc] for refinement ***/

	/* proceed along neighbor's buffer to next face */
	y_loc += 1;

      }

      /* If I am more refined than neighbor, they'll take care of it, 
	 so proceed along my buffer to next face */
      else if ((m_uid < y_uid) || (m_uid == y_uid && m_rhist < y_rhist))
	m_loc += 1;

      /* If we're at the same refinement level, proceed along both 
	 buffers to next face */
      else {
	m_loc += 1;
	y_loc += 1;
      }  /* end if */

      /* see if we've reached the end of the buffers */
      /* NOTE: MAYBE WE SHOULD DO SOME CHECKS HERE TO ENSURE THAT 
	 NOTHING MESSY HAPPENED ALONG THE WAY?? */
      if ( (m_loc >= buff_len[i]) && (y_loc >= nbor_bufflen[i]) )
	break;

    }  /* end for loop over faces (j loop) */
  } /* end for loop over processor neighbors (i loop) */


  /* At this point any local simplices requiring refinement to match the 
     neighbor's interface mesh should have been marked appropriately.  
     As we have not changed any of the buffer information, this 
     information could be reused in the solver since that will require 
     communication of interface VALUES that can occur in the same format 
     as done here.
  */

  /* return successfully */
  return;
}

