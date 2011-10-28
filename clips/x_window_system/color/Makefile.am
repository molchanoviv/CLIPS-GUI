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
METASOURCES = AUTO

INCLUDES = -I$(top_srcdir)/clips $(PACKAGE_CFLAGS)

bin_PROGRAMS = xclips-color

xclips_color_LDADD =                               \
	-lXaw -lXmu -lXt -lXext -lX11 -lm    \
	$(top_builddir)/clips/libclips.la \
	$(PACKAGE_LIBS)

xclips_color_SOURCES = \
	color.c

noinst_HEADERS = \
	colors.h xdefault.h
