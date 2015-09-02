### ##########################################################################
### PUNC = < Portable Understructure for Numerical Computing >
### Copyright (C) 1994-- Michael Holst
### 
### This library is free software; you can redistribute it and/or
### modify it under the terms of the GNU Lesser General Public
### License as published by the Free Software Foundation; either
### version 2.1 of the License, or (at your option) any later version.
### 
### This library is distributed in the hope that it will be useful,
### but WITHOUT ANY WARRANTY; without even the implied warranty of
### MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
### Lesser General Public License for more details.
### 
### You should have received a copy of the GNU Lesser General Public
### License along with this library; if not, write to the Free Software
### Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
### 
### rcsid="$Id: Makefile.am,v 1.4 2010/08/12 05:52:29 fetk Exp $"
### ##########################################################################

## ###########################################################################
## File:    Makefile.am
##
## Purpose: Automatically generate Makefile.in for autoconf using automake.
##
## Notes:   The final makefile produced by autoconf will use the following:
##
##     COMPILE = $(CC) $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
##     LINK = $(CC) $(CFLAGS) $(LDFLAGS) -o $@
##
## Author:  Michael Holst and Stephen Bond
## ###########################################################################

CPPINC = -I@srcdir@ -I@srcdir@/punc \
         -I${top_srcdir}/src/amd -I${top_srcdir}/src/amd/punc

# Preprocessing for UMFPACK Library
umfpack_gn_global.c:
	$(CPP) ${CPPINC} @srcdir@/umfpack_global.c > umfpack_gn_global.c
umfpack_gn_timer.c:
	$(CPP) ${CPPINC} @srcdir@/umfpack_timer.c > umfpack_gn_timer.c
umfpack_gn_tictoc.c:
	$(CPP) ${CPPINC} @srcdir@/umfpack_tictoc.c > umfpack_gn_tictoc.c
umf_i_analyze.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_analyze.c > umf_i_analyze.c
umf_i_apply_order.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_apply_order.c > umf_i_apply_order.c
umf_i_colamd.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_colamd.c > umf_i_colamd.c
umf_i_free.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_free.c > umf_i_free.c
umf_i_fsize.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_fsize.c > umf_i_fsize.c
umf_i_is_permutation.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_is_permutation.c > umf_i_is_permutation.c
umf_i_malloc.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_malloc.c > umf_i_malloc.c
umf_i_realloc.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_realloc.c > umf_i_realloc.c
umf_i_report_perm.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_report_perm.c > umf_i_report_perm.c
umf_i_singletons.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_singletons.c > umf_i_singletons.c
umf_l_analyze.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_analyze.c > umf_l_analyze.c
umf_l_apply_order.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_apply_order.c > umf_l_apply_order.c
umf_l_colamd.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_colamd.c > umf_l_colamd.c
umf_l_free.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_free.c > umf_l_free.c
umf_l_fsize.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_fsize.c > umf_l_fsize.c
umf_l_is_permutation.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_is_permutation.c > umf_l_is_permutation.c
umf_l_malloc.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_malloc.c > umf_l_malloc.c
umf_l_realloc.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_realloc.c > umf_l_realloc.c
umf_l_report_perm.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_report_perm.c > umf_l_report_perm.c
umf_l_singletons.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_singletons.c > umf_l_singletons.c
umf_di_lhsolve.c:
	$(CPP) ${CPPINC} -DDINT -DCONJUGATE_SOLVE @srcdir@/umf_ltsolve.c > umf_di_lhsolve.c
umf_di_uhsolve.c:
	$(CPP) ${CPPINC} -DDINT -DCONJUGATE_SOLVE @srcdir@/umf_utsolve.c > umf_di_uhsolve.c
umf_di_triplet_map_nox.c:
	$(CPP) ${CPPINC} -DDINT -DDO_MAP @srcdir@/umf_triplet.c > umf_di_triplet_map_nox.c
umf_di_triplet_nomap_x.c:
	$(CPP) ${CPPINC} -DDINT -DDO_VALUES @srcdir@/umf_triplet.c > umf_di_triplet_nomap_x.c
umf_di_triplet_nomap_nox.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_triplet.c > umf_di_triplet_nomap_nox.c
umf_di_triplet_map_x.c:
	$(CPP) ${CPPINC} -DDINT -DDO_MAP -DDO_VALUES @srcdir@/umf_triplet.c > umf_di_triplet_map_x.c
umf_di_assemble_fixq.c:
	$(CPP) ${CPPINC} -DDINT -DFIXQ @srcdir@/umf_assemble.c > umf_di_assemble_fixq.c
umf_di_store_lu_drop.c:
	$(CPP) ${CPPINC} -DDINT -DDROP @srcdir@/umf_store_lu.c > umf_di_store_lu_drop.c
