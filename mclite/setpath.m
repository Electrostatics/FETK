%SETPATH  Initialize the MCLite package
%
% Usage: setpath
%
% Author:   Michael Holst
% rcsid="$Id: setpath.m,v 1.1.1.1 2007/04/27 08:28:05 hrg Exp $"

%%% setup the MCLite library paths

   path(path,'lib');
   path(path,'lib/adapt');
   path(path,'lib/geom');
   path(path,'lib/io');
   path(path,'lib/master');
   path(path,'lib/mcsf');
   path(path,'lib/pde');
   path(path,'lib/solv');
   path(path,'lib/util');

%%% some i/o

   clc;
   mclitehi;

