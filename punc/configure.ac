dnl ##########################################################################
dnl PUNC = < Portable Understructure for Numerical Computing >
dnl Copyright (C) 1994-- Michael Holst
dnl
dnl This library is free software; you can redistribute it and/or
dnl modify it under the terms of the GNU Lesser General Public
dnl License as published by the Free Software Foundation; either
dnl version 2.1 of the License, or (at your option) any later version.
dnl
dnl This library is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
dnl Lesser General Public License for more details.
dnl
dnl You should have received a copy of the GNU Lesser General Public
dnl License along with this library; if not, write to the Free Software
dnl Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
dnl
dnl rcsid="INTENTIONALLY LEFT BLANK"
dnl ##########################################################################

dnl ##########################################################################
dnl File:    configure.ac
dnl
dnl Purpose: configure.ac script for PUNC (Portable Understructure for
dnl          Numerical Computing).
dnl
dnl Author:  Michael Holst
dnl ##########################################################################

dnl 0. autoconf initialization
AC_INIT(punc, 1.0, mholst@math.ucsd.edu)
AC_CONFIG_SRCDIR(src/aaa_inc/punc/punc.h)
AC_CONFIG_HEADERS(src/aaa_inc/punccf.h)
AC_CONFIG_AUX_DIR(config)
AC_PREFIX_DEFAULT(${HOME})
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

dnl 1. automake initialization
AM_INIT_AUTOMAKE([foreign])
FETK_VERSION="1:0:0"
AC_SUBST(FETK_VERSION)
AM_MAINTAINER_MODE

dnl 2. checks for programs
AC_LANG_C
AC_PROG_CC
AC_PROG_CPP
AC_DISABLE_STATIC
AM_PROG_LIBTOOL

dnl 3. checks for libraries
AC_CHECK_LIB(m,pow,[math_lib="-lm"],[math_lib=""])
AC_SUBST(math_lib)
AC_CHECK_LIB(iberty,strerrno,[liberty_lib="-liberty"],[liberty_lib=""])
AC_SUBST(liberty_lib)
nsl_lib="";
AC_CHECK_FUNC(gethostbyname,[try_nsl=""],[try_nsl="yes"])
if test -n "${try_nsl}"; then
    AC_CHECK_LIB(nsl,gethostbyname,[nsl_lib="-lnsl"],[nsl_lib=""])
fi
AC_SUBST(nsl_lib)
socket_lib="";
AC_CHECK_FUNC(connect,[try_socket=""],[try_socket="yes"])
if test -n "${try_socket}"; then
    AC_CHECK_LIB(socket,connect,[socket_lib="-lsocket"],[socket_lib=""])
fi
AC_SUBST(socket_lib)
thread_lib="";
AC_CHECK_FUNC(thr_create,[try_thread=""],[try_thread="yes"])
if test -n "${try_thread}"; then
    AC_CHECK_LIB(thread,thr_create,[thread_lib="-lthread"],[thread_lib=""])
fi
AC_SUBST(thread_lib)

dnl 4. checks for header files
dnl 5. checks for typedefs
dnl 6. checks for structures
dnl 7. checks for compiler characteristics
dnl 8. checks for library functions
dnl 9. checks for system services
dnl 10. checks for anything else

dnl # ------------------------------------------------
dnl # CHECK WHETHER TO DISABLE CPU-VENDOR-HOST TRIPLET
dnl # ------------------------------------------------
fetk_cpu_vendor_os="";
AC_MSG_CHECKING([whether you want to disable the CPU-VENDOR-OS install triplet])
AC_ARG_ENABLE(triplet,
    [  --disable-triplet       disable CPU-VENDOR-OS install triplet [[default=no]]],
    [ triplet_kill="yes"],
    [ triplet_kill="" ]
)
if test "${triplet_kill}" = yes; then
    AC_MSG_RESULT([yes])
    fetk_cpu_vendor_os="";
else
    AC_MSG_RESULT([no])
    fetk_cpu_vendor_os="${host_cpu}-${host_vendor}-${host_os}";
fi
AC_SUBST(fetk_cpu_vendor_os)

dnl # ---------------------------------------------------
dnl # HANDLE VARIOUS ARCHITECTURE-SPECIFIC CONFIGURATIONS
dnl # ---------------------------------------------------
if test "${host_os}" = "cygwin"; then
    AC_DEFINE(HAVE_CYGWIN)
fi

