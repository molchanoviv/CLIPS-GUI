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

INCLUDES = -I$(top_srcdir)/. $(PACKAGE_CFLAGS)

lib_LTLIBRARIES = libclips.la

library_includedir = $(includedir)/clips
libclips_la_LDFLAGS = -version-info @LIBTOOL_SO_VERSION@ $(PACKAGE_LIBS)

library_include_HEADERS = \
	agenda.h    cstrnpsr.h  factbld.h   immthpsr.h  network.h   ruledef.h	\
	analysis.h  cstrnutl.h  factcmp.h   incrrset.h  objbin.h    ruledlt.h	\
	argacces.h  default.h   factcom.h   inherpsr.h  objcmp.h    rulelhs.h	\
	bload.h     defins.h    factfun.h   inscom.h    object.h    rulepsr.h	\
	bmathfun.h  developr.h  factgen.h   insfile.h   objrtbin.h  scanner.h	\
	bsave.h     dffctbin.h  facthsh.h   insfun.h    objrtbld.h  setup.h	\
	classcom.h  dffctbsc.h  factlhs.h   insmngr.h   objrtcmp.h  sortfun.h	\
	classexm.h  dffctcmp.h  factmch.h   insmoddp.h  objrtfnx.h  strngfun.h	\
	classfun.h  dffctdef.h  factmngr.h  insmult.h   objrtgen.h  strngrtr.h	\
	classinf.h  dffctpsr.h  factprt.h   inspsr.h    objrtmch.h  symblbin.h	\
	classini.h  dffnxbin.h  factqpsr.h  insquery.h  parsefun.h  symblcmp.h	\
	classpsr.h  dffnxcmp.h  factqury.h  insqypsr.h  pattern.h   symbol.h	\
	clips.h     dffnxexe.h  factrete.h  iofun.h     pprint.h    sysdep.h	\
	clsltpsr.h  dffnxfun.h  factrhs.h   lgcldpnd.h  prccode.h   textpro.h	\
	cmptblty.h  dffnxpsr.h  filecom.h   match.h     prcdrfun.h  tmpltbin.h	\
	commline.h  dfinsbin.h  filertr.h   memalloc.h  prcdrpsr.h  tmpltbsc.h	\
	conscomp.h  dfinscmp.h  generate.h  miscfun.h   prdctfun.h  tmpltcmp.h	\
	constant.h  drive.h     genrcbin.h  modulbin.h  prntutil.h  tmpltdef.h	\
	constrct.h  ed.h        genrccmp.h  modulbsc.h  proflfun.h  tmpltfun.h	\
	constrnt.h  emathfun.h  genrccom.h  modulcmp.h  reorder.h   tmpltlhs.h	\
	crstrtgy.h  engine.h    genrcexe.h  moduldef.h  reteutil.h  tmpltpsr.h	\
	cstrcbin.h  envrnmnt.h  genrcfun.h  modulpsr.h  retract.h   tmpltrhs.h	\
	cstrccmp.h  evaluatn.h  genrcpsr.h  modulutl.h  router.h    tmpltutl.h	\
	cstrccom.h  expressn.h  globlbin.h  msgcom.h    rulebin.h   userdata.h	\
	cstrcpsr.h  exprnbin.h  globlbsc.h  msgfun.h    rulebld.h   usrsetup.h	\
	cstrnbin.h  exprnops.h  globlcmp.h  msgpass.h   rulebsc.h   utility.h	\
	cstrnchk.h  exprnpsr.h  globlcom.h  msgpsr.h    rulecmp.h   watch.h	\
	cstrncmp.h  extnfunc.h  globldef.h  multifld.h  rulecom.h		\
	cstrnops.h  factbin.h   globlpsr.h  multifun.h  rulecstr.h		\
	clips-config.h

libclips_la_SOURCES = \
	agenda.c    developr.c  factbld.c   immthpsr.c  objbin.c    rulelhs.c	\
	analysis.c  dffctbin.c  factcmp.c   incrrset.c  objcmp.c    rulepsr.c	\
	argacces.c  dffctbsc.c  factcom.c   inherpsr.c  objrtbin.c  scanner.c	\
	bload.c     dffctcmp.c  factfun.c   inscom.c    objrtbld.c  sortfun.c	\
	bmathfun.c  dffctdef.c  factgen.c   insfile.c   objrtcmp.c  strngfun.c	\
	bsave.c     dffctpsr.c  facthsh.c   insfun.c    objrtfnx.c  strngrtr.c	\
	classcom.c  dffnxbin.c  factlhs.c   insmngr.c   objrtgen.c  symblbin.c	\
	classexm.c  dffnxcmp.c  factmch.c   insmoddp.c  objrtmch.c  symblcmp.c	\
	classfun.c  dffnxexe.c  factmngr.c  insmult.c   parsefun.c  symbol.c	\
	classinf.c  dffnxfun.c  factprt.c   inspsr.c    pattern.c   sysdep.c	\
	classini.c  dffnxpsr.c  factqpsr.c  insquery.c  pprint.c    textpro.c	\
	classpsr.c  dfinsbin.c  factqury.c  insqypsr.c  prccode.c   tmpltbin.c	\
	clsltpsr.c  dfinscmp.c  factrete.c  iofun.c     prcdrfun.c  tmpltbsc.c	\
	commline.c  drive.c     factrhs.c   lgcldpnd.c  prcdrpsr.c  tmpltcmp.c	\
	conscomp.c  edbasic.c   filecom.c               prdctfun.c  tmpltdef.c	\
	constrct.c  edmain.c    filertr.c   memalloc.c  prntutil.c  tmpltfun.c	\
	constrnt.c  edmisc.c    generate.c  miscfun.c   proflfun.c  tmpltlhs.c	\
	crstrtgy.c  edstruct.c  genrcbin.c  modulbin.c  reorder.c   tmpltpsr.c	\
	cstrcbin.c  edterm.c    genrccmp.c  modulbsc.c  reteutil.c  tmpltrhs.c	\
	cstrccom.c  emathfun.c  genrccom.c  modulcmp.c  retract.c   tmpltutl.c	\
	cstrcpsr.c  engine.c    genrcexe.c  moduldef.c  router.c    userdata.c	\
	cstrnbin.c  envrnmnt.c  genrcfun.c  modulpsr.c  rulebin.c   userfunctions.c \
	cstrnchk.c  evaluatn.c  genrcpsr.c  modulutl.c  rulebld.c   utility.c	\
	cstrncmp.c  expressn.c  globlbin.c  msgcom.c    rulebsc.c   watch.c	\
	cstrnops.c  exprnbin.c  globlbsc.c  msgfun.c    rulecmp.c		\
	cstrnpsr.c  exprnops.c  globlcmp.c  msgpass.c   rulecom.c		\
	cstrnutl.c  exprnpsr.c  globlcom.c  msgpsr.c    rulecstr.c		\
	default.c   extnfunc.c  globldef.c  multifld.c  ruledef.c		\
	defins.c    factbin.c   globlpsr.c  multifun.c  ruledlt.c

bin_PROGRAMS = clips

clips_LDADD =  $(PACKAGE_LIBS) libclips.la

clips_SOURCES = main.c

