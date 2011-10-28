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
ACLOCAL_AMFLAGS = -I m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = clips-6.pc

EXTRA_DIST = COPYING_CLIPS_LINUX README_CLIPS_LINUX \
	examples/animal.clp    examples/dilemma2.clp  examples/wine.clp					\
	examples/auto.clp      examples/dilemma3.clp  examples/wordgame.clp				\
	examples/dilemma1.clp  examples/mab.clp       examples/zebra.clp				\
	examples/circuit/circuit1.clp  examples/circuit/circuit3.clp					\
	examples/circuit/circuit2.clp  examples/circuit/electrnc.clp					\
	examples/manners/manners128.bat  examples/manners/manners32.bat  examples/manners/manners8.bat	\
	examples/manners/manners128.fct  examples/manners/manners32.fct  examples/manners/manners8.fct	\
	examples/manners/manners16.bat   examples/manners/manners64.bat  examples/manners/manners.clp	\
	examples/manners/manners16.fct   examples/manners/manners64.fct					\
	examples/sudoku/how_to_use.txt     examples/sudoku/output-simple.clp  examples/sudoku/sudoku.clp	\
	examples/sudoku/output-frills.clp  examples/sudoku/runbench.bat				\
	examples/sudoku/output-none.clp    examples/sudoku/solve.clp				\
	examples/sudoku/puzzles/grid2x2-p1.clp   examples/sudoku/puzzles/grid3x3-p8.clp		\
	examples/sudoku/puzzles/grid3x3-p10.clp  examples/sudoku/puzzles/grid3x3-p9.clp		\
	examples/sudoku/puzzles/grid3x3-p11.clp  examples/sudoku/puzzles/grid4x4-p10.clp	\
	examples/sudoku/puzzles/grid3x3-p12.clp  examples/sudoku/puzzles/grid4x4-p13.clp	\
	examples/sudoku/puzzles/grid3x3-p13.clp  examples/sudoku/puzzles/grid4x4-p17.clp	\
	examples/sudoku/puzzles/grid3x3-p14.clp  examples/sudoku/puzzles/grid4x4-p1.clp		\
	examples/sudoku/puzzles/grid3x3-p15.clp  examples/sudoku/puzzles/grid4x4-p3.clp		\
	examples/sudoku/puzzles/grid3x3-p16.clp  examples/sudoku/puzzles/grid4x4-p4.clp		\
	examples/sudoku/puzzles/grid3x3-p17.clp  examples/sudoku/puzzles/grid4x4-p8.clp		\
	examples/sudoku/puzzles/grid3x3-p18.clp  examples/sudoku/puzzles/grid4x4-p9.clp		\
	examples/sudoku/puzzles/grid3x3-p1.clp   examples/sudoku/puzzles/grid5x5-p11.clp	\
	examples/sudoku/puzzles/grid3x3-p2.clp   examples/sudoku/puzzles/grid5x5-p1.clp		\
	examples/sudoku/puzzles/grid3x3-p3.clp   examples/sudoku/puzzles/grid5x5-p3.clp		\
	examples/sudoku/puzzles/grid3x3-p4.clp   examples/sudoku/puzzles/grid5x5-p4.clp		\
	examples/sudoku/puzzles/grid3x3-p5.clp   examples/sudoku/puzzles/grid5x5-p6.clp		\
	examples/sudoku/puzzles/grid3x3-p6.clp   examples/sudoku/puzzles/grid5x5-p9.clp		\
	examples/sudoku/puzzles/grid3x3-p7.clp							\
	examples/waltz/waltz12.bat  examples/waltz/waltz37.bat  examples/waltz/waltz.c		\
	examples/waltz/waltz12.clp  examples/waltz/waltz37.clp  examples/waltz/waltz.clp	\
	examples/waltz/waltz12.fct  examples/waltz/waltz37.fct  examples/waltz/waltz.jess	\
	examples/waltz/waltz25.bat  examples/waltz/waltz50.bat  examples/waltz/waltzudf.clp	\
	examples/waltz/waltz25.clp  examples/waltz/waltz50.clp					\
	examples/waltz/waltz25.fct  examples/waltz/waltz50.fct

SUBDIRS = clips x_window_system documentation

dist-hook:
	cd documentation && make docs
	mv documentation/$(PACKAGE)-$(VERSION)-doc.tar.gz .
	mv documentation/$(PACKAGE)-$(VERSION)-doc.tar.bz2 .
	mv documentation/$(PACKAGE)-$(VERSION)-doc.zip .