dnl # ---------------------------
dnl # HANDLE THE READLINE LIBRARY
dnl # ---------------------------
rl_lib="";
AC_MSG_CHECKING([whether your environment defines FETK_RL_LIBRARY])
if test -n "${FETK_RL_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    rl_lib_path="-L${FETK_RL_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    rl_lib_path="";
fi
LDFLAGS_SAVE=${LDFLAGS};
LDFLAGS=${rl_lib_path};
AC_CHECK_LIB(ncurses,tgetnum,
    [ncurses_lib="-lncurses"],
    [ncurses_lib=""],
    [${math_lib}])
AC_CHECK_LIB(readline,readline,
    [rl_use="yes";rl_lib="${rl_lib_path}-lreadline ${ncurses_lib}"],
    [rl_use="";rl_lib=""],
    [${rl_lib_path} ${ncurses_lib} ${math_lib}])
if test -n "${rl_use}"; then
    AC_CHECK_LIB(readline,add_history,
        [rl_use="yes";rl_lib="${rl_lib_path}-lreadline ${ncurses_lib}"],
        [rl_use="";rl_lib=""],
        [${rl_lib_path} ${ncurses_lib} ${math_lib}])
fi
LDFLAGS=${LDFLAGS_SAVE};
AC_SUBST(rl_lib)

dnl # ----------------------
dnl # HANDLE THE MPI LIBRARY
dnl # ----------------------
mpi_lib="";
AC_MSG_CHECKING([whether your environment defines FETK_MPI_LIBRARY])
if test -n "${FETK_MPI_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    mpi_lib_path="-L${FETK_MPI_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    mpi_lib_path="";
fi
LDFLAGS_SAVE=${LDFLAGS};
LDFLAGS=${mpi_lib_path};
mpi_use="";
AC_CHECK_LIB(mpi,main,
    [mpi_use="yes";mpi_lib="${mpi_lib_path}-lmpi"],
    [mpi_use="";mpi_lib=""],${mpi_lib_path})
if test -z "${mpi_use}"; then
    AC_CHECK_LIB(mpich,main,
        [mpi_use="yes";mpi_lib="${mpi_lib_path}-lmpich"],
        [mpi_use="";mpi_lib=""],${mpi_lib_path})
fi
LDFLAGS=${LDFLAGS_SAVE};
AC_SUBST(mpi_lib)

dnl # -----------------------
dnl # HANDLE SYMBOL EMBEDDING
dnl # -----------------------
AC_MSG_CHECKING([whether EMBED macro can be used without compilation errors])
AC_TRY_COMPILE(,
    [#define EMBED(rctag) \
     static const char* rctag; \
     static void* use_rcsid=(0 ? &use_rcsid : (void*)&rcsid);
     EMBED(rcsid)],
    [embed_ok=yes;AC_DEFINE(HAVE_EMBED)],[embed_ok=no])
AC_MSG_RESULT(${embed_ok})

AC_MSG_RESULT([---------- begin processing PUNC configure options --------])

dnl # ------------------------
dnl # HANDLE DEBUG COMPILATION
dnl # ------------------------
AC_MSG_CHECKING([whether you want debug compilation])
AC_ARG_ENABLE(vdebug,
    [  --enable-vdebug         enable debug compilation [default=no]],
    [ vdebug_use="yes" ],
    [ vdebug_use=""    ]
)
if test -z "${vdebug_use}"; then
    AC_MSG_RESULT([no])
else
    AC_MSG_RESULT([yes])
    AC_DEFINE(HAVE_DEBUG)
fi

dnl # --------------------------------
dnl # HANDLE ANSI/PEDANTIC COMPILATION
dnl # --------------------------------
AC_MSG_CHECKING([whether you want pedantic ANSI compilation])
AC_ARG_ENABLE(pansi,
    [  --enable-pansi          enable pedantic ANSI compilation],
    [ pansi_use="yes" ],
    [ pansi_use=""    ]
)
if test -z "${pansi_use}"; then
    AC_MSG_RESULT([no])
    wall=""
    wall_pedantic=""
    wall_pedantic_ansi=""
    pedantic_ansi=""
else
    AC_MSG_RESULT([yes])
    wall="-Wall"
    wall_pedantic="-Wall -pedantic"
    wall_pedantic_ansi="-Wall -pedantic -ansi"
    pedantic_ansi="-pedantic -ansi"
fi
AC_SUBST(wall)
AC_SUBST(wall_pedantic)
AC_SUBST(wall_pedantic_ansi)
AC_SUBST(pedantic_ansi)

dnl # ----------------
dnl # HANDLE PROFILING
dnl # ----------------
AC_MSG_CHECKING([whether you want profiling])
AC_ARG_ENABLE(gprof,
    [  --enable-gprof          enable gprof profiling [default=no]],
    [ gprof_use="yes" ],
    [ gprof_use=""    ]
)
if test -z "${gprof_use}"; then
    AC_MSG_RESULT([no])
    profile=""
    profile_lib=""
else
    AC_MSG_RESULT([yes])
    profile="-pg"
    profile_lib="-pg"
fi
AC_SUBST(profile)
AC_SUBST(profile_lib)

dnl # ---------------------------------
dnl # HANDLE THE ELECTRIC FENCE LIBRARY
dnl # ---------------------------------
AC_MSG_CHECKING([whether you want ElectricFence])
AC_ARG_ENABLE(efence,
    [  --enable-efence         enable ElectricFence malloc lib [default=no]],
    [ efence_use="yes" ],
    [ efence_use=""    ]
)
if test -z "${efence_use}"; then
    AC_MSG_RESULT([no])
    zfence="";
    zfence_lib="";
else
    AC_MSG_RESULT([yes ...poking around for it])
    AC_CHECK_LIB(efence,main,
        [efence_use="yes";zfence="zfence";zfence_lib="-lefence"],
        [efence_use="";zfence="";zfence_lib=""])
fi
AC_SUBST(zfence)
AC_SUBST(zfence_lib)

dnl # -----------------------
dnl # HANDLE THE VF2C LIBRARY
dnl # -----------------------

dnl # Check for forced build of VF2C
vf2c_lib="";
vf2c="";
AC_MSG_CHECKING([whether you want force build of VF2C lib])
AC_ARG_ENABLE(vf2cforce,
    [  --enable-vf2cforce      force building of VF2C library [default=no]],
    [ vf2c="vf2c" ],
    [ vf2c="" ],
)

dnl # Look for VF2C if required
if test -n "${vf2c}"; then
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no ...poking around])
   
    dnl # VF2C library location ENV specification
    AC_MSG_CHECKING([whether your environment defines FETK_VF2C_LIBRARY])
    if test -n "${FETK_VF2C_LIBRARY}"; then
        AC_MSG_RESULT([yes])
        vf2c_lib_path="-L${FETK_VF2C_LIBRARY} ";
    else
        AC_MSG_RESULT([no])
        vf2c_lib_path="-L${FETK_LIBRARY} ";
    fi
   
    dnl # Setup temp LDFLAGS and look for VF2C library
    LDFLAGS_SAVE=${LDFLAGS};
    LDFLAGS=${vf2c_lib_path};
    vf2c_use="";
    AC_CHECK_LIB(vf2c,d_abs,
        [vf2c_use="yes";vf2c_lib="${vf2c_lib_path}-lvf2c"],
        [vf2c_use="";vf2c_lib=""],
        [${vf2c_lib_path}-lvf2c])
    if test -z "${vf2c_use}"; then
        AC_MSG_RESULT([** VF2C library missing ...will BUILD **])
        vf2c="vf2c";
    else
        AC_MSG_RESULT([** VF2C library found ...will USE **])
        vf2c="";
    fi
   
    dnl # Return LDFLAGS to normal
    LDFLAGS=${LDFLAGS_SAVE};
