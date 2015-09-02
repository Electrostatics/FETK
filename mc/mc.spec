### ##########################################################################
### MC = < Manifold Code >
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
### rcsid="$Id: mc.spec,v 1.4 2010/08/09 19:01:36 fetk Exp $"
### ##########################################################################

## ###########################################################################
## File:    mc.spec
##
## Purpose: Spec file for building RPMS
##
## Notes:   If this is installed in the top directory the user can build a
##          full set of src and arch rpms with one command:
##
##          rpm -ta mc.tar.gz
##
## Author:  Stephen Bond and Michael Holst
## ###########################################################################

Summary: Manifold Code
Name: mc
Version: 0.1
Release: 1
Copyright: GPL
Group: Applications/Science
Prefix: /usr/local
Buildroot: %{_topdir}/buildroot
Source: mc.tar.gz
URL: http://cam.ucsd.edu/~mholst
Packager: Michael Holst <mholst@math.ucsd.edu>
%description
MC (Manifold Code) is a small self-contained parallel adaptive multilevel
finite element software package.  MC is an adaptive multilevel finite
element kernel designed to be used collaboratively with several related
research tools such as MALOC, SG, and APBS.  MC can be used as a small
stand-alone adaptive multilevel finite element code, or it can be used with
these other tools which extend the capabilities of MC in various ways.
MC is designed to numerically approximate the solutions of covariant
divergence-form second-order nonlinear elliptic systems of partial
differential equations on domains with the structure of Riemannian two-
and three-manifolds.  To accomplish this task as accurately and efficiently
as possible, MC employs simplex triangulations of the domain manifold,
Petrov-Galerkin finite element methods, a posteriori error estimation, 
adaptive mesh refinement and un-refinement, continuation, Newton methods,
multilevel methods, and a new low-communication approach in parallel
adaptive finite element methods.

%prep
%setup -n mc

%build

./configure --prefix=${RPM_BUILD_ROOT}/%{prefix}
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
