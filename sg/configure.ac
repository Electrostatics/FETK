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
dnl rcsid="INTENTIONALLY LEFT BLANK"
dnl ##########################################################################

dnl ##########################################################################
dnl File:    configure.ac
dnl
dnl Purpose: configure.ac script for SG (Socket Graphics).
dnl
dnl Author:  Michael Holst
dnl ##########################################################################

dnl 0. autoconf initialization
AC_INIT(sg, 1.0, mholst@math.ucsd.edu)
AC_CONFIG_SRCDIR(src/ogl/sg/ogl.h)
AM_CONFIG_HEADER(src/aaa_inc/sgcf.h)
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
    AC_DEFINE(HAVE_X11)
    x_lib_base="-lXaw -lXmu -lXi -lXt -lXext -lX11"
    x_lib="${x_lib_path} ${X_LIBS} ${X_EXTRA_LIBS} ${X_PRE_LIBS} ${x_lib_base}"
else
    x_lib=""
fi
AC_SUBST(x_lib)

AC_MSG_RESULT([----------- begin processing SG configure options ---------])

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

dnl # ------------------------
dnl # HANDLE THE MOTIF LIBRARY
dnl # ------------------------

dnl # Check for forced build of Motif
motif_inc="";
motif_lib="";
motif_use="";
AC_MSG_CHECKING([whether you want to disable Motif])
AC_ARG_ENABLE(motif,
    [  --disable-motif         disable motif [default=no]],
    [ motif_use="" ],
    [ motif_use="yes" ],
)

dnl # Look for Motif if required
if test -z "${motif_use}"; then
    AC_MSG_RESULT([yes -- Motif DISABLED])
    motif_use="";
elif test -n "${no_x}"; then
    AC_MSG_RESULT([no ...poking around])
    AC_MSG_RESULT([You do not have X...Motif DISABLED])
    motif_use="";