fi

dnl # Final decisions on VF2C
AC_SUBST(vf2c_lib)
AC_SUBST(vf2c)
AM_CONDITIONAL(BUILD_VF2C, test x$vf2c = xvf2c)

dnl # -----------------------
dnl # HANDLE THE BLAS LIBRARY
dnl # -----------------------

dnl # Check for forced build of BLAS
blas_lib="";
blas="";
AC_MSG_CHECKING([whether you want force build of BLAS lib])
AC_ARG_ENABLE(blasforce,
    [  --enable-blasforce      force building of BLAS library [default=no]],
    [ blas="blas" ],
    [ blas="" ],
)

dnl # Look for BLAS if required
if test -n "${blas}"; then
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no ...poking around])
   
    dnl # BLAS library location ENV specification
    AC_MSG_CHECKING([whether your environment defines FETK_BLAS_LIBRARY])
    if test -n "${FETK_BLAS_LIBRARY}"; then
        AC_MSG_RESULT([yes])
        blas_lib_path="-L${FETK_BLAS_LIBRARY} ";
    else
        AC_MSG_RESULT([no])
        blas_lib_path="-L${FETK_LIBRARY} ";
    fi
   
    dnl # Setup temp LDFLAGS and look for BLAS library
    LDFLAGS_SAVE=${LDFLAGS};
    LDFLAGS=${blas_lib_path};
    blas_use="";
    AC_CHECK_LIB(blas,dscal_,
        [blas_use="yes";blas_lib="${blas_lib_path}-lblas"],
        [blas_use="";blas_lib=""],
        [${blas_lib_path}-lblas -lvf2c])
    if test -z "${blas_use}"; then
        AC_MSG_RESULT([** BLAS library missing ...will BUILD **])
        blas="blas";
    else
        AC_MSG_RESULT([** BLAS library found ...will USE **])
        blas="";
    fi
   
    dnl # Return LDFLAGS to normal
    LDFLAGS=${LDFLAGS_SAVE};