umf_di_assemble.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_assemble.c > umf_di_assemble.c
umf_di_blas3_update.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_blas3_update.c > umf_di_blas3_update.c
umf_di_build_tuples.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_build_tuples.c > umf_di_build_tuples.c
umf_di_create_element.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_create_element.c > umf_di_create_element.c
umf_di_dump.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_dump.c > umf_di_dump.c
umf_di_extend_front.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_extend_front.c > umf_di_extend_front.c
umf_di_garbage_collection.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_garbage_collection.c > umf_di_garbage_collection.c
umf_di_get_memory.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_get_memory.c > umf_di_get_memory.c
umf_di_init_front.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_init_front.c > umf_di_init_front.c
umf_di_kernel.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_kernel.c > umf_di_kernel.c
umf_di_kernel_init.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_kernel_init.c > umf_di_kernel_init.c
umf_di_kernel_wrapup.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_kernel_wrapup.c > umf_di_kernel_wrapup.c
umf_di_local_search.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_local_search.c > umf_di_local_search.c
umf_di_lsolve.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_lsolve.c > umf_di_lsolve.c
umf_di_ltsolve.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_ltsolve.c > umf_di_ltsolve.c
umf_di_mem_alloc_element.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_mem_alloc_element.c > umf_di_mem_alloc_element.c
umf_di_mem_alloc_head_block.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_mem_alloc_head_block.c > umf_di_mem_alloc_head_block.c
umf_di_mem_alloc_tail_block.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_mem_alloc_tail_block.c > umf_di_mem_alloc_tail_block.c
umf_di_mem_free_tail_block.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_mem_free_tail_block.c > umf_di_mem_free_tail_block.c
umf_di_mem_init_memoryspace.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_mem_init_memoryspace.c > umf_di_mem_init_memoryspace.c
umf_di_report_vector.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_report_vector.c > umf_di_report_vector.c
umf_di_row_search.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_row_search.c > umf_di_row_search.c
umf_di_scale_column.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_scale_column.c > umf_di_scale_column.c
umf_di_set_stats.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_set_stats.c > umf_di_set_stats.c
umf_di_solve.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_solve.c > umf_di_solve.c
umf_di_symbolic_usage.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_symbolic_usage.c > umf_di_symbolic_usage.c
umf_di_transpose.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_transpose.c > umf_di_transpose.c
umf_di_tuple_lengths.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_tuple_lengths.c > umf_di_tuple_lengths.c
umf_di_usolve.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_usolve.c > umf_di_usolve.c
umf_di_utsolve.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_utsolve.c > umf_di_utsolve.c
umf_di_valid_numeric.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_valid_numeric.c > umf_di_valid_numeric.c
umf_di_valid_symbolic.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_valid_symbolic.c > umf_di_valid_symbolic.c
umf_di_grow_front.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_grow_front.c > umf_di_grow_front.c
umf_di_start_front.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_start_front.c > umf_di_start_front.c
umf_di_2by2.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_2by2.c > umf_di_2by2.c
umf_di_store_lu.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_store_lu.c > umf_di_store_lu.c
umf_di_scale.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umf_scale.c > umf_di_scale.c
umfpack_di_wsolve.c:
	$(CPP) ${CPPINC} -DDINT -DWSOLVE @srcdir@/umfpack_solve.c > umfpack_di_wsolve.c
umfpack_di_col_to_triplet.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_col_to_triplet.c > umfpack_di_col_to_triplet.c
umfpack_di_defaults.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_defaults.c > umfpack_di_defaults.c
umfpack_di_free_numeric.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_free_numeric.c > umfpack_di_free_numeric.c
umfpack_di_free_symbolic.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_free_symbolic.c > umfpack_di_free_symbolic.c
umfpack_di_get_numeric.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_get_numeric.c > umfpack_di_get_numeric.c
umfpack_di_get_lunz.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_get_lunz.c > umfpack_di_get_lunz.c
umfpack_di_get_symbolic.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_get_symbolic.c > umfpack_di_get_symbolic.c
umfpack_di_get_determinant.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_get_determinant.c > umfpack_di_get_determinant.c
umfpack_di_numeric.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_numeric.c > umfpack_di_numeric.c
umfpack_di_qsymbolic.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_qsymbolic.c > umfpack_di_qsymbolic.c
umfpack_di_report_control.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_report_control.c > umfpack_di_report_control.c
umfpack_di_report_info.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_report_info.c > umfpack_di_report_info.c
umfpack_di_report_matrix.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_report_matrix.c > umfpack_di_report_matrix.c
umfpack_di_report_numeric.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_report_numeric.c > umfpack_di_report_numeric.c
umfpack_di_report_perm.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_report_perm.c > umfpack_di_report_perm.c
umfpack_di_report_status.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_report_status.c > umfpack_di_report_status.c
umfpack_di_report_symbolic.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_report_symbolic.c > umfpack_di_report_symbolic.c
umfpack_di_report_triplet.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_report_triplet.c > umfpack_di_report_triplet.c
umfpack_di_report_vector.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_report_vector.c > umfpack_di_report_vector.c
umfpack_di_solve.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_solve.c > umfpack_di_solve.c
umfpack_di_symbolic.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_symbolic.c > umfpack_di_symbolic.c
umfpack_di_transpose.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_transpose.c > umfpack_di_transpose.c
umfpack_di_triplet_to_col.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_triplet_to_col.c > umfpack_di_triplet_to_col.c
umfpack_di_scale.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_scale.c > umfpack_di_scale.c
umfpack_di_load_numeric.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_load_numeric.c > umfpack_di_load_numeric.c
umfpack_di_save_numeric.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_save_numeric.c > umfpack_di_save_numeric.c
umfpack_di_load_symbolic.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_load_symbolic.c > umfpack_di_load_symbolic.c
umfpack_di_save_symbolic.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/umfpack_save_symbolic.c > umfpack_di_save_symbolic.c
umf_dl_lhsolve.c:
	$(CPP) ${CPPINC} -DDLONG -DCONJUGATE_SOLVE @srcdir@/umf_ltsolve.c > umf_dl_lhsolve.c
umf_dl_uhsolve.c:
	$(CPP) ${CPPINC} -DDLONG -DCONJUGATE_SOLVE @srcdir@/umf_utsolve.c > umf_dl_uhsolve.c
umf_dl_triplet_map_nox.c:
	$(CPP) ${CPPINC} -DDLONG -DDO_MAP @srcdir@/umf_triplet.c > umf_dl_triplet_map_nox.c
umf_dl_triplet_nomap_x.c:
	$(CPP) ${CPPINC} -DDLONG -DDO_VALUES @srcdir@/umf_triplet.c > umf_dl_triplet_nomap_x.c
umf_dl_triplet_nomap_nox.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_triplet.c > umf_dl_triplet_nomap_nox.c
umf_dl_triplet_map_x.c:
	$(CPP) ${CPPINC} -DDLONG -DDO_MAP -DDO_VALUES @srcdir@/umf_triplet.c > umf_dl_triplet_map_x.c
