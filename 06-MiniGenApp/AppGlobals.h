/* *****************************************************************************
	FILE: 			AppGlobals.h
	
	DESCRIPTION: 	Application global variables declaration and definitions

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	3.30.90	-	May 1990 MacUser Release
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
	There's a trick in these definitions:
	
	if _Main_Module_ is defined, and it's only defined in Shell.c,
	then SCOPE is a comment and the variables are defined, the space for
	them created.
	
	if _Main_Module_ is undefined, as in all other modules but Shell.c
	then SCOPE becomes the keyword 'extern' and these variables are declared,
	so they're accessable, but no space is created for them.
	
	Thus, you can use this file in any file that needs to access 
	the application's globals. Then, there's no need to define globals 
	extern in a module before they can be used--it's already done for you.

*/
	
#include "AppConstants.h"
#include "AppTypes.h"

#include "Version.h"	/* sets up the compiler version flag - see the readme file */

#ifdef V5
#include <Menus.h>
#else
#include <MenuMgr.h>
#endif

#ifdef V2
#include <OSUtil.h>
#endif


SCOPE 		MenuHandle 			gDeskMenu,			/* menu handles */
								gFileMenu,
								gEditMenu;

SCOPE		SysEnvRec			gSysEnv;			/* the current HW environment */
SCOPE		Boolean				gHasWNE,			/* has Wait Next Event implemented */
								gHasColor,			/* has color toolbox */
								gDevel;				/* in development */
								
SCOPE		Rect				gScreenRect,		/* the main device screen rect */
								gWindowRect;		/* default window rect */

#undef _main_module

#endif
/* ==================================  EOF  ====================================
 		Copryright © 1990 Kurt W.G. Matthies,  All Rights Reserved
   ============================================================================= */