fi

dnl # Final decisions on BLAS
AC_SUBST(blas_lib)
AC_SUBST(blas)
AM_CONDITIONAL(BUILD_BLAS, test x$blas = xblas)

dnl # -------------------------
dnl # HANDLE THE LAPACK LIBRARY
dnl # -------------------------

dnl # Check for forced build of LAPACK
lapack_lib="";
lapack="";
AC_MSG_CHECKING([whether you want force build of LAPACK lib])
AC_ARG_ENABLE(lapackforce,
    [  --enable-lapackforce    force building of LAPACK library [default=no]],
    [ lapack="lapack" ],
    [ lapack="" ],
)

dnl # Look for LAPACK if required
if test -n "${lapack}"; then
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no])
dnl AC_MSG_RESULT([no ...poking around])
dnl
dnl dnl # LAPACK library location ENV specification
dnl AC_MSG_CHECKING([whether your environment defines FETK_LAPACK_LIBRARY])
dnl if test -n "${FETK_LAPACK_LIBRARY}"; then
dnl     AC_MSG_RESULT([yes])
dnl     lapack_lib_path="-L${FETK_LAPACK_LIBRARY} ";
dnl else
dnl     AC_MSG_RESULT([no])
dnl     lapack_lib_path="-L${FETK_LIBRARY} ";
dnl fi
dnl
dnl dnl # Setup temp LDFLAGS and look for LAPACK library
dnl LDFLAGS_SAVE=${LDFLAGS};
dnl LDFLAGS=${lapack_lib_path};
dnl lapack_use="";
dnl AC_CHECK_LIB(lapack,dsysv_,
dnl     [lapack_use="yes";lapack_lib="${lapack_lib_path}-llapack"],
dnl     [lapack_use="";lapack_lib=""],
dnl     [${lapack_lib_path}-llapack ${blas_lib} -lvf2c])
dnl if test -z "${lapack_use}"; then
dnl     AC_MSG_RESULT([** LAPACK library missing ...will BUILD **])
dnl     lapack="lapack";
dnl else
dnl     AC_MSG_RESULT([** LAPACK library found ...will USE **])
dnl     lapack="";
dnl fi
dnl
dnl dnl # Return LDFLAGS to normal
dnl LDFLAGS=${LDFLAGS_SAVE};
fi

dnl # Final decisions on LAPACK
AC_SUBST(lapack_lib)
AC_SUBST(lapack)
AM_CONDITIONAL(BUILD_LAPACK, test x$lapack = xlapack)

dnl # --------------------------
dnl # HANDLE THE AMD LIBRARY
dnl # --------------------------

dnl # Check for forced build of AMD
amd_lib="";
amd="";
AC_MSG_CHECKING([whether you want force build of AMD lib])
AC_ARG_ENABLE(amdforce,
    [  --enable-amdforce   force building of AMD library [default=no]],
    [ amd="amd" ],
    [ amd="" ],
)

dnl # Look for AMD if required
if test -n "${amd}"; then
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no ...poking around])
   
    dnl # AMD library location ENV specification
    AC_MSG_CHECKING([whether your environment defines FETK_AMD_LIBRARY])
    if test -n "${FETK_AMD_LIBRARY}"; then
        AC_MSG_RESULT([yes])
        amd_lib_path="-L${FETK_AMD_LIBRARY} ";
    else
        AC_MSG_RESULT([no])
        amd_lib_path="-L${FETK_LIBRARY} ";
    fi
   
    dnl # Setup temp LDFLAGS and look for AMD library
    LDFLAGS_SAVE=${LDFLAGS};
    LDFLAGS=${amd_lib_path};
    amd_use="";
    AC_CHECK_LIB(amd,AMD_order,
        [amd_use="yes";amd_lib="${amd_lib_path}-lamd"],
        [amd_use="";amd_lib=""],
        [${amd_lib_path}-lamd ${blas_lib} -lvf2c])
    if test -z "${amd_use}"; then
        AC_MSG_RESULT([** AMD library missing ...will BUILD **])
        amd="amd";
    else
        AC_MSG_RESULT([** AMD library found ...will USE **])
        amd="";
    fi
   
    dnl # Return LDFLAGS to normal
    LDFLAGS=${LDFLAGS_SAVE};
fi

dnl # Final decisions on AMD
AC_SUBST(amd_lib)
AC_SUBST(amd)
AM_CONDITIONAL(BUILD_AMD, test x$amd = xamd)

dnl # --------------------------
dnl # HANDLE THE UMFPACK LIBRARY
dnl # --------------------------