umf_dl_assemble_fixq.c:
	$(CPP) ${CPPINC} -DDLONG -DFIXQ @srcdir@/umf_assemble.c > umf_dl_assemble_fixq.c
umf_dl_store_lu_drop.c:
	$(CPP) ${CPPINC} -DDLONG -DDROP @srcdir@/umf_store_lu.c > umf_dl_store_lu_drop.c
umf_dl_assemble.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_assemble.c > umf_dl_assemble.c
umf_dl_blas3_update.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_blas3_update.c > umf_dl_blas3_update.c
umf_dl_build_tuples.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_build_tuples.c > umf_dl_build_tuples.c
umf_dl_create_element.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_create_element.c > umf_dl_create_element.c
umf_dl_dump.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_dump.c > umf_dl_dump.c
umf_dl_extend_front.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_extend_front.c > umf_dl_extend_front.c
umf_dl_garbage_collection.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_garbage_collection.c > umf_dl_garbage_collection.c
umf_dl_get_memory.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_get_memory.c > umf_dl_get_memory.c
umf_dl_init_front.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_init_front.c > umf_dl_init_front.c
umf_dl_kernel.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_kernel.c > umf_dl_kernel.c
umf_dl_kernel_init.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_kernel_init.c > umf_dl_kernel_init.c
umf_dl_kernel_wrapup.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_kernel_wrapup.c > umf_dl_kernel_wrapup.c
umf_dl_local_search.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_local_search.c > umf_dl_local_search.c
umf_dl_lsolve.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_lsolve.c > umf_dl_lsolve.c
umf_dl_ltsolve.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_ltsolve.c > umf_dl_ltsolve.c
umf_dl_mem_alloc_element.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_mem_alloc_element.c > umf_dl_mem_alloc_element.c
umf_dl_mem_alloc_head_block.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_mem_alloc_head_block.c > umf_dl_mem_alloc_head_block.c
umf_dl_mem_alloc_tail_block.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_mem_alloc_tail_block.c > umf_dl_mem_alloc_tail_block.c
umf_dl_mem_free_tail_block.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_mem_free_tail_block.c > umf_dl_mem_free_tail_block.c
umf_dl_mem_init_memoryspace.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_mem_init_memoryspace.c > umf_dl_mem_init_memoryspace.c
umf_dl_report_vector.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_report_vector.c > umf_dl_report_vector.c
umf_dl_row_search.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_row_search.c > umf_dl_row_search.c
umf_dl_scale_column.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_scale_column.c > umf_dl_scale_column.c
umf_dl_set_stats.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_set_stats.c > umf_dl_set_stats.c
umf_dl_solve.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_solve.c > umf_dl_solve.c
umf_dl_symbolic_usage.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_symbolic_usage.c > umf_dl_symbolic_usage.c
umf_dl_transpose.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_transpose.c > umf_dl_transpose.c
umf_dl_tuple_lengths.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_tuple_lengths.c > umf_dl_tuple_lengths.c
umf_dl_usolve.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_usolve.c > umf_dl_usolve.c
umf_dl_utsolve.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_utsolve.c > umf_dl_utsolve.c
umf_dl_valid_numeric.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_valid_numeric.c > umf_dl_valid_numeric.c
umf_dl_valid_symbolic.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_valid_symbolic.c > umf_dl_valid_symbolic.c
umf_dl_grow_front.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_grow_front.c > umf_dl_grow_front.c
umf_dl_start_front.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_start_front.c > umf_dl_start_front.c
umf_dl_2by2.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_2by2.c > umf_dl_2by2.c
umf_dl_store_lu.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_store_lu.c > umf_dl_store_lu.c
umf_dl_scale.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umf_scale.c > umf_dl_scale.c
umfpack_dl_wsolve.c:
	$(CPP) ${CPPINC} -DDLONG -DWSOLVE @srcdir@/umfpack_solve.c > umfpack_dl_wsolve.c
umfpack_dl_col_to_triplet.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_col_to_triplet.c > umfpack_dl_col_to_triplet.c
umfpack_dl_defaults.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_defaults.c > umfpack_dl_defaults.c
umfpack_dl_free_numeric.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_free_numeric.c > umfpack_dl_free_numeric.c
umfpack_dl_free_symbolic.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_free_symbolic.c > umfpack_dl_free_symbolic.c
umfpack_dl_get_numeric.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_get_numeric.c > umfpack_dl_get_numeric.c
umfpack_dl_get_lunz.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_get_lunz.c > umfpack_dl_get_lunz.c
umfpack_dl_get_symbolic.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_get_symbolic.c > umfpack_dl_get_symbolic.c
umfpack_dl_get_determinant.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_get_determinant.c > umfpack_dl_get_determinant.c
umfpack_dl_numeric.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_numeric.c > umfpack_dl_numeric.c
umfpack_dl_qsymbolic.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_qsymbolic.c > umfpack_dl_qsymbolic.c
umfpack_dl_report_control.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_report_control.c > umfpack_dl_report_control.c
umfpack_dl_report_info.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_report_info.c > umfpack_dl_report_info.c
umfpack_dl_report_matrix.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_report_matrix.c > umfpack_dl_report_matrix.c
umfpack_dl_report_numeric.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_report_numeric.c > umfpack_dl_report_numeric.c
umfpack_dl_report_perm.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_report_perm.c > umfpack_dl_report_perm.c
umfpack_dl_report_status.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_report_status.c > umfpack_dl_report_status.c
umfpack_dl_report_symbolic.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_report_symbolic.c > umfpack_dl_report_symbolic.c
umfpack_dl_report_triplet.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_report_triplet.c > umfpack_dl_report_triplet.c
umfpack_dl_report_vector.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_report_vector.c > umfpack_dl_report_vector.c
umfpack_dl_solve.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_solve.c > umfpack_dl_solve.c
umfpack_dl_symbolic.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_symbolic.c > umfpack_dl_symbolic.c
umfpack_dl_transpose.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_transpose.c > umfpack_dl_transpose.c
umfpack_dl_triplet_to_col.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_triplet_to_col.c > umfpack_dl_triplet_to_col.c
umfpack_dl_scale.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_scale.c > umfpack_dl_scale.c
umfpack_dl_load_numeric.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_load_numeric.c > umfpack_dl_load_numeric.c
umfpack_dl_save_numeric.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_save_numeric.c > umfpack_dl_save_numeric.c
umfpack_dl_load_symbolic.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_load_symbolic.c > umfpack_dl_load_symbolic.c
umfpack_dl_save_symbolic.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/umfpack_save_symbolic.c > umfpack_dl_save_symbolic.c
umf_zi_lhsolve.c:
	$(CPP) ${CPPINC} -DZINT -DCONJUGATE_SOLVE @srcdir@/umf_ltsolve.c > umf_zi_lhsolve.c
