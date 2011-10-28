/*****************************************************************************
 **   Copyright (C) 2004 by Rick L. Vinyard, Jr.                            **
 **   rvinyard@cs.nmsu.edu                                                  **
 **                                                                         **
 **   This program is free software; you can redistribute it and/or modify  **
 **   it under the terms of the GNU General Public License as               **
 **   published by the Free Software Foundation version 2.                  **
 **                                                                         **
 **   This program is distributed in the hope that it will be useful,       **
 **   but WITHOUT ANY WARRANTY; without even the implied warranty of        **
 **   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
 **   GNU General Public License for more details.                          **
 **                                                                         **
 **   You should have received a copy of the GNU General Public             **
 **   License along with this library; if not, write to the                 **
 **   Free Software Foundation, Inc.,                                       **
 **   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA              **
 *****************************************************************************/

#ifndef _H_usrsetup
#define _H_usrsetup

/****************************************************************/
/* HELP: To implement the help facility, set the flag below and */
/* specify the path and name of the help data file your system. */
/****************************************************************/

#undef HELP_FUNCTIONS
#undef HELP_DEFAULT

#include <clips/clips-config.h>
#define HELP_FUNCTIONS 1
#define HELP_DEFAULT CLIPS_HELPFILE

#endif	/* _H_usrsetup */

