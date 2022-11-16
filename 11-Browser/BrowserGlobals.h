/* *****************************************************************************
	FILE: 			BrowserGlobals.h
	
	DESCRIPTION: 	Browser global variables declaration and definitions

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#ifndef _BrowserGlobals_
#define	_BrowserGlobals_


#ifdef _Main_Module_
#define SCOPE /*GLOBAL*/
#else
#define SCOPE extern
#endif

#include "BrowserConstants.h"
#include "BrowserTypes.h"

#include "Version.h"
#ifdef V5
#include <Menus.h>
#else
#include <MenuMgr.h>
#endif

SCOPE 		MenuHandle 			gDeskMenu,			/* application menu handles */
								gFileMenu,
								gEditMenu,
								gWindowMenu,
								gOpenMenu;

SCOPE		SysEnvRec			gSysEnv;			/* the current HW environment */
SCOPE		Boolean				gHasWNE,			/* has Wait Next Event implemented */
								gHasColor,			/* has color toolbox */
								gDevel;				/* in development */
								
SCOPE		Rect				gGrayRgnRect,		/* entire screen rect */
								gScreenRect,		/* the main device screen rect */
								gWindowRect;		/* default window rect */

SCOPE		short				gNumOpenDocs,		/* open document count */
								gTextFont,			/* the current user selected text attribnutes */
								gTextSize;
								
SCOPE		uchar				gTextFace;

#endif
/* ==================================  EOF  ====================================
 		Copryright © 1990 Kurt W.G. Matthies,  All Rights Reserved
   ============================================================================= */