umf_zi_uhsolve.c:
	$(CPP) ${CPPINC} -DZINT -DCONJUGATE_SOLVE @srcdir@/umf_utsolve.c > umf_zi_uhsolve.c
umf_zi_triplet_map_nox.c:
	$(CPP) ${CPPINC} -DZINT -DDO_MAP @srcdir@/umf_triplet.c > umf_zi_triplet_map_nox.c
umf_zi_triplet_nomap_x.c:
	$(CPP) ${CPPINC} -DZINT -DDO_VALUES @srcdir@/umf_triplet.c > umf_zi_triplet_nomap_x.c
umf_zi_triplet_nomap_nox.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_triplet.c > umf_zi_triplet_nomap_nox.c
umf_zi_triplet_map_x.c:
	$(CPP) ${CPPINC} -DZINT -DDO_MAP -DDO_VALUES @srcdir@/umf_triplet.c > umf_zi_triplet_map_x.c
umf_zi_assemble_fixq.c:
	$(CPP) ${CPPINC} -DZINT -DFIXQ @srcdir@/umf_assemble.c > umf_zi_assemble_fixq.c
umf_zi_store_lu_drop.c:
	$(CPP) ${CPPINC} -DZINT -DDROP @srcdir@/umf_store_lu.c > umf_zi_store_lu_drop.c
umf_zi_assemble.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_assemble.c > umf_zi_assemble.c
umf_zi_blas3_update.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_blas3_update.c > umf_zi_blas3_update.c
umf_zi_build_tuples.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_build_tuples.c > umf_zi_build_tuples.c
umf_zi_create_element.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_create_element.c > umf_zi_create_element.c
umf_zi_dump.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_dump.c > umf_zi_dump.c
umf_zi_extend_front.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_extend_front.c > umf_zi_extend_front.c
umf_zi_garbage_collection.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_garbage_collection.c > umf_zi_garbage_collection.c
umf_zi_get_memory.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_get_memory.c > umf_zi_get_memory.c
umf_zi_init_front.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_init_front.c > umf_zi_init_front.c
umf_zi_kernel.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_kernel.c > umf_zi_kernel.c
umf_zi_kernel_init.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_kernel_init.c > umf_zi_kernel_init.c
umf_zi_kernel_wrapup.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_kernel_wrapup.c > umf_zi_kernel_wrapup.c
umf_zi_local_search.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_local_search.c > umf_zi_local_search.c
umf_zi_lsolve.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_lsolve.c > umf_zi_lsolve.c
umf_zi_ltsolve.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_ltsolve.c > umf_zi_ltsolve.c
umf_zi_mem_alloc_element.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_mem_alloc_element.c > umf_zi_mem_alloc_element.c
umf_zi_mem_alloc_head_block.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_mem_alloc_head_block.c > umf_zi_mem_alloc_head_block.c
umf_zi_mem_alloc_tail_block.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_mem_alloc_tail_block.c > umf_zi_mem_alloc_tail_block.c
umf_zi_mem_free_tail_block.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_mem_free_tail_block.c > umf_zi_mem_free_tail_block.c
umf_zi_mem_init_memoryspace.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_mem_init_memoryspace.c > umf_zi_mem_init_memoryspace.c
umf_zi_report_vector.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_report_vector.c > umf_zi_report_vector.c
umf_zi_row_search.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_row_search.c > umf_zi_row_search.c
umf_zi_scale_column.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_scale_column.c > umf_zi_scale_column.c
umf_zi_set_stats.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_set_stats.c > umf_zi_set_stats.c
umf_zi_solve.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_solve.c > umf_zi_solve.c
umf_zi_symbolic_usage.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_symbolic_usage.c > umf_zi_symbolic_usage.c
umf_zi_transpose.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_transpose.c > umf_zi_transpose.c
umf_zi_tuple_lengths.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_tuple_lengths.c > umf_zi_tuple_lengths.c
umf_zi_usolve.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_usolve.c > umf_zi_usolve.c
umf_zi_utsolve.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_utsolve.c > umf_zi_utsolve.c
umf_zi_valid_numeric.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_valid_numeric.c > umf_zi_valid_numeric.c
umf_zi_valid_symbolic.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_valid_symbolic.c > umf_zi_valid_symbolic.c
umf_zi_grow_front.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_grow_front.c > umf_zi_grow_front.c
umf_zi_start_front.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_start_front.c > umf_zi_start_front.c
umf_zi_2by2.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_2by2.c > umf_zi_2by2.c
umf_zi_store_lu.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_store_lu.c > umf_zi_store_lu.c
umf_zi_scale.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umf_scale.c > umf_zi_scale.c
umfpack_zi_wsolve.c:
	$(CPP) ${CPPINC} -DZINT -DWSOLVE @srcdir@/umfpack_solve.c > umfpack_zi_wsolve.c
