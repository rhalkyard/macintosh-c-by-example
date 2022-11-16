/* *****************************************************************************
	FILE: 			AppGlobals.h
	
	DESCRIPTION: 	Application global variables declaration and definitions

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.20.90 - 	July 1990 MacUser Release - scrolling
	4.24.90	-	June 1990 MacUser Release - multiple windows
	3.30.90 - 	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#ifndef _AppGlobals_
#define	_AppGlobals_


#ifdef _Main_Module_
#define SCOPE /*GLOBAL*/
#else
#define SCOPE extern
#endif

/* 
	there's a trick here:
	
	if _Main_Module_ is defined, and it's only defined in Shell.c,
	then SCOPE is a comment and the variables are defined.
	
	if _Main_Module_ is undefined, then SCOPE becomes the keyword
	extern and these variables are declared.
	
	Thus, you can use this file in any file that needs to access 
	the application's globals. There's no need for an "extern.h"
	
	Thanks to Jean-Phillipe for this one.
	
*/
	
#include "AppConstants.h"
#include "AppTypes.h"

#include "Version.h"

#ifdef V5
#include <Menus.h>
#else
#include <MenuMgr.h>
#endif

#ifdef V2
#include <OSUtil.h>
#endif


SCOPE 		MenuHandle 			gDeskMenu,			/* application menu handles */
								gFileMenu,
								gEditMenu,
/* ### kwgm 5.17.90 */
								gDocTypeMenu;
/* ### kwgm 5.17.90 */

SCOPE		SysEnvRec			gSysEnv;			/* the current HW environment */
SCOPE		Boolean				gHasWNE,			/* has Wait Next Event implemented */
								gHasColor,			/* has color toolbox */
								gDevel;				/* in development */
								
SCOPE		Rect				gGrayRgnRect,		/* entire screen rect */
								gScreenRect,		/* the main device screen rect */
								gWindowRect;		/* default window rect */

SCOPE		short				gNumOpenDocs,		/* open document count */
								gNextWindow;		/* next available untitled window # */

#undef _main_module

#endif
/* ==================================  EOF  ====================================
 		Copryright © 1990 Kurt W.G. Matthies,  All Rights Reserved
   ============================================================================= */