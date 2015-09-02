dnl ##########################################################################
dnl SG = < Socket Graphics >
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
dnl rcsid="$Id: configure.ac,v 1.42 2010/12/08 07:30:51 fetk Exp $"
dnl ##########################################################################

dnl ##########################################################################
dnl File:    configure.ac
dnl
dnl Purpose: configure.ac script for a typical SG application.
dnl
dnl Author:  Michael Holst
dnl ##########################################################################

dnl 0. autoconf initialization
AC_INIT(sgapp, 1.0, mholst@math.ucsd.edu)
AC_CONFIG_SRCDIR(main.c)
AC_CONFIG_AUX_DIR(config)
AC_PREFIX_DEFAULT(${HOME})
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

dnl 1. automake initialization (uncomment only if rebuilding Makefile.in's)
AM_INIT_AUTOMAKE([foreign])
FETK_VERSION="1:0:0"
AC_SUBST(FETK_VERSION)
AM_MAINTAINER_MODE

dnl 2. checks for programs
AC_LANG_C
AC_PROG_CC
AC_PROG_CPP

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

dnl # ------------------
dnl # HANDLE OBJECTIVE-C
dnl # ------------------
AC_MSG_CHECKING([whether this is an OPENSTEP/NeXTSTEP/MacOS machine])
if test "${host_os}" = "openstep4"; then
    AC_MSG_RESULT([yes])
    objc_lib="-framework AppKit -Xlinker -read_only_relocs -Xlinker suppress";
else
    AC_MSG_RESULT([no])
    objc_lib="";
fi
AC_SUBST(objc_lib)

dnl # ----------------------
dnl # HANDLE THE X LIBRARIES
dnl # ----------------------
AC_MSG_CHECKING([whether your environment defines FETK_X_LIBRARY])
if test -n "${FETK_X_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    x_lib_path="-L${FETK_X_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    x_lib_path="";
fi
AC_PATH_X
AC_PATH_XTRA
if test -z "${no_x}"; then
    x_lib_base="-lXaw -lXmu -lXi -lXt -lXext -lX11"
    x_lib="${x_lib_path} ${X_LIBS} ${X_EXTRA_LIBS} ${X_PRE_LIBS} ${x_lib_base}"
else
    x_lib=""
fi
AC_SUBST(x_lib)

AC_MSG_RESULT([---------- begin processing APP configure options ----------])

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

dnl # ------------------------
dnl # HANDLE THE MOTIF LIBRARY
dnl # ------------------------
dnl # Motif library location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_MOTIF_LIBRARY])
if test -n "${FETK_MOTIF_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    motif_lib_path="-L${FETK_MOTIF_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    motif_lib_path="";
fi
dnl # Motif library check
motif_lib=""
motif_use="";
if test -n "${no_x}"; then
    AC_MSG_RESULT([** You do not have X ...Motif DISABLED **])
else
    dnl # Setup temp LDFLAGS and look for Motif library
    LDFLAGS_SAVE=${LDFLAGS};
    LDFLAGS=${motif_lib_path};
    AC_CHECK_LIB(Xm,XmGetColors,
        [motif_use="yes";motif_lib="${motif_lib_path}-lXm"],
        [motif_use="";motif_lib=""],
        [${motif_lib_path}-lXm ${x_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${objc_lib} ${math_lib}])
    dnl # Return LDFLAGS to normal
    LDFLAGS=${LDFLAGS_SAVE};
fi
AC_SUBST(motif_lib)
AM_CONDITIONAL(EXISTS_MOTIF, test x$motif_use = xyes)

dnl # Final Motif check
if test -z "${no_x}"; then
    if test -z "${motif_use}"; then
        AC_MSG_RESULT([Motif library missing but not required ...rocking on...])
    fi
fi

dnl # ---------------------
dnl # HANDLE THE GL LIBRARY
dnl # ---------------------
dnl # GL library location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_GL_LIBRARY])
if test -n "${FETK_GL_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    gl_lib_path="-L${FETK_GL_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    gl_lib_path="";
fi
if test -n "${FETK_LIBRARY}"; then
    gl_lib_path="${gl_lib_path} -L${FETK_LIBRARY} ";
fi

dnl # Setup temp LDFLAGS and look for GL library
LDFLAGS_SAVE=${LDFLAGS};
LDFLAGS=${gl_lib_path};
gl_lib="";
gl_use="";
AC_MSG_CHECKING([whether you need the MacOSX hack for OpenGL])
if test "${host_vendor}" == "apple"; then
    AC_MSG_RESULT([yes])
    gl_lib_hack="-Wl,-dylib_file,/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib:/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib"
else
    AC_MSG_RESULT([no])
    gl_lib_hack="";
fi
AC_CHECK_LIB(GL,glPushMatrix,
    [gl_use="yes";gl_lib="${gl_lib_path}-lGL ${gl_lib_hack}"],
    [gl_use="";gl_lib=""],
    [${gl_lib_path}-lGL ${gl_lib_hack} ${motif_lib} ${x_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${objc_lib} ${math_lib}])

dnl # Return LDFLAGS to normal
LDFLAGS=${LDFLAGS_SAVE};
AC_SUBST(gl_lib)

dnl # Final GL check
if test -z "${gl_use}"; then
    AC_MSG_ERROR([GL library missing but REQUIRED...EXITING ON ERROR])
fi

dnl # ----------------------
dnl # HANDLE THE GLU LIBRARY
dnl # ----------------------
dnl # GLU library location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_GLU_LIBRARY])
if test -n "${FETK_GLU_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    glu_lib_path="-L${FETK_GLU_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    glu_lib_path="";
fi
if test -n "${FETK_LIBRARY}"; then
    glu_lib_path="${glu_lib_path} -L${FETK_LIBRARY} ";
fi

dnl # Setup temp LDFLAGS and look for GLU library
LDFLAGS_SAVE=${LDFLAGS};
LDFLAGS=${glu_lib_path};
glu_use="";
AC_CHECK_LIB(GLU,gluLookAt,
    [glu_use="yes";glu_lib="${glu_lib_path}-lGLU"],
    [glu_use="";glu_lib=""],
    [${glu_lib_path}-lGLU ${gl_lib} ${motif_lib} ${x_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${objc_lib} ${math_lib}])

dnl # Return LDFLAGS to normal
LDFLAGS=${LDFLAGS_SAVE};
AC_SUBST(glu_lib)

dnl # Final GLU check
if test -z "${glu_use}"; then
    AC_MSG_ERROR([GLU library missing but REQUIRED...EXITING ON ERROR])
fi

dnl # ----------------------
dnl # HANDLE THE GLW LIBRARY
dnl # ----------------------
dnl # GLw library location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_GLW_LIBRARY])
if test -n "${FETK_GLW_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    glw_lib_path="-L${FETK_GLW_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    glw_lib_path="";
fi
if test -n "${FETK_LIBRARY}"; then
    glw_lib_path="${glw_lib_path} -L${FETK_LIBRARY} ";
fi

dnl # GLw library check
glw_lib=""
glw_use="";
if test -n "${no_x}"; then
    AC_MSG_RESULT([** You do not have X ...GLw DISABLED **])
else
    dnl # Setup temp LDFLAGS and look for GLw library
    LDFLAGS_SAVE=${LDFLAGS};
    LDFLAGS=${glw_lib_path};
    AC_CHECK_LIB(GLw,GLwDrawingAreaSwapBuffers,
        [glw_use="yes";glw_lib="${glw_lib_path}-lGLw"],
        [glw_use="";glw_lib=""],
        [${glw_lib_path}-lGLw ${glu_lib} ${gl_lib} ${motif_lib} ${x_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${objc_lib} ${math_lib}])
    dnl # Return LDFLAGS to normal
    LDFLAGS=${LDFLAGS_SAVE};
fi
AC_SUBST(glw_lib)

dnl # Final GLw check
if test -z "${no_x}"; then
    if test -z "${glw_lib}"; then
        AC_MSG_ERROR([GLw library missing but REQUIRED...EXITING ON ERROR])
    fi
fi

dnl # -----------------------------
dnl # HANDLE BUILDING LIBRARY TESTS
dnl # -----------------------------
AC_MSG_CHECKING([whether you want to build library test programs])
AC_ARG_ENABLE(vtst,
    [  --enable-vtst           enable building of library tests [default=no]],
    [ vtst="tests";AC_MSG_RESULT([yes]) ],
    [ vtst="";AC_MSG_RESULT([no]) ]
)
AC_SUBST(vtst)

AC_MSG_RESULT([------------ end processing APP configure options ----------])

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

AC_MSG_RESULT([---------- end configuring for MALOC linkage --------------])

AC_MSG_RESULT([---------- begin configuring for SG linkage ---------------])

dnl # -----------------------
dnl # HANDLE THE SG LIBRARIES
dnl # -----------------------
dnl # SG header location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_INCLUDE])
if test -n "${FETK_INCLUDE}"; then
    AC_MSG_RESULT([yes])
    sg_inc_path="-I${FETK_INCLUDE} ";
else
    AC_MSG_RESULT([no])
    sg_inc_path="";
fi

dnl # SG library location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_LIBRARY])
if test -n "${FETK_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    sg_lib_path="-L${FETK_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    sg_lib_path="";
fi

dnl # Setup temp LDFLAGS and look for SG library/header
LDFLAGS_SAVE=${LDFLAGS};
CPPFLAGS_SAVE=${CPPFLAGS};
LDFLAGS=${sg_lib_path};
CPPFLAGS=${sg_inc_path};
sg_found="";
AC_CHECK_HEADER(sg/sg.h,
    [sg_found="yes";sg_inc="${sg_inc_path}"],
    [sg_found="";sg_inc=""])
if test -n "${sg_found}"; then
    AC_CHECK_LIB(sg,sg_link,
        [sg_found="yes";sg_lib="${sg_lib_path}-lsg"],
        [sg_found="";sg_lib=""],
        [${sg_lib_path}-lsg ${maloc_lib} ${glw_lib} ${glu_lib} ${gl_lib} ${motif_lib} ${x_lib} ${rl_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${thread_lib} ${objc_lib} ${math_lib} ${zfence_lib} ${profile_lib}])
fi
if test -z "${sg_found}"; then
    AC_MSG_ERROR([SG libraries OR headers missing ...EXITING ON ERROR])
else
    AC_MSG_RESULT([SG libraries AND headers were found ...rocking on...])
fi

dnl # Return LDFLAGS and CPPFLAGS to normal
LDFLAGS=${LDFLAGS_SAVE};
CPPFLAGS=${CPPFLAGS_SAVE};
AC_SUBST(sg_lib)
AC_SUBST(sg_inc)

AC_MSG_RESULT([---------- end processing SG configure options ----------])

dnl 11. generate the makefiles
AC_OUTPUT([
    Makefile
    tests/Makefile
    tests/gl/Makefile
    tests/glu/Makefile
    tests/glw/Makefile
])