umfpack_zi_col_to_triplet.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_col_to_triplet.c > umfpack_zi_col_to_triplet.c
umfpack_zi_defaults.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_defaults.c > umfpack_zi_defaults.c
umfpack_zi_free_numeric.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_free_numeric.c > umfpack_zi_free_numeric.c
umfpack_zi_free_symbolic.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_free_symbolic.c > umfpack_zi_free_symbolic.c
umfpack_zi_get_numeric.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_get_numeric.c > umfpack_zi_get_numeric.c
umfpack_zi_get_lunz.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_get_lunz.c > umfpack_zi_get_lunz.c
umfpack_zi_get_symbolic.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_get_symbolic.c > umfpack_zi_get_symbolic.c
umfpack_zi_get_determinant.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_get_determinant.c > umfpack_zi_get_determinant.c
umfpack_zi_numeric.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_numeric.c > umfpack_zi_numeric.c
umfpack_zi_qsymbolic.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_qsymbolic.c > umfpack_zi_qsymbolic.c
umfpack_zi_report_control.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_report_control.c > umfpack_zi_report_control.c
umfpack_zi_report_info.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_report_info.c > umfpack_zi_report_info.c
umfpack_zi_report_matrix.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_report_matrix.c > umfpack_zi_report_matrix.c
umfpack_zi_report_numeric.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_report_numeric.c > umfpack_zi_report_numeric.c
umfpack_zi_report_perm.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_report_perm.c > umfpack_zi_report_perm.c
umfpack_zi_report_status.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_report_status.c > umfpack_zi_report_status.c
umfpack_zi_report_symbolic.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_report_symbolic.c > umfpack_zi_report_symbolic.c
umfpack_zi_report_triplet.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_report_triplet.c > umfpack_zi_report_triplet.c
umfpack_zi_report_vector.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_report_vector.c > umfpack_zi_report_vector.c
umfpack_zi_solve.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_solve.c > umfpack_zi_solve.c
umfpack_zi_symbolic.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_symbolic.c > umfpack_zi_symbolic.c
umfpack_zi_transpose.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_transpose.c > umfpack_zi_transpose.c
umfpack_zi_triplet_to_col.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_triplet_to_col.c > umfpack_zi_triplet_to_col.c
umfpack_zi_scale.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_scale.c > umfpack_zi_scale.c
umfpack_zi_load_numeric.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_load_numeric.c > umfpack_zi_load_numeric.c
umfpack_zi_save_numeric.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_save_numeric.c > umfpack_zi_save_numeric.c
umfpack_zi_load_symbolic.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_load_symbolic.c > umfpack_zi_load_symbolic.c
umfpack_zi_save_symbolic.c:
	$(CPP) ${CPPINC} -DZINT @srcdir@/umfpack_save_symbolic.c > umfpack_zi_save_symbolic.c
umf_zl_lhsolve.c:
	$(CPP) ${CPPINC} -DZLONG -DCONJUGATE_SOLVE @srcdir@/umf_ltsolve.c > umf_zl_lhsolve.c
umf_zl_uhsolve.c:
	$(CPP) ${CPPINC} -DZLONG -DCONJUGATE_SOLVE @srcdir@/umf_utsolve.c > umf_zl_uhsolve.c
umf_zl_triplet_map_nox.c:
	$(CPP) ${CPPINC} -DZLONG -DDO_MAP @srcdir@/umf_triplet.c > umf_zl_triplet_map_nox.c
umf_zl_triplet_nomap_x.c:
	$(CPP) ${CPPINC} -DZLONG -DDO_VALUES @srcdir@/umf_triplet.c > umf_zl_triplet_nomap_x.c
umf_zl_triplet_nomap_nox.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_triplet.c > umf_zl_triplet_nomap_nox.c
umf_zl_triplet_map_x.c:
	$(CPP) ${CPPINC} -DZLONG -DDO_MAP -DDO_VALUES @srcdir@/umf_triplet.c > umf_zl_triplet_map_x.c
umf_zl_assemble_fixq.c:
	$(CPP) ${CPPINC} -DZLONG -DFIXQ @srcdir@/umf_assemble.c > umf_zl_assemble_fixq.c
umf_zl_store_lu_drop.c:
	$(CPP) ${CPPINC} -DZLONG -DDROP @srcdir@/umf_store_lu.c > umf_zl_store_lu_drop.c
