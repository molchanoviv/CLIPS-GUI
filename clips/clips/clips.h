   /*******************************************************/
   /*      "C" Language Integrated Production System      */
   /*                                                     */
   /*             CLIPS Version 6.30  03/04/08            */
   /*                                                     */
   /*                   API HEADER FILE                   */
   /*******************************************************/

/*************************************************************/
/* Purpose:                                                  */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.24: Added filertr.h and tmpltfun.h to include      */
/*            list.                                          */
/*                                                           */
/*      6.30: Added classpsr.h to include list.              */
/*                                                           */
/*************************************************************/

#ifndef _H_API
#define _H_API

#ifdef __cplusplus
extern "C" {
#endif

#include <clips/setup.h>
#ifndef _H_argacces
#include <clips/argacces.h>
#endif
#include <clips/constant.h>
#include <clips/memalloc.h>
#include <clips/cstrcpsr.h>
#include <clips/filecom.h>
#include <clips/strngfun.h>
#include <clips/envrnmnt.h>
#include <clips/commline.h>
#ifndef _H_symbol
#include <clips/symbol.h>
#endif

#include <clips/router.h>
#include <clips/filertr.h>
#include <clips/strngrtr.h>

#include <clips/iofun.h>

#include <clips/sysdep.h>
#include <clips/bmathfun.h>
#ifndef _H_expressn
#include <clips/expressn.h>
#endif
#include <clips/exprnpsr.h>
#ifndef _H_evaluatn
#include <clips/evaluatn.h>
#endif
#ifndef _H_constrct
#include <clips/constrct.h>
#endif
#include <clips/utility.h>
#include <clips/watch.h>
#include <clips/modulbsc.h>

#if BLOAD_ONLY || BLOAD || BLOAD_AND_BSAVE
#include <clips/bload.h>
#endif

#if BLOAD_AND_BSAVE
#include <clips/bsave.h>
#endif

#if DEFRULE_CONSTRUCT
#ifndef _H_ruledef
#include <clips/ruledef.h>
#endif
#include <clips/rulebsc.h>
#include <clips/engine.h>
#include <clips/drive.h>
#include <clips/incrrset.h>
#include <clips/rulecom.h>
#include <clips/crstrtgy.h>
#endif

#if DEFFACTS_CONSTRUCT
#include <clips/dffctdef.h>
#include <clips/dffctbsc.h>
#endif

#if DEFTEMPLATE_CONSTRUCT
#include <clips/tmpltdef.h>
#include <clips/tmpltbsc.h>
#include <clips/tmpltfun.h>
#include <clips/factcom.h>
#include <clips/factfun.h>
#ifndef _H_factmngr
#include <clips/factmngr.h>
#endif
#include <clips/facthsh.h>
#endif

#if DEFGLOBAL_CONSTRUCT
#include <clips/globldef.h>
#include <clips/globlbsc.h>
#include <clips/globlcom.h>
#endif

#if DEFFUNCTION_CONSTRUCT
#include <clips/dffnxfun.h>
#endif

#if DEFGENERIC_CONSTRUCT
#include <clips/genrccom.h>
#include <clips/genrcfun.h>
#endif

#if OBJECT_SYSTEM
#include <clips/classcom.h>
#include <clips/classexm.h>
#include <clips/classinf.h>
#include <clips/classini.h>
#include <clips/classpsr.h>
#include <clips/defins.h>
#include <clips/inscom.h>
#include <clips/insfile.h>
#include <clips/insfun.h>
#include <clips/msgcom.h>
#include <clips/msgpass.h>
#include <clips/objrtmch.h>
#endif

#ifdef __cplusplus
}
#endif


#endif