dnl # Check for forced build of UMFPACK
umfpack_lib="";
umfpack="";
AC_MSG_CHECKING([whether you want force build of UMFPACK lib])
AC_ARG_ENABLE(umfpackforce,
    [  --enable-umfpackforce   force building of UMFPACK library [default=no]],
    [ umfpack="umfpack" ],
    [ umfpack="" ],
)

dnl # Look for UMFPACK if required
if test -n "${umfpack}"; then
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no ...poking around])

    dnl # UMFPACK library location ENV specification
    AC_MSG_CHECKING([whether your environment defines FETK_UMFPACK_LIBRARY])
    if test -n "${FETK_UMFPACK_LIBRARY}"; then
        AC_MSG_RESULT([yes])
        umfpack_lib_path="-L${FETK_UMFPACK_LIBRARY} ";
    else
        AC_MSG_RESULT([no])
        umfpack_lib_path="-L${FETK_LIBRARY} ";
    fi

    dnl # Setup temp LDFLAGS and look for UMFPACK library
    LDFLAGS_SAVE=${LDFLAGS};
    LDFLAGS=${umfpack_lib_path};
    umfpack_use="";
    AC_CHECK_LIB(umfpack,UMFPACK_numeric,
        [umfpack_use="yes";umfpack_lib="${umfpack_lib_path}-lumfpack"],
        [umfpack_use="";umfpack_lib=""],
        [${umfpack_lib_path}-lumfpack ${blas_lib} -lvf2c])
    if test -z "${umfpack_use}"; then
        AC_MSG_RESULT([** UMFPACK library missing ...will BUILD **])
        umfpack="umfpack";
    else
        AC_MSG_RESULT([** UMFPACK library found ...will USE **])
        umfpack="";
    fi

    dnl # Return LDFLAGS to normal
    LDFLAGS=${LDFLAGS_SAVE};
fi

dnl # Final decisions on UMFPACK
AC_SUBST(umfpack_lib)
AC_SUBST(umfpack)
AM_CONDITIONAL(BUILD_UMFPACK, test x$umfpack = xumfpack)

dnl # --------------------------
dnl # HANDLE THE SUPERLU LIBRARY
dnl # --------------------------

dnl # Check for forced build of SUPERLU
superlu_lib="";
superlu="";
AC_MSG_CHECKING([whether you want force build of SUPERLU lib])
AC_ARG_ENABLE(superluforce,
    [  --enable-superluforce   force building of SUPERLU library [default=no]],
    [ superlu="superlu" ],
    [ superlu="" ],
)

dnl # Look for SUPERLU if required
if test -n "${superlu}"; then
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no ...poking around])
   
    dnl # SUPERLU library location ENV specification
    AC_MSG_CHECKING([whether your environment defines FETK_SUPERLU_LIBRARY])
    if test -n "${FETK_SUPERLU_LIBRARY}"; then
        AC_MSG_RESULT([yes])
        superlu_lib_path="-L${FETK_SUPERLU_LIBRARY} ";
    else
        AC_MSG_RESULT([no])
        superlu_lib_path="-L${FETK_LIBRARY} ";
    fi
   
    dnl # Setup temp LDFLAGS and look for SUPERLU library
    LDFLAGS_SAVE=${LDFLAGS};
    LDFLAGS=${superlu_lib_path};
    superlu_use="";
    AC_CHECK_LIB(superlu,Destroy_SuperMatrix_Store,
        [superlu_use="yes";superlu_lib="${superlu_lib_path}-lsuperlu"],
        [superlu_use="";superlu_lib=""],
        [${superlu_lib_path}-lsuperlu ${lapack_lib} ${blas_lib} -lvf2c])
    if test -z "${superlu_use}"; then
        AC_MSG_RESULT([** SUPERLU library missing ...will BUILD **])
        superlu="superlu";
    else
        AC_MSG_RESULT([** SUPERLU library found ...will USE **])
        superlu="";
    fi
   
    dnl # Return LDFLAGS to normal
    LDFLAGS=${LDFLAGS_SAVE};
fi

dnl # Final decisions on SUPERLU
AC_SUBST(superlu_lib)
AC_SUBST(superlu)
AM_CONDITIONAL(BUILD_SUPERLU, test x$superlu = xsuperlu)

dnl # -------------------------
dnl # HANDLE THE ARPACK LIBRARY
dnl # -------------------------

dnl # Check for forced build of ARPACK
arpack_lib="";
arpack="";
AC_MSG_CHECKING([whether you want force build of ARPACK lib])
AC_ARG_ENABLE(arpackforce,
    [  --enable-arpackforce    force building of ARPACK library [default=no]],
    [ arpack="arpack" ],
    [ arpack="" ],
)