umf_zl_assemble.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_assemble.c > umf_zl_assemble.c
umf_zl_blas3_update.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_blas3_update.c > umf_zl_blas3_update.c
umf_zl_build_tuples.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_build_tuples.c > umf_zl_build_tuples.c
umf_zl_create_element.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_create_element.c > umf_zl_create_element.c
umf_zl_dump.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_dump.c > umf_zl_dump.c
umf_zl_extend_front.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_extend_front.c > umf_zl_extend_front.c
umf_zl_garbage_collection.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_garbage_collection.c > umf_zl_garbage_collection.c
umf_zl_get_memory.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_get_memory.c > umf_zl_get_memory.c
umf_zl_init_front.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_init_front.c > umf_zl_init_front.c
umf_zl_kernel.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_kernel.c > umf_zl_kernel.c
umf_zl_kernel_init.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_kernel_init.c > umf_zl_kernel_init.c
umf_zl_kernel_wrapup.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_kernel_wrapup.c > umf_zl_kernel_wrapup.c
umf_zl_local_search.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_local_search.c > umf_zl_local_search.c
umf_zl_lsolve.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_lsolve.c > umf_zl_lsolve.c
umf_zl_ltsolve.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_ltsolve.c > umf_zl_ltsolve.c
umf_zl_mem_alloc_element.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_mem_alloc_element.c > umf_zl_mem_alloc_element.c
umf_zl_mem_alloc_head_block.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_mem_alloc_head_block.c > umf_zl_mem_alloc_head_block.c
umf_zl_mem_alloc_tail_block.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_mem_alloc_tail_block.c > umf_zl_mem_alloc_tail_block.c
umf_zl_mem_free_tail_block.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_mem_free_tail_block.c > umf_zl_mem_free_tail_block.c
umf_zl_mem_init_memoryspace.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_mem_init_memoryspace.c > umf_zl_mem_init_memoryspace.c
umf_zl_report_vector.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_report_vector.c > umf_zl_report_vector.c
umf_zl_row_search.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_row_search.c > umf_zl_row_search.c
umf_zl_scale_column.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_scale_column.c > umf_zl_scale_column.c
umf_zl_set_stats.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_set_stats.c > umf_zl_set_stats.c
umf_zl_solve.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_solve.c > umf_zl_solve.c
umf_zl_symbolic_usage.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_symbolic_usage.c > umf_zl_symbolic_usage.c
umf_zl_transpose.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_transpose.c > umf_zl_transpose.c
umf_zl_tuple_lengths.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_tuple_lengths.c > umf_zl_tuple_lengths.c
umf_zl_usolve.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_usolve.c > umf_zl_usolve.c
umf_zl_utsolve.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_utsolve.c > umf_zl_utsolve.c
umf_zl_valid_numeric.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_valid_numeric.c > umf_zl_valid_numeric.c
umf_zl_valid_symbolic.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_valid_symbolic.c > umf_zl_valid_symbolic.c
umf_zl_grow_front.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_grow_front.c > umf_zl_grow_front.c
umf_zl_start_front.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_start_front.c > umf_zl_start_front.c
umf_zl_2by2.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_2by2.c > umf_zl_2by2.c
umf_zl_store_lu.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_store_lu.c > umf_zl_store_lu.c
umf_zl_scale.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umf_scale.c > umf_zl_scale.c
umfpack_zl_wsolve.c:
	$(CPP) ${CPPINC} -DZLONG -DWSOLVE @srcdir@/umfpack_solve.c > umfpack_zl_wsolve.c
umfpack_zl_col_to_triplet.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_col_to_triplet.c > umfpack_zl_col_to_triplet.c
umfpack_zl_defaults.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_defaults.c > umfpack_zl_defaults.c
umfpack_zl_free_numeric.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_free_numeric.c > umfpack_zl_free_numeric.c
umfpack_zl_free_symbolic.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_free_symbolic.c > umfpack_zl_free_symbolic.c
umfpack_zl_get_numeric.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_get_numeric.c > umfpack_zl_get_numeric.c
umfpack_zl_get_lunz.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_get_lunz.c > umfpack_zl_get_lunz.c
umfpack_zl_get_symbolic.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_get_symbolic.c > umfpack_zl_get_symbolic.c
umfpack_zl_get_determinant.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_get_determinant.c > umfpack_zl_get_determinant.c
umfpack_zl_numeric.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_numeric.c > umfpack_zl_numeric.c
umfpack_zl_qsymbolic.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_qsymbolic.c > umfpack_zl_qsymbolic.c
umfpack_zl_report_control.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_report_control.c > umfpack_zl_report_control.c
umfpack_zl_report_info.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_report_info.c > umfpack_zl_report_info.c
umfpack_zl_report_matrix.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_report_matrix.c > umfpack_zl_report_matrix.c
umfpack_zl_report_numeric.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_report_numeric.c > umfpack_zl_report_numeric.c
umfpack_zl_report_perm.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_report_perm.c > umfpack_zl_report_perm.c
umfpack_zl_report_status.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_report_status.c > umfpack_zl_report_status.c
umfpack_zl_report_symbolic.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_report_symbolic.c > umfpack_zl_report_symbolic.c
umfpack_zl_report_triplet.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_report_triplet.c > umfpack_zl_report_triplet.c
umfpack_zl_report_vector.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_report_vector.c > umfpack_zl_report_vector.c
umfpack_zl_solve.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_solve.c > umfpack_zl_solve.c
umfpack_zl_symbolic.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_symbolic.c > umfpack_zl_symbolic.c
umfpack_zl_transpose.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_transpose.c > umfpack_zl_transpose.c
umfpack_zl_triplet_to_col.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_triplet_to_col.c > umfpack_zl_triplet_to_col.c
umfpack_zl_scale.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_scale.c > umfpack_zl_scale.c
umfpack_zl_load_numeric.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_load_numeric.c > umfpack_zl_load_numeric.c
umfpack_zl_save_numeric.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_save_numeric.c > umfpack_zl_save_numeric.c
umfpack_zl_load_symbolic.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_load_symbolic.c > umfpack_zl_load_symbolic.c
umfpack_zl_save_symbolic.c:
	$(CPP) ${CPPINC} -DZLONG @srcdir@/umfpack_save_symbolic.c > umfpack_zl_save_symbolic.c