else
    AC_MSG_RESULT([no ...poking around])
    motif_use="";

    dnl # Motif header location ENV specification
    AC_MSG_CHECKING([whether your environment defines FETK_MOTIF_INCLUDE])
    if test -n "${FETK_MOTIF_INCLUDE}"; then
        AC_MSG_RESULT([yes])
        motif_inc_path="-I${FETK_MOTIF_INCLUDE} ";
    else
        AC_MSG_RESULT([no])
        AC_MSG_CHECKING([whether your environment defines FETK_INCLUDE])
        if test -n "${FETK_INCLUDE}"; then
            AC_MSG_RESULT([yes])
            motif_inc_path="-I${FETK_INCLUDE} ";
        else
            AC_MSG_RESULT([no])
            motif_inc_path="";
        fi
    fi

    dnl # Motif library location ENV specification
    AC_MSG_CHECKING([whether your environment defines FETK_MOTIF_LIBRARY])
    if test -n "${FETK_MOTIF_LIBRARY}"; then
        AC_MSG_RESULT([yes])
        motif_lib_path="-L${FETK_MOTIF_LIBRARY} ";
    else
        AC_MSG_RESULT([no])
        AC_MSG_CHECKING([whether your environment defines FETK_LIBRARY])
        if test -n "${FETK_LIBRARY}"; then
            AC_MSG_RESULT([yes])
            motif_lib_path="-L${FETK_LIBRARY} ";
        else
            AC_MSG_RESULT([no])
            motif_lib_path="";
        fi
    fi

    dnl # Setup temp LDFLAGS and CPPFLAGS and look for Motif library and headers
    LDFLAGS_SAVE=${LDFLAGS};
    CPPFLAGS_SAVE=${CPPFLAGS};
    LDFLAGS=${motif_lib_path};
    CPPFLAGS=${motif_inc_path};
    motif_use="";
    AC_CHECK_HEADER(Xm/Xm.h,
        [motif_use="yes";motif_inc="${motif_inc_path}"],
        [motif_use="";motif_inc=""])
    if test -n "${motif_use}"; then
        AC_CHECK_LIB(Xm,XmGetColors,
            [motif_use="yes";motif_lib="${motif_lib_path}-lXm"],
            [motif_use="";motif_lib=""],
            [${motif_lib_path}-lXm ${x_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${objc_lib} ${math_lib}])
    fi
    if test -z "${motif_use}"; then
        AC_MSG_RESULT([** Motif library OR header missing ...Motif DISABLED **])
    else
        AC_MSG_RESULT([** Motif library AND header found ...will USE **])
        AC_DEFINE(HAVE_MOTIF)
    fi

    dnl # Return LDFLAGS and CPPFLAGS to normal
    LDFLAGS=${LDFLAGS_SAVE};
    CPPFLAGS=${CPPFLAGS_SAVE};
fi

dnl # Final decisions on Motif
AC_SUBST(motif_inc)
AC_SUBST(motif_lib)
AM_CONDITIONAL(EXISTS_MOTIF, test x$motif_use = xyes)

dnl # ---------------------
dnl # HANDLE THE GL LIBRARY
dnl # ---------------------

dnl # Check for forced build of GL
gl_inc="";
gl_lib="";
gl="";
AC_MSG_CHECKING([whether you want force build of GL lib])
AC_ARG_ENABLE(glforce,
    [  --enable-glforce        force building of GL library [default=no]],
    [ gl="gl" ],
    [ gl="" ],
)

dnl # Look for GL if required
if test -n "${gl}"; then
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no ...poking around])

    dnl # GL header location ENV specification
    AC_MSG_CHECKING([whether your environment defines FETK_GL_INCLUDE])
    if test -n "${FETK_GL_INCLUDE}"; then
        AC_MSG_RESULT([yes])
        gl_inc_path="-I${FETK_GL_INCLUDE} ";
    else
        AC_MSG_RESULT([no])
        gl_inc_path="";
    fi
    if test -n "${FETK_INCLUDE}"; then
        gl_inc_path="${gl_inc_path} -I${FETK_INCLUDE} ";
    fi

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

    dnl # Setup temp LDFLAGS and CPPFLAGS and look for GL library/headers
    LDFLAGS_SAVE=${LDFLAGS};
    CPPFLAGS_SAVE=${CPPFLAGS};
    LDFLAGS=${gl_lib_path};
    CPPFLAGS=${gl_inc_path};
    gl_use="";
    AC_CHECK_HEADER(GL/gl.h,
        [gl_use="yes";gl_inc="${gl_inc_path}"],
        [gl_use="";gl_inc=""])
    if test -n "${gl_use}"; then
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
    fi
    if test -z "${gl_use}"; then
        AC_MSG_RESULT([** GL library OR header missing ...will BUILD **])
        gl="gl";
    else
        AC_MSG_RESULT([** GL library AND header found ...will USE **])
        gl="";
    fi

    dnl # Return LDFLAGS and CPPFLAGS to normal
    LDFLAGS=${LDFLAGS_SAVE};
    CPPFLAGS=${CPPFLAGS_SAVE};
fi

dnl # Final decisions on GL
AC_SUBST(gl_inc)
AC_SUBST(gl_lib)
AC_SUBST(gl)
AM_CONDITIONAL(BUILD_GL, test x$gl = xgl)

dnl # ----------------------
dnl # HANDLE THE GLU LIBRARY
dnl # ----------------------

dnl # Check for forced build of GLU
glu_inc="";
glu_lib="";
glu="";
AC_MSG_CHECKING([whether you want force build of GLU lib])
AC_ARG_ENABLE(gluforce,
    [  --enable-gluforce       force building of GLU library [default=no]],
    [ glu="glu" ],
    [ glu="" ],
)

dnl # Look for GLU if required
if test -n "${glu}"; then
    AC_MSG_RESULT([yes])