dnl # Look for ARPACK if required
if test -n "${arpack}"; then
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no])
dnl AC_MSG_RESULT([no ...poking around])
dnl
dnl dnl # ARPACK library location ENV specification
dnl AC_MSG_CHECKING([whether your environment defines FETK_ARPACK_LIBRARY])
dnl if test -n "${FETK_ARPACK_LIBRARY}"; then
dnl     AC_MSG_RESULT([yes])
dnl     arpack_lib_path="-L${FETK_ARPACK_LIBRARY} ";
dnl else
dnl     AC_MSG_RESULT([no])
dnl     arpack_lib_path="-L${FETK_LIBRARY} ";
dnl fi
dnl
dnl dnl # Setup temp LDFLAGS and look for ARPACK library
dnl LDFLAGS_SAVE=${LDFLAGS};
dnl LDFLAGS=${arpack_lib_path};
dnl arpack_use="";
dnl AC_CHECK_LIB(arpack,dsgets_,
dnl     [arpack_use="yes";arpack_lib="${arpack_lib_path}-larpack"],
dnl     [arpack_use="";arpack_lib=""],
dnl     [${arpack_lib_path}-larpack ${blas_lib} -lvf2c])
dnl if test -z "${arpack_use}"; then
dnl     AC_MSG_RESULT([** ARPACK library missing ...will BUILD **])
dnl     arpack="arpack";
dnl else
dnl     AC_MSG_RESULT([** ARPACK library found ...will USE **])
dnl     arpack="";
dnl fi
dnl
dnl dnl # Return LDFLAGS to normal
dnl LDFLAGS=${LDFLAGS_SAVE};
fi

dnl # Final decisions on ARPACK
AC_SUBST(arpack_lib)
AC_SUBST(arpack)
AM_CONDITIONAL(BUILD_ARPACK, test x$arpack = xarpack)

dnl # -------------------------
dnl # HANDLE THE CGCODE LIBRARY
dnl # -------------------------

dnl # Check for forced build of CGCODE
cgcode_lib="";
cgcode="";
AC_MSG_CHECKING([whether you want force build of CGCODE lib])
AC_ARG_ENABLE(cgcodeforce,
    [  --enable-cgcodeforce    force building of CGCODE library [default=no]],
    [ cgcode="cgcode" ],
    [ cgcode="" ],
)

dnl # Look for CGCODE if required
if test -n "${cgcode}"; then
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no])
dnl AC_MSG_RESULT([no ...poking around])
dnl
dnl dnl # CGCODE library location ENV specification
dnl AC_MSG_CHECKING([whether your environment defines FETK_CGCODE_LIBRARY])
dnl if test -n "${FETK_CGCODE_LIBRARY}"; then
dnl     AC_MSG_RESULT([yes])
dnl     cgcode_lib_path="-L${FETK_CGCODE_LIBRARY} ";
dnl else
dnl     AC_MSG_RESULT([no])
dnl     cgcode_lib_path="-L${FETK_LIBRARY} ";
dnl fi
dnl
dnl dnl # Setup temp LDFLAGS and look for CGCODE library
dnl LDFLAGS_SAVE=${LDFLAGS};
dnl LDFLAGS=${cgcode_lib_path};
dnl cgcode_use="";
dnl AC_CHECK_LIB(cgcode,scgdrv_,
dnl     [cgcode_use="yes";cgcode_lib="${cgcode_lib_path}-lcgcode"],
dnl     [cgcode_use="";cgcode_lib=""],
dnl     [${cgcode_lib_path}-lcgcode ${blas_lib} -lvf2c])
dnl if test -z "${cgcode_use}"; then
dnl     AC_MSG_RESULT([** CGCODE library missing ...will BUILD **])
dnl     cgcode="cgcode";
dnl else
dnl     AC_MSG_RESULT([** CGCODE library found ...will USE **])
dnl     cgcode="";
dnl fi
dnl
dnl dnl # Return LDFLAGS to normal
dnl LDFLAGS=${LDFLAGS_SAVE};
fi

dnl # Final decisions on CGCODE
AC_SUBST(cgcode_lib)
AC_SUBST(cgcode)
AM_CONDITIONAL(BUILD_CGCODE, test x$cgcode = xcgcode)

dnl # ----------------------
dnl # HANDLE THE PMG LIBRARY
dnl # ----------------------

dnl # Check for forced build of PMG
pmg_lib="";
pmg="";
AC_MSG_CHECKING([whether you want force build of PMG lib])
AC_ARG_ENABLE(pmgforce,
    [  --enable-pmgforce       force building of PMG library [default=no]],
    [ pmg="pmg" ],
    [ pmg="" ],
)