UMF_GN = umfpack_gn_global.c umfpack_gn_timer.c umfpack_gn_tictoc.c
UMF_I = umf_i_analyze.c umf_i_apply_order.c umf_i_colamd.c umf_i_free.c \
   umf_i_fsize.c umf_i_is_permutation.c umf_i_malloc.c umf_i_realloc.c \
   umf_i_report_perm.c umf_i_singletons.c umf_di_lhsolve.c \
   umf_di_uhsolve.c umf_di_triplet_map_nox.c umf_di_triplet_nomap_x.c \
   umf_di_triplet_nomap_nox.c umf_di_triplet_map_x.c \
   umf_di_assemble_fixq.c umf_di_store_lu_drop.c umf_di_assemble.c \
   umf_di_blas3_update.c umf_di_build_tuples.c \
   umf_di_create_element.c umf_di_dump.c umf_di_extend_front.c \
   umf_di_garbage_collection.c umf_di_get_memory.c \
   umf_di_init_front.c umf_di_kernel.c umf_di_kernel_init.c \
   umf_di_kernel_wrapup.c umf_di_local_search.c umf_di_lsolve.c \
   umf_di_ltsolve.c umf_di_mem_alloc_element.c \
   umf_di_mem_alloc_head_block.c umf_di_mem_alloc_tail_block.c \
   umf_di_mem_free_tail_block.c umf_di_mem_init_memoryspace.c \
   umf_di_report_vector.c umf_di_row_search.c umf_di_scale_column.c \
   umf_di_set_stats.c umf_di_solve.c umf_di_symbolic_usage.c \
   umf_di_transpose.c umf_di_tuple_lengths.c umf_di_usolve.c \
   umf_di_utsolve.c umf_di_valid_numeric.c umf_di_valid_symbolic.c \
   umf_di_grow_front.c umf_di_start_front.c umf_di_2by2.c \
   umf_di_store_lu.c umf_di_scale.c umfpack_di_wsolve.c \
   umfpack_di_col_to_triplet.c umfpack_di_defaults.c \
   umfpack_di_free_numeric.c umfpack_di_free_symbolic.c \
   umfpack_di_get_numeric.c umfpack_di_get_lunz.c \
   umfpack_di_get_symbolic.c umfpack_di_get_determinant.c \
   umfpack_di_numeric.c \
   umfpack_di_qsymbolic.c umfpack_di_report_control.c \
   umfpack_di_report_info.c umfpack_di_report_matrix.c \
   umfpack_di_report_numeric.c umfpack_di_report_perm.c \
   umfpack_di_report_status.c umfpack_di_report_symbolic.c \
   umfpack_di_report_triplet.c umfpack_di_report_vector.c \
   umfpack_di_solve.c umfpack_di_symbolic.c umfpack_di_transpose.c \
   umfpack_di_triplet_to_col.c umfpack_di_scale.c \
   umfpack_di_load_numeric.c umfpack_di_save_numeric.c \
   umfpack_di_load_symbolic.c umfpack_di_save_symbolic.c 
UMF_L = umf_l_analyze.c umf_l_apply_order.c umf_l_colamd.c umf_l_free.c \
   umf_l_fsize.c umf_l_is_permutation.c umf_l_malloc.c umf_l_realloc.c \
   umf_l_report_perm.c umf_l_singletons.c umf_dl_lhsolve.c \
   umf_dl_uhsolve.c umf_dl_triplet_map_nox.c umf_dl_triplet_nomap_x.c \
   umf_dl_triplet_nomap_nox.c umf_dl_triplet_map_x.c \
   umf_dl_assemble_fixq.c umf_dl_store_lu_drop.c umf_dl_assemble.c \
   umf_dl_blas3_update.c umf_dl_build_tuples.c \
   umf_dl_create_element.c umf_dl_dump.c umf_dl_extend_front.c \
   umf_dl_garbage_collection.c umf_dl_get_memory.c \
   umf_dl_init_front.c umf_dl_kernel.c umf_dl_kernel_init.c \
   umf_dl_kernel_wrapup.c umf_dl_local_search.c umf_dl_lsolve.c \
   umf_dl_ltsolve.c umf_dl_mem_alloc_element.c \
   umf_dl_mem_alloc_head_block.c umf_dl_mem_alloc_tail_block.c \
   umf_dl_mem_free_tail_block.c umf_dl_mem_init_memoryspace.c \
   umf_dl_report_vector.c umf_dl_row_search.c umf_dl_scale_column.c \
   umf_dl_set_stats.c umf_dl_solve.c umf_dl_symbolic_usage.c \
   umf_dl_transpose.c umf_dl_tuple_lengths.c umf_dl_usolve.c \
   umf_dl_utsolve.c umf_dl_valid_numeric.c umf_dl_valid_symbolic.c \
   umf_dl_grow_front.c umf_dl_start_front.c umf_dl_2by2.c \
   umf_dl_store_lu.c umf_dl_scale.c umfpack_dl_wsolve.c \
   umfpack_dl_col_to_triplet.c umfpack_dl_defaults.c \
   umfpack_dl_free_numeric.c umfpack_dl_free_symbolic.c \
   umfpack_dl_get_numeric.c umfpack_dl_get_lunz.c \
   umfpack_dl_get_symbolic.c umfpack_dl_get_determinant.c \
   umfpack_dl_numeric.c umfpack_dl_qsymbolic.c umfpack_dl_report_control.c \
   umfpack_dl_report_info.c umfpack_dl_report_matrix.c \
   umfpack_dl_report_numeric.c umfpack_dl_report_perm.c \
   umfpack_dl_report_status.c umfpack_dl_report_symbolic.c \
   umfpack_dl_report_triplet.c umfpack_dl_report_vector.c \
   umfpack_dl_solve.c umfpack_dl_symbolic.c umfpack_dl_transpose.c \
   umfpack_dl_triplet_to_col.c umfpack_dl_scale.c \
   umfpack_dl_load_numeric.c umfpack_dl_save_numeric.c \
   umfpack_dl_load_symbolic.c umfpack_dl_save_symbolic.c
