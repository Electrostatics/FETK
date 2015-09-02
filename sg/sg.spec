### ##########################################################################
### SG = < Socket Graphics >
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
### rcsid="$Id: sg.spec,v 1.4 2010/08/09 19:01:59 fetk Exp $"
### ##########################################################################

## ###########################################################################
## File:    sg.spec
##
## Purpose: Spec file for building RPMS
##
## Notes:   If this is installed in the top directory the user can build a
##          full set of src and arch rpms with one command:
##
##          rpm -ta sg.tar.gz
##
## Author:  Stephen Bond and Michael Holst
## ###########################################################################

Summary: Socket Graphics
Name: sg
Version: 0.1
Release: 1
Copyright: GPL
Group: Applications/Science
Prefix: /usr/local
Buildroot: %{_topdir}/buildroot
Source: sg.tar.gz
URL: http://scicomp.ucsd.edu/~mholst
Packager: Michael Holst <mholst@math.ucsd.edu>
%description
SG (Socket Graphics) is an unstructured simplex mesh OpenGL display and
manipulation tool for use with the finite element research codes MC and
PLTMG.  SG provides OpenGL-based graphics over UNIX and INET sockets on
UNIX/X-based systems, Win32-based systems, and other systems.  It can
also be used with MCLite as a replacement for MATLAB's builtin graphics
for polygons.  SG can read Geomview OFF files and OpenInventor files for
polygonal surface descriptions, and it can also read PDB files for molecule
descriptions.  SG looks and acts somewhat like Geomview, and it mimics most
of the basic features and controls of Geomview for displaying polygonal
2-manifolds.

%prep
%setup -n sg

%build

./configure --enable-shared --prefix=${RPM_BUILD_ROOT}/%{prefix}
make 

%install
mkdir -p ${RPM_BUILD_ROOT}/%{prefix}
make install

%clean
rm -rf ${RPM_BUILD_ROOT}

%post

%postun

%files
%defattr(-,root,root)
%{prefix}/lib
%{prefix}/include
%doc AUTHORS COPYING INSTALL NEWS ChangeLog doc