dnl # Look for PMG if required
if test -n "${pmg}"; then
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no])
dnl AC_MSG_RESULT([no ...poking around])
dnl
dnl dnl # PMG library location ENV specification
dnl AC_MSG_CHECKING([whether your environment defines FETK_PMG_LIBRARY])
dnl if test -n "${FETK_PMG_LIBRARY}"; then
dnl     AC_MSG_RESULT([yes])
dnl     pmg_lib_path="-L${FETK_PMG_LIBRARY} ";
dnl else
dnl     AC_MSG_RESULT([no])
dnl     pmg_lib_path="-L${FETK_LIBRARY} ";
dnl fi
dnl
dnl dnl # Setup temp LDFLAGS and look for PMG library
dnl LDFLAGS_SAVE=${LDFLAGS};
dnl LDFLAGS=${pmg_lib_path};
dnl pmg_use="";
dnl AC_CHECK_LIB(pmg,buildg_,
dnl     [pmg_use="yes";pmg_lib="${pmg_lib_path}-lpmg"],
dnl     [pmg_use="";pmg_lib=""],
dnl     [${pmg_lib_path}-lpmg ${blas_lib} -lvf2c])
dnl if test -z "${pmg_use}"; then
dnl     AC_MSG_RESULT([** PMG library missing ...will BUILD **])
dnl     pmg="pmg";
dnl else
dnl     AC_MSG_RESULT([** PMG library found ...will USE **])
dnl     pmg="";
dnl fi
dnl
dnl dnl # Return LDFLAGS to normal
dnl LDFLAGS=${LDFLAGS_SAVE};
fi

dnl # Final decisions on PMG
AC_SUBST(pmg_lib)
AC_SUBST(pmg)
AM_CONDITIONAL(BUILD_PMG, test x$pmg = xpmg)

AC_MSG_RESULT([----------- end processing PUNC configure options ---------])

AC_MSG_RESULT([---------- begin configuring for MALOC linkage ------------])

dnl # ------------------------
dnl # HANDLE THE MALOC LIBRARY
dnl # ------------------------

dnl # MALOC header location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_INCLUDE])
if test -n "${FETK_INCLUDE}"; then
    AC_MSG_RESULT([yes])
    maloc_inc_path="-I${FETK_INCLUDE} ";
else
    AC_MSG_RESULT([no])
    maloc_inc_path="";
fi