UMF_ZI = umf_zi_lhsolve.c umf_zi_uhsolve.c \
   umf_zi_triplet_map_nox.c umf_zi_triplet_nomap_x.c \
   umf_zi_triplet_nomap_nox.c umf_zi_triplet_map_x.c \
   umf_zi_assemble_fixq.c umf_zi_store_lu_drop.c umf_zi_assemble.c \
   umf_zi_blas3_update.c umf_zi_build_tuples.c \
   umf_zi_create_element.c umf_zi_dump.c umf_zi_extend_front.c \
   umf_zi_garbage_collection.c umf_zi_get_memory.c \
   umf_zi_init_front.c umf_zi_kernel.c umf_zi_kernel_init.c \
   umf_zi_kernel_wrapup.c umf_zi_local_search.c umf_zi_lsolve.c \
   umf_zi_ltsolve.c umf_zi_mem_alloc_element.c \
   umf_zi_mem_alloc_head_block.c umf_zi_mem_alloc_tail_block.c \
   umf_zi_mem_free_tail_block.c umf_zi_mem_init_memoryspace.c \
   umf_zi_report_vector.c umf_zi_row_search.c umf_zi_scale_column.c \
   umf_zi_set_stats.c umf_zi_solve.c umf_zi_symbolic_usage.c \
   umf_zi_transpose.c umf_zi_tuple_lengths.c umf_zi_usolve.c \
   umf_zi_utsolve.c umf_zi_valid_numeric.c umf_zi_valid_symbolic.c \
   umf_zi_grow_front.c umf_zi_start_front.c umf_zi_2by2.c \
   umf_zi_store_lu.c umf_zi_scale.c umfpack_zi_wsolve.c \
   umfpack_zi_col_to_triplet.c umfpack_zi_defaults.c \
   umfpack_zi_free_numeric.c umfpack_zi_free_symbolic.c \
   umfpack_zi_get_numeric.c umfpack_zi_get_lunz.c \
   umfpack_zi_get_symbolic.c umfpack_zi_get_determinant.c \
   umfpack_zi_numeric.c umfpack_zi_qsymbolic.c umfpack_zi_report_control.c \
   umfpack_zi_report_info.c umfpack_zi_report_matrix.c \
   umfpack_zi_report_numeric.c umfpack_zi_report_perm.c \
   umfpack_zi_report_status.c umfpack_zi_report_symbolic.c \
   umfpack_zi_report_triplet.c umfpack_zi_report_vector.c \
   umfpack_zi_solve.c umfpack_zi_symbolic.c umfpack_zi_transpose.c \
   umfpack_zi_triplet_to_col.c umfpack_zi_scale.c \
   umfpack_zi_load_numeric.c umfpack_zi_save_numeric.c \
   umfpack_zi_load_symbolic.c umfpack_zi_save_symbolic.c
UMF_ZL = umf_zl_lhsolve.c umf_zl_uhsolve.c \
   umf_zl_triplet_map_nox.c umf_zl_triplet_nomap_x.c \
   umf_zl_triplet_nomap_nox.c umf_zl_triplet_map_x.c \
   umf_zl_assemble_fixq.c umf_zl_store_lu_drop.c umf_zl_assemble.c \
   umf_zl_blas3_update.c umf_zl_build_tuples.c \
   umf_zl_create_element.c umf_zl_dump.c umf_zl_extend_front.c \
   umf_zl_garbage_collection.c umf_zl_get_memory.c \
   umf_zl_init_front.c umf_zl_kernel.c umf_zl_kernel_init.c \
   umf_zl_kernel_wrapup.c umf_zl_local_search.c umf_zl_lsolve.c \
   umf_zl_ltsolve.c umf_zl_mem_alloc_element.c \
   umf_zl_mem_alloc_head_block.c umf_zl_mem_alloc_tail_block.c \
   umf_zl_mem_free_tail_block.c umf_zl_mem_init_memoryspace.c \
   umf_zl_report_vector.c umf_zl_row_search.c umf_zl_scale_column.c \
   umf_zl_set_stats.c umf_zl_solve.c umf_zl_symbolic_usage.c \
   umf_zl_transpose.c umf_zl_tuple_lengths.c umf_zl_usolve.c \
   umf_zl_utsolve.c umf_zl_valid_numeric.c umf_zl_valid_symbolic.c \
   umf_zl_grow_front.c umf_zl_start_front.c umf_zl_2by2.c \
   umf_zl_store_lu.c umf_zl_scale.c umfpack_zl_wsolve.c \
   umfpack_zl_col_to_triplet.c umfpack_zl_defaults.c \
   umfpack_zl_free_numeric.c umfpack_zl_free_symbolic.c \
   umfpack_zl_get_numeric.c umfpack_zl_get_lunz.c \
   umfpack_zl_get_symbolic.c umfpack_zl_get_determinant.c \
   umfpack_zl_numeric.c umfpack_zl_qsymbolic.c umfpack_zl_report_control.c \
   umfpack_zl_report_info.c umfpack_zl_report_matrix.c \
   umfpack_zl_report_numeric.c umfpack_zl_report_perm.c \
   umfpack_zl_report_status.c umfpack_zl_report_symbolic.c \
   umfpack_zl_report_triplet.c umfpack_zl_report_vector.c \
   umfpack_zl_solve.c umfpack_zl_symbolic.c umfpack_zl_transpose.c \
   umfpack_zl_triplet_to_col.c umfpack_zl_scale.c \
   umfpack_zl_load_numeric.c umfpack_zl_save_numeric.c \
   umfpack_zl_load_symbolic.c umfpack_zl_save_symbolic.c

AUTOMAKE_OPTIONS = no-dependencies
SUFFIXES = .y .l .H .h .m .C .cc .c .f .java .o
always_built_SUBDIRS =
SUBDIRS = $(always_built_SUBDIRS) .
THISLIB = umfpack

noinst_LTLIBRARIES    = libumfpack.la

libumfpack_la_SOURCES = ${UMF_GN} ${UMF_I} ${UMF_ZI} ${UMF_L} ${UMF_ZL}

INCLUDES              = @maloc_inc@ 
AM_CFLAGS             = @profile@ @pedantic_ansi@

all-local:
	-cp -p ${top_srcdir}/src/${THISLIB}/punc/*.h ../aaa_inc/punc/.

clean-local:
	-rm -f ${UMF_GN} ${UMF_I} ${UMF_ZI} ${UMF_L} ${UMF_ZL}

