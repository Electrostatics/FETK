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
### rcsid="$Id: Makefile.am,v 1.5 2010/08/12 05:52:08 fetk Exp $"
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

docdir = @prefix@/doc/punc

doc_DATA = punc_doc

punc_doc: 
	$(doxygen_path) $(top_srcdir)/doc/doxygen/punc.dox

install-docDATA:
	mkdir -p $(docdir)
	cp -r ../api $(docdir)/
