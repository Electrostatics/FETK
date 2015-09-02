/**
 * @defgroup global_sg global_sg class
 * @brief    Global group for SG
 */

/**
 *  @file       sg_base.h
 *  @ingroup    global_sg
 *  @author     Michael Holst
 *  @brief      The base (or foundation) header for SG.
 *  @note       None
 *  @version    $Id: sg_base.h,v 1.7 2010/08/12 04:56:17 fetk Exp $
 *
 *  @attention
 *  @verbatim
 *
 * SG = < Socket Graphics >
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
 *  @endverbatim
 */


#ifndef _SG_BASE_H_
#define _SG_BASE_H_

#include <maloc/maloc.h>

/*
 * ***************************************************************************
 * Some parameters 
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Inlining via macros for speed
 * ***************************************************************************
 */

/** @brief Inlining via macros for speed */
#if 1
/** @brief Class Ogl:Inlineable methods */    
#   define VINLINE_OGL
/** @brief Class Vgl:Inlineable methods */    
#   define VINLINE_VGL
#endif

#endif /* _SG_BASE_H_ */