dnl # MALOC library location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_LIBRARY])
if test -n "${FETK_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    maloc_lib_path="-L${FETK_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    maloc_lib_path="";
fi

dnl # Setup temp LDFLAGS and look for MALOC library/header
LDFLAGS_SAVE=${LDFLAGS};
CPPFLAGS_SAVE=${CPPFLAGS};
LDFLAGS=${maloc_lib_path};
CPPFLAGS=${maloc_inc_path};
maloc_found="";
AC_CHECK_HEADER(maloc/maloc.h,
    [maloc_found="yes";maloc_inc="${maloc_inc_path}"],
    [maloc_found="";maloc_inc=""])
if test -n "${maloc_found}"; then
    AC_CHECK_LIB(maloc,maloc_link,
        [maloc_found="yes";maloc_lib="${maloc_lib_path}-lmaloc"],
        [maloc_found="";maloc_lib=""],
        [${maloc_lib_path}-lmaloc ${rl_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${thread_lib} ${math_lib} ${zfence_lib} ${profile_lib}])
fi
if test -z "${maloc_found}"; then
    AC_MSG_ERROR([MALOC libraries OR headers missing ...EXITING ON ERROR])
else
    AC_MSG_RESULT([MALOC libraries AND headers were found ...rocking on...])
fi

dnl # Return LDFLAGS and CPPFLAGS to normal
LDFLAGS=${LDFLAGS_SAVE};
CPPFLAGS=${CPPFLAGS_SAVE};
AC_SUBST(maloc_lib)
AC_SUBST(maloc_inc)

dnl # Check whether MALOC actually needs the READLINE library
AC_CHECK_LIB(maloc,maloc_needs_rl,
    [rl_use="yes"],
    [rl_use=""],
    [${maloc_lib} ${rl_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${thread_lib} ${math_lib} ${zfence_lib} ${profile_lib}])

dnl # Check whether MALOC actually needs the MPI library
AC_CHECK_LIB(maloc,maloc_needs_mpi,
    [mpi_use="yes"],
    [mpi_use=""],
    [${maloc_lib} ${mpi_lib} ${rl_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${thread_lib} ${math_lib} ${zfence_lib} ${profile_lib}])

AC_MSG_RESULT([---------- end configuring for MALOC linkage --------------])

dnl ##########################################################################
dnl 11. templates
dnl ##########################################################################

AH_TEMPLATE([HAVE_CYGWIN],
            [Am I running in a Cygwin/Win32 environment?])

AH_TEMPLATE([HAVE_EMBED],
            [Does EMBED macro for embedding rcsid symbols into binaries work?])

AH_TEMPLATE([HAVE_DEBUG],
            [Do I compile as a debug version?])

AH_TOP([
/*
 * ***************************************************************************
 * PUNC = < Portable Understructure for Numerical Computing >
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
 * rcsid="INTENTIONALLY LEFT BLANK"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     acconfig.h
 *
 * Purpose:  Generates the main configuration header "punccf.h" for PUNC.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#ifndef _PUNCCF_H_
#define _PUNCCF_H_
])

AH_BOTTOM([
/*
 * ***************************************************************************
 * Undo the damage done by the autoconf tools
 * ***************************************************************************
 */
#undef HAVE_DLFCN_H
#undef HAVE_INTTYPES_H
#undef HAVE_MEMORY_H
#undef HAVE_STDINT_H
#undef HAVE_STDLIB_H
#undef HAVE_STRINGS_H
#undef HAVE_STRING_H
#undef HAVE_SYS_STAT_H
#undef HAVE_SYS_TYPES_H
#undef HAVE_UNISTD_H

/*  
 * ***************************************************************************
 * Define some RCS tag embedding and debug I/O macros
 * ***************************************************************************
 */

/* Embedded RCS tags ("ident filename" prints module versions in filename) */
#if defined(HAVE_EMBED)
#    define VEMBED(rctag) \
         VPRIVATE const char* rctag; \
         static void* use_rcsid=(0 ? &use_rcsid : (void*)&rcsid);
#else
#    define VEMBED(rctag)
#endif

/* Produce additional debugging I/O */
#if defined(HAVE_DEBUG)
#    define VDEBUGIO(str) fprintf(stderr,str)
#else
#    define VDEBUGIO(str)
#endif

#endif /* _PUNCCF_H_ */
])

dnl ##########################################################################
dnl 12. Test for doxygen and graphviz                                  
dnl ##########################################################################

cwd=`pwd`
cd ${srcdir}
TOPDIR=`pwd`
cd ${cwd}

AC_ARG_WITH(doxygen, [AC_HELP_STRING([--with-doxygen],[Doxygen path])],
                     with_doxygen=$withval, with_doxygen=no)

if test "$with_doxygen" = "no"; then
  AC_PATH_PROG(doxygen_path, doxygen)
  if test -z "${doxygen_path}"; then
    AC_MSG_WARN([Unable to find doxygen!])
  fi
else
  doxygen_path=$with_doxygen
fi

AC_ARG_WITH(dot, [AC_HELP_STRING([--with-dot],[Dot path])],
                  with_dot=$withval, with_dot=no)

if test "$with_dot" = "no"; then
  AC_PATH_PROG(dot_path, dot)
  if test -z "${dot_path}"; then
    AC_MSG_WARN([Unable to find dot!])
  fi
else
  dot_path=$with_dot
fi

if test "$dot_path" = ""; then
  sed -e 's%@have_dot@%'NO'%' $TOPDIR/doc/doxygen/punc.dox.in > $TOPDIR/doc/doxygen/punc.dox.in.temp
  sed -e 's%@dot_path@%''%' $TOPDIR/doc/doxygen/punc.dox.in.temp > $TOPDIR/doc/doxygen/punc.dox.in.temp.2
else
  sed -e 's%@have_dot@%'YES'%' $TOPDIR/doc/doxygen/punc.dox.in > $TOPDIR/doc/doxygen/punc.dox.in.temp
  sed -e 's%@dot_path@%'${dot_path}'%' $TOPDIR/doc/doxygen/punc.dox.in.temp > $TOPDIR/doc/doxygen/punc.dox.in.temp.2
fi

sed -e 's%@topdir@%'${TOPDIR}'%' $TOPDIR/doc/doxygen/punc.dox.in.temp.2 > $TOPDIR/doc/doxygen/punc.dox
rm -f $TOPDIR/doc/doxygen/punc.dox.in.temp*

AM_CONDITIONAL(MAKE_DOC, test "$doxygen_path" != "")
AC_SUBST(MAKE_DOC)
AC_SUBST(doxygen_path)

dnl ##########################################################################
dnl 13. generate the makefiles
dnl ##########################################################################

AC_OUTPUT([
    Makefile
    src/Makefile

    src/base/Makefile

    src/vf2c/Makefile
    src/blas/Makefile
    src/lapack/Makefile
    src/amd/Makefile
    src/umfpack/Makefile
    src/superlu/Makefile
    src/arpack/Makefile
    src/cgcode/Makefile
    src/pmg/Makefile

    src/aaa_inc/Makefile
    src/aaa_inc/punc/Makefile

    src/aaa_lib/Makefile

    doc/Makefile
    doc/doxygen/Makefile
])

