#############################################################################
##   Copyright (C) 2004 by Rick L. Vinyard, Jr.                            ##
##   rvinyard@cs.nmsu.edu                                                  ##
##                                                                         ##
##   This program is free software; you can redistribute it and/or modify  ##
##   it under the terms of the GNU General Public License as               ##
##   published by the Free Software Foundation version 2.                  ##
##                                                                         ##
##   This program is distributed in the hope that it will be useful,       ##
##   but WITHOUT ANY WARRANTY; without even the implied warranty of        ##
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         ##
##   GNU General Public License for more details.                          ##
##                                                                         ##
##   You should have received a copy of the GNU General Public             ##
##   License along with this library; if not, write to the                 ##
##   Free Software Foundation, Inc.,                                       ##
##   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA              ##
#############################################################################

#########################################################################
#  package specific values
#########################################################################
pushdef([PACKAGE_MAJOR_VERSION], [6])
pushdef([PACKAGE_MINOR_VERSION], [30])
pushdef([PACKAGE_MICRO_VERSION], [0.20090722svn])
pushdef([PKG_VERSION], PACKAGE_MAJOR_VERSION.PACKAGE_MINOR_VERSION.PACKAGE_MICRO_VERSION)

AC_INIT([clips], PKG_VERSION, [rvinyard@cs.nmsu.edu])

[PACKAGE_MAJOR_VERSION]=PACKAGE_MAJOR_VERSION
[PACKAGE_MINOR_VERSION]=PACKAGE_MINOR_VERSION
[PACKAGE_MICRO_VERSION]=PACKAGE_MICRO_VERSION

popdef([PACKAGE_MAJOR_VERSION])
popdef([PACKAGE_MINOR_VERSION])
popdef([PACKAGE_MICRO_VERSION])
popdef([PKG_VERSION])

#
# +1 :  ? : +1 == new interface that does not break old one
# +1 :  ? :  0 == new interface that breaks old one
#  ? :  ? :  0 == no new interfaces, but breaks apps
#  ? : +1 :  ? == just some internal changes, nothing breaks but might work better
# CURRENT : REVISION : AGE
LIBTOOL_SO_VERSION=2:0:0

PKGCONFIG_RELEASE=6

#########################################################################
#  don't touch this
#########################################################################
PACKAGE_RELEASE=$PACKAGE_MAJOR_VERSION.$PACKAGE_MINOR_VERSION
AC_SUBST(PACKAGE_RELEASE)

AC_DEFUN([EXPAND_DIR], [
  $1=$2
  $1=`(
        test "x$prefix" = xNONE && prefix="$ac_default_prefix"
        test "x$exec_prefix" = xNONE && exec_prefix="${prefix}"
        eval echo \""[$]$1"\"
      )`
  ])

EXPAND_DIR( helpdir, "$datadir/$PACKAGE_NAME")
AC_SUBST(helpdir)

AC_DEFINE_UNQUOTED( CLIPS_HELPFILE, "${helpdir}/clips.hlp", [CLIPS help file] )
CLIPS_HELPFILE="${helpdir}/clips.hlp"
AC_SUBST(CLIPS_HELPFILE)

AC_SUBST(LIBTOOL_SO_VERSION)

AC_DEFINE_UNQUOTED(PACKAGE_MAJOR_VERSION, $PACKAGE_MAJOR_VERSION, [Major version])
AC_DEFINE_UNQUOTED(PACKAGE_MINOR_VERSION, $PACKAGE_MINOR_VERSION, [Minor version])
AC_DEFINE_UNQUOTED(PACKAGE_MICRO_VERSION, $PACKAGE_MICRO_VERSION, [Micro version])
AC_SUBST(PACKAGE_MAJOR_VERSION)
AC_SUBST(PACKAGE_MINOR_VERSION)
AC_SUBST(PACKAGE_MICRO_VERSION)

AC_SUBST(PKGCONFIG_RELEASE)

AM_INIT_AUTOMAKE([1.9 tar-ustar dist-bzip2 dist-zip])
AM_CONFIG_HEADER(config.h)
AC_CONFIG_MACRO_DIR([m4])

AC_LANG_CPLUSPLUS
AC_PROG_CXX
AC_PROG_INSTALL

for top_builddir in . .. ../.. $ac_auxdir $ac_auxdir/..; do
test -f $top_builddir/configure && break
done
AC_PROG_LIBTOOL

AC_CHECK_LIB(m, pow)
AC_CHECK_LIB(ncurses, tputs)
AC_CHECK_LIB(ncurses, tgoto)
AC_CHECK_LIB(ncurses, tgetent)
AC_CHECK_LIB(ncurses, tgetstr)
AC_CHECK_LIB(rt, clock_gettime)
AC_CHECK_LIB(termcap, PC)
AC_CHECK_LIB(termcap, UP)

AC_OUTPUT(clips-6.pc clips/clips-config.h Makefile clips/Makefile \
	x_window_system/Makefile x_window_system/xinterface/Makefile \
	x_window_system/color/Makefile documentation/Makefile)

