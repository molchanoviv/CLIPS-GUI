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

EXTRA_DIST = clips.hlp	\
	clips-init.el  clips-mode.el  inf-clips.el \
	get-html-docs.sh get-pdf-docs.sh


clipshelpdir = @helpdir@
clipshelp_DATA = clips.hlp

docdistdir="$(PACKAGE)-$(VERSION)-doc"

docs:
	rm -rf $(docdistdir) 
	./get-html-docs.sh
	./get-pdf-docs.sh
	mkdir $(docdistdir)
	cp -arv html  $(docdistdir)
	cp -p apg.pdf bpg.pdf ig.pdf ug.pdf $(docdistdir)
	cp -p 3CCP.pdf advanced.doc architecture5-1.pdf basic.doc $(docdistdir)
	cp -p interfaces.doc user.doc $(docdistdir)
	cp -p abstract.pdf $(docdistdir)
	tar cvzf $(docdistdir).tar.gz $(docdistdir)/*
	tar cvjf $(docdistdir).tar.bz2 $(docdistdir)/*
	zip -r $(docdistdir).zip $(docdistdir)/*
	rm -rf $(docdistdir) 

mostlyclean-local:
	if [ -e $(PACKAGE)-*-doc.tar.gz ]; then rm $(PACKAGE)-*-doc.tar.gz; fi
	if [ -e $(PACKAGE)-*-doc.tar.bz2 ]; then rm $(PACKAGE)-*-doc.tar.bz2; fi
	if [ -e $(PACKAGE)-*-doc.zip ]; then rm $(PACKAGE)-*-doc.zip; fi
