/* *****************************************************************************
	FILE: 			AppInit.c
	
	DESCRIPTION: 	Application Initialization Utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	4.24.90	-	June 1990 MacUser Release (multiple windows)
	3.30.90 - 	May 1990 MacUser Release (miniGenApp)
	==========================================================

   ***************************************************************************** */
#include <Dialogs.h>
#include <Fonts.h>
#include <Menus.h>
#include <Quickdraw.h>
#include <TextEdit.h>
#include <Windows.h>

#include "AppGlobals.h"
#include "MenuConstants.h"

#include "AboutBoxPr.h"
#include "DocUtilPr.h"
#include "ShellPr.h"

#include "AppInitPr.h"

/* -----------------  Local Constants  ---------------------------------- */

/* you estimate your minimum needs here */
#define kMinSegSize		4096L		/* free space needed for this application */
#define	kMastersNeeded	4			/* for pre-alloc of master pointers */

#define	kScreenBorder	4			/* these values in pixels */
#define	kIconSize		32		


/* ----------------------------  Local Prototypes  ------------------------------- */
static Boolean		initMem 		( void );
static void			initMenus 		( void );

/*----------------------------------------------------------------------------------------
	initApp -	initialize the QD environment and the application state
	3.30.90kwgm
----------------------------------------------------------------------------------------- */
void
initApplication ()
{
	InitGraf(&qd.thePort);    /* initialize the Mac managers */
	InitFonts ();
	InitWindows();
	InitCursor ();	
	InitMenus  ();
	TEInit ();
	InitDialogs (0L);
	
	splashScreen ();		/* put up splash screen */
	
	if (!initMem())			/* initialize application memory */
	{
		StopAlert (kNotEnufMem, 0L);
		ExitToShell ();
	}
	
	initMenus ();			/* init application menus */
	
} /* initApp */

/* ----------------------------------------------------------------------------------------
	openAppDocs -	if application is opened from doc, open those documents. Else put new
	3.30.90kwgm		document up. This is a result of double-clicking on a document in the
					desktop
------------------------------------------------------------------------------------------ */
void
openAppDocs ()
{
	Boolean		openedOne;
	
	/* GenApp has no documents - this is a hook for future use */
	openedOne = false;
	
	if (!openedOne)
		doNewDoc ();
	 
} /* openAppDocs */

/* ----------------------------------------------------------------------------------------
	initMem -	initialize application state/global variables
	3.30.90kwgm
	4.24.90kwgm - modified for multiple window environment
------------------------------------------------------------------------------------------ */
static Boolean
initMem ()
{
	register short 	i;
	short 			resW, resH, menuBarHeight;
	Size 			sz;
	OSErr			resultCode;
	Rect			grayRgnBounds;
	RgnHandle		grayRgnHdl;

	MaxApplZone ();    		/* maximize available memory */
	
	sz = FreeMem ();		/* get the available free memory */
	
	if (sz < kMinSegSize)
		return (false);		/* not enough memory for our application */

	/* to avoid memory fragmentation, allocate master pointers at bottom of heap */
	for (i = 0 ; i < kMastersNeeded ; i++)
		MoreMasters();
	
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
		this default window rect is offset from the screen's edges by the
		size of an icon 
	*/
	SetRect (&gWindowRect, kIconSize, menuBarHeight + kIconSize, 
		resW - kIconSize, resH - kIconSize);
	
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
	}

/* ### 4.24.90 kwgm - new stuff for multiGeneric */
	/* now get entire gray rgn rect (the size of all monitors) */
	grayRgnHdl = GetGrayRgn ();					/* known as the 'gray region' */
	grayRgnBounds = (*grayRgnHdl)->rgnBBox;		/* the bounding box for the region */
	resW = grayRgnBounds.right - grayRgnBounds.left;
	resH = grayRgnBounds.bottom - grayRgnBounds.top;
	
	/*
		this rect encompasses all of the monitor desktop space,
		minus the menu bar and inset by a margin. We'll use this
		rectangle to limit dragging and resizing windows
	*/
	SetRect (&gGrayRgnRect, kScreenBorder, menuBarHeight + kScreenBorder, 
		resW - kScreenBorder, resH - kScreenBorder);

	gNumOpenDocs = 0;		/* multiple window globals */
	gNextWindow = 1;
/* ### 4.24.90 kwgm - new stuff for multiGeneric */
	
	gDevel = true;			/* can be used to turn on debugging features */
	
	return (true);
	
} /* initMem */

/* ---------------------------------------------------------------------------------
	initMenus -		set up the application menus
	3.30.90kwgm		all menu templates are in the resource file
-----------------------------------------------------------------------------------*/
void
initMenus ()
{
	gDeskMenu = GetMenu (kAppleMenuID);
	AddResMenu (gDeskMenu, 'DRVR');			/* add DAs to the apple menu */
	InsertMenu (gDeskMenu, 0);
	
	gFileMenu = GetMenu (kFileMenuID);	/* read template, get handle */
	InsertMenu (gFileMenu, 0);			/* and insert in the app's menu list */

	gEditMenu = GetMenu (kEditMenuID);
	InsertMenu (gEditMenu, 0);
	
	DrawMenuBar();
	
} /* initMenus */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */