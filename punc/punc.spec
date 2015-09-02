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
### rcsid="$Id: punc.spec,v 1.14 2010/08/09 19:01:48 fetk Exp $"
### ##########################################################################

## ###########################################################################
## File:    punc.spec
##
## Purpose: Spec file for building RPMS
##
## Notes:   If this is installed in the top directory the user can build a
##          full set of src and arch rpms with one command:
##
##          rpm -ta punc.tar.gz
##
## Author:  Stephen Bond and Michael Holst
## ###########################################################################

Summary: Portable Understructure for Numerical Computing
Name: punc
Version: 0.1
Release: 2
Copyright: GPL
Group: Applications/Science
Prefix: /usr/local
Buildroot: %{_topdir}/buildroot
Source: punc-0.1-2.tar.gz
URL: http://scicomp.ucsd.edu/~mholst
Packager: Michael Holst <mholst@math.ucsd.edu>
%description
PUNC (Portable Understructure for Numerical Computing) is a small portable 
collection of standard numerical linear algebra and other reference 
libraries for numerical analysis software.  Some of the higher-level 
libraries in the collection are further wrapped with an object-oriented 
C interface for safer/easier software engineering into other software.
PUNC is used as the linear algebra layer for a number of applications,
including MC and FEtk.

%prep
%setup -n punc

%build

%ifarch alpha
  export CC='ccc'
  export CFLAGS='-O2'
  export F77='fort'
  export FFLAGS='-O2'
  ./configure --enable-shared --prefix=${RPM_BUILD_ROOT}/%{prefix}
  make 
%endif

# For Portland group compilers on the AMD Opteron
# Note - we need to disable blas 
%ifarch x86_64 
     export CC=pgcc
     export CFLAGS='-O2 -fastsse -fPIC'
     ./configure --prefix=${RPM_BUILD_ROOT}/%{prefix} --disable-blas
     make
%endif
     
# For Itanium ia64 
# Note - we need to disable blas
%ifarch ia64
     export CC=icc
     export CFLAGS='-O2 -fPIC'
     ./configure --prefix=${RPM_BUILD_ROOT}/%{prefix} --disable-blas
     make
%endif

# For power 64, disabling blas
%ifarch ppc64 ppc64pseries
     export CC=xlc
     export CFLAGS="-q64 -qarch=pwr4 -qtune=pwr4"
     ./configure --prefix=${RPM_BUILD_ROOT}/%{prefix}  --disable-blas
     make
%endif

# All others
%ifnarch alpha x86_64 ia64 ppc64 ppc64pseries
     export CC=icc
     export CFLAGS='-O2 -fPIC'
     ./configure --prefix=${RPM_BUILD_ROOT}/%{prefix}
     make 
%endif

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