else
    AC_MSG_RESULT([no ...poking around])

    dnl # GLU header location ENV specification
    AC_MSG_CHECKING([whether your environment defines FETK_GLU_INCLUDE])
    if test -n "${FETK_GLU_INCLUDE}"; then
        AC_MSG_RESULT([yes])
        glu_inc_path="-I${FETK_GLU_INCLUDE} ";
    else
        AC_MSG_RESULT([no])
        glu_inc_path="";
    fi
    if test -n "${FETK_INCLUDE}"; then
        glu_inc_path="${glu_inc_path} -I${FETK_INCLUDE} ";
    fi

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

    dnl # Setup temp LDFLAGS and CPPFLAGS and look for GLU library/headers
    LDFLAGS_SAVE=${LDFLAGS};
    CPPFLAGS_SAVE=${CPPFLAGS};
    LDFLAGS=${glu_lib_path};
    CPPFLAGS=${glu_inc_path};
    glu_use="";
    AC_CHECK_HEADER(GL/glu.h,
        [glu_use="yes";glu_inc="${glu_inc_path}"],
        [glu_use="";glu_inc=""])
    if test -n "${glu_use}"; then
        AC_CHECK_LIB(GLU,gluLookAt,
            [glu_use="yes";glu_lib="${glu_lib_path}-lGLU"],
            [glu_use="";glu_lib=""],
            [${glu_lib_path}-lGLU ${gl_lib} ${motif_lib} ${x_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${objc_lib} ${math_lib}])
    fi
    if test -z "${glu_use}"; then
        AC_MSG_RESULT([** GLU library OR header missing ...will BUILD **])
        glu="glu";
    else
        AC_MSG_RESULT([** GLU library AND header found ...will USE **])
        glu="";
    fi

    dnl # Return LDFLAGS and CPPFLAGS to normal
    LDFLAGS=${LDFLAGS_SAVE};
    CPPFLAGS=${CPPFLAGS_SAVE};
fi

dnl # Final decisions on GLU
AC_SUBST(glu_inc)
AC_SUBST(glu_lib)
AC_SUBST(glu)
AM_CONDITIONAL(BUILD_GLU, test x$glu = xglu)

dnl # ----------------------
dnl # HANDLE THE GLW LIBRARY
dnl # ----------------------

dnl # Check for forced build of GLw
glw_inc="";
glw_lib="";
glw="";
AC_MSG_CHECKING([whether you want force build of GLw lib])
AC_ARG_ENABLE(glwforce,
    [  --enable-glwforce       force building of GLw library [default=no]],
    [ glw="glw" ],
    [ glw="" ],
)

dnl # Look for GLw if required
if test -n "${glw}"; then
    AC_MSG_RESULT([yes])
    if test -n "${no_x}"; then
        AC_MSG_RESULT([You do not have X...GLw DISABLED])
        glw=""
    fi
elif test -n "${no_x}"; then
    AC_MSG_RESULT([no ...poking around])
    AC_MSG_RESULT([You do not have X...GLw DISABLED])
    glw=""
else
    AC_MSG_RESULT([no ...poking around])

    dnl # GLw header location ENV specification
    AC_MSG_CHECKING([whether your environment defines FETK_GLW_INCLUDE])
    if test -n "${FETK_GLW_INCLUDE}"; then
        AC_MSG_RESULT([yes])
        glw_inc_path="-I${FETK_GLW_INCLUDE} ";
    else
        AC_MSG_RESULT([no])
        glw_inc_path="";
    fi
    if test -n "${FETK_INCLUDE}"; then
        glw_inc_path="${glw_inc_path} -I${FETK_INCLUDE} ";
    fi

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

    dnl # Setup temp LDFLAGS and CPPFLAGS and look for GLw library/headers
    LDFLAGS_SAVE=${LDFLAGS};
    CPPFLAGS_SAVE=${CPPFLAGS};
    LDFLAGS=${glw_lib_path};
    CPPFLAGS=${glw_inc_path};
    glw_use="";
    AC_CHECK_HEADER(GL/GLwDrawA.h,
        [glw_use="yes";glw_inc="${glw_inc_path}"],
        [glw_use="";glw_inc=""])
    if test -z "${glw_use}"; then
        AC_CHECK_HEADER(GLw/GLwDrawA.h,
            [glw_use="yes";glw_inc="${glw_inc_path}"],
            [glw_use="";glw_inc=""])
    fi
    if test -n "${glw_use}"; then
        AC_CHECK_LIB(GLw,GLwDrawingAreaSwapBuffers,
            [glw_use="yes";glw_lib="${glw_lib_path}-lGLw"],
            [glw_use="";glw_lib=""],
            [${glw_lib_path}-lGLw ${glu_lib} ${gl_lib} ${motif_lib} ${x_lib} ${liberty_lib} ${socket_lib} ${nsl_lib} ${objc_lib} ${math_lib}])
    fi
    if test -z "${glw_use}"; then
        AC_MSG_RESULT([** GLw library OR header missing ...will BUILD **])
        glw="glw";
    else
        AC_MSG_RESULT([** GLw library AND header found ...will USE **])
        glw="";
    fi

    dnl # Return LDFLAGS and CPPFLAGS to normal
    LDFLAGS=${LDFLAGS_SAVE};
    CPPFLAGS=${CPPFLAGS_SAVE};
fi

dnl # Final decisions on GLW
AC_SUBST(glw_inc)
AC_SUBST(glw_lib)
AC_SUBST(glw)
AM_CONDITIONAL(BUILD_GLW, test x$glw = xglw)

AC_MSG_RESULT([------------ end processing SG configure options ----------])

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
    maloc_inc_path="-I${HOME}/include ";
fi

dnl # MALOC library location ENV specification
AC_MSG_CHECKING([whether your environment defines FETK_LIBRARY])
if test -n "${FETK_LIBRARY}"; then
    AC_MSG_RESULT([yes])
    maloc_lib_path="-L${FETK_LIBRARY} ";
else
    AC_MSG_RESULT([no])
    maloc_lib_path="-L${HOME}/lib ";
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

dnl ##########################################################################
dnl 11. templates
dnl ##########################################################################

AH_TEMPLATE([HAVE_CYGWIN],
            [Am I running in a Cygwin/Win32 environment?])

AH_TEMPLATE([HAVE_EMBED],
            [Does EMBED macro for embedding rcsid symbols into binaries work?])

AH_TEMPLATE([HAVE_DEBUG],
            [Do I compile as a debug version?])

AH_TEMPLATE([HAVE_X11],
            [Do I have X?])

AH_TEMPLATE([HAVE_MOTIF],
            [Do I have Motif?])

AH_TOP([
/*
 * ***************************************************************************
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
 * rcsid="INTENTIONALLY LEFT BLANK"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     acconfig.h
 *
 * Purpose:  Generates the main configuration header "sgcf.h" for SG.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#ifndef _SGCF_H_
#define _SGCF_H_
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
 * Handle some additional window system and graphics things manually
 * ***************************************************************************
 */

#if defined(WIN32) || defined(__WATCOMC__)
#   define HAVE_WIN32
#   define POLYGON_OFFSET_MISSING 1
#endif

#if defined(NeXT) || defined(__NeXT__)
#   define HAVE_NEXT
#endif

#if !defined(POLYGON_OFFSET_MISSING)
#   define HAVE_POLYGON_OFFSET
#endif

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

#endif /* _SGCF_H_ */
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
  sed -e 's%@have_dot@%'NO'%' $TOPDIR/doc/doxygen/sg.dox.in > $TOPDIR/doc/doxygen/sg.dox.in.temp
  sed -e 's%@dot_path@%''%' $TOPDIR/doc/doxygen/sg.dox.in.temp > $TOPDIR/doc/doxygen/sg.dox.in.temp.2
else
  sed -e 's%@have_dot@%'YES'%' $TOPDIR/doc/doxygen/sg.dox.in > $TOPDIR/doc/doxygen/sg.dox.in.temp
  sed -e 's%@dot_path@%'${dot_path}'%' $TOPDIR/doc/doxygen/sg.dox.in.temp > $TOPDIR/doc/doxygen/sg.dox.in.temp.2
fi

sed -e 's%@topdir@%'${TOPDIR}'%' $TOPDIR/doc/doxygen/sg.dox.in.temp.2 > $TOPDIR/doc/doxygen/sg.dox
rm -f $TOPDIR/doc/doxygen/sg.dox.in.temp*

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

    src/gl/Makefile
    src/glu/Makefile
    src/glw/Makefile
    src/ogl/Makefile
    src/vgl/Makefile

    src/aaa_inc/Makefile
    src/aaa_inc/sg/Makefile
    src/aaa_inc/GL/Makefile

    src/aaa_lib/Makefile

    doc/Makefile
    doc/doxygen/Makefile 
])

