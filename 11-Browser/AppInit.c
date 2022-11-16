/* *****************************************************************************
	FILE: 			AppInit.c
	
	DESCRIPTION: 	Browser Initialization Utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#include "BrowserGlobals.h"
#include "MenuConstants.h"

#include <Dialogs.h>
#include <Menus.h>
#include <Quickdraw.h>
#include <TextEdit.h>
#include <Windows.h>

#include "AboutBoxPr.h"
#include "DocUtilPr.h"
#include "BrowserPr.h"
#include "WindowTblPr.h"

#include "AppInitPr.h"

/* -----------------  Local Constants  ---------------------------------- */

#define kMinSegSize		32768L		/* estimate of minimum memory needs  */
#define	kMastersNeeded	8			/* for pre-alloc of master pointers */

#define	kScreenBorder	4			/* these values in pixels */
#define	kIconSize		32			/* the width or height of an ICON in pixels */


/* ----------------------------  Local Prototypes  ------------------------------- */
static Boolean			initMem 		( void );
static void			initMenus 		( void );

/*----------------------------------------------------------------------------------------
	initApp -	initialize the QD environment and the application state
----------------------------------------------------------------------------------------- */
void
initApplication ()
{
	short 		item;

	InitGraf(&qd.thePort);    /* initialize the managers */
	InitFonts ();
	InitWindows();
	InitCursor ();	
	InitMenus  ();
	TEInit ();
	InitDialogs (0L);
	
	splashScreen ();
	
	if (!initMem())			/* initialize my stuff */
	{
		StopAlert (kNotEnufMem, 0L);
		ExitToShell ();
	}
	
	initMenus ();			/* init application menus */
		
} /* initApp */

/* ----------------------------------------------------------------------------------------
	initMem -	initialize application state/global variables
------------------------------------------------------------------------------------------ */
static Boolean
initMem ()
{
	register short 	i;
	Size 			sz;
	short 			resW, resH, menuBarHeight;
	OSErr			resultCode;
	Rect			grayRgnBounds;
	RgnHandle		grayRgnHdl;

	MaxApplZone ();    		/* maximize available memory */
	
	if ((sz = FreeMem ()) < kMinSegSize)
		return (false);
	
	/* to avoid memory fragmentation, allocate master pointers at bottom of heap */
	for (i = 0 ; i < kMastersNeeded ; i++)
		MoreMasters();
	
	/* what are we running on here (System 4.1 or greater) */
	if (resultCode = SysEnvirons (1, &gSysEnv))
	{
		switch (resultCode) {
			case envNotPresent:
			default:
				StopAlert (kUnknownMach, 0L);	/* unknown environment */
				ExitToShell ();
				break;
		}
	}
	else
	{
		/* is WaitNextEvent implemented? - from Macintosh Tech Note #158 */
		if (gSysEnv.machineType > envMachUnknown)
			gHasWNE = NGetTrapAddress (0x60, ToolTrap) != NGetTrapAddress (0x9F, ToolTrap);
		else
			gHasWNE = false;		
	
		gHasColor = gSysEnv.hasColorQD;		/* color QD available */
	}

	/* get screen dimensions */
	resW = qd.screenBits.bounds.right - qd.screenBits.bounds.left;
	resH = qd.screenBits.bounds.bottom - qd.screenBits.bounds.top;
	menuBarHeight = GetMBarHeight();
	
	/*
		gScreenRect is the size of the main screen, inset by a margin
	*/
	SetRect (&gScreenRect, kScreenBorder, menuBarHeight + kScreenBorder, 
		resW - kScreenBorder, resH - kScreenBorder);
		
	/* 
		this default window rect for a browser window
	*/
	SetRect (&gWindowRect, 0, 0, 500, 260);

	/* now get entire gray rgn rect (the size of all screens in multiple screen env.) */
	grayRgnHdl = (RgnHandle)GetGrayRgn ();					/* known as the 'gray region' */
	grayRgnBounds = (*grayRgnHdl)->rgnBBox;		/* the bounding box for the region */
	resW = grayRgnBounds.right - grayRgnBounds.left;
	resH = grayRgnBounds.bottom - grayRgnBounds.top;
	
	/*
		this rect encompasses all of the monitor desktop space,
		minus the menu bar and inset by a margin. We'll use this
		rectangle to limit dragging windows
	*/
	SetRect (&gGrayRgnRect, kScreenBorder, menuBarHeight + kScreenBorder, 
		resW - kScreenBorder, resH - kScreenBorder);

	initDocList ();
	gNumOpenDocs = 0;		/* window management globals */
	gTextFace = 0;			/* font sizes */
	gTextFont = courier;
	gTextSize = 10;
	
	gDevel = true;			/* we are in development */
	
	return (true);
	
} /* initMem */

/* ---------------------------------------------------------------------------------
	initMenus -		set up the application menus.
-----------------------------------------------------------------------------------*/
void
initMenus ()
{
	gDeskMenu = GetMenu (kAppleMenuID);
	AddResMenu (gDeskMenu, 'DRVR');
	InsertMenu (gDeskMenu, 0);
	
	gFileMenu = GetMenu (kFileMenuID);
	InsertMenu (gFileMenu, 0);
	
	gOpenMenu = GetMenu (kOpenMenuID);
	InsertMenu (gOpenMenu, hierMenu);

	gEditMenu = GetMenu (kEditMenuID);
	InsertMenu (gEditMenu, 0);
	
	gWindowMenu = GetMenu (kWindowMenuID);
	InsertMenu (gWindowMenu, 0);
	
	DrawMenuBar();
	
} /* initMenus */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */