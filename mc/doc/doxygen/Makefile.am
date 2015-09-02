### ##########################################################################
### MC = < Manifold Code >
### Copyright (C) 1994-- Michael Holst
###
### This program is free software; you can redistribute it and/or modify it
### under the terms of the GNU General Public License as published by the
### Free Software Foundation; either version 2 of the License, or (at your
### option) any later version.
###
### This program is distributed in the hope that it will be useful,
### but WITHOUT ANY WARRANTY; without even the implied warranty of
### MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
### See the GNU General Public License for more details.
###
### You should have received a copy of the GNU General Public License along
### with this program; if not, write to the Free Software Foundation, Inc.,
### 675 Mass Ave, Cambridge, MA 02139, USA.
###
### rcsid="$Id: Makefile.am,v 1.5 2010/08/12 05:16:31 fetk Exp $"
### ##########################################################################

## ###########################################################################
## File:    Makefile
##
## Purpose: Automatically generate documentation using doxygen.
##
## Notes:   Both HTML and LaTeX (dvi/ps/pdf) documentation is created.
##
## Author:  Michael Holst
## ###########################################################################

docdir = @prefix@/doc/mc

doc_DATA = mc_doc

mc_doc: 
	$(doxygen_path) $(top_srcdir)/doc/doxygen/mc.dox

install-docDATA:
	mkdir -p $(docdir)
	cp -r ../api $(docdir)/
