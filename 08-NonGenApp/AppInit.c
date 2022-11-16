/* *****************************************************************************
	FILE: 			AppInit.c
	
	DESCRIPTION: 	Application Initialization Utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.20.90	-	July 1990 MacUser Release (scrolling)
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

#define kMinSegSize		32768L		/* estimate of minimum memory needs  */
#define	kMastersNeeded	4			/* for pre-alloc of master pointers */

#define	kScreenBorder	4			/* these values in pixels */
#define	kIconSize		32			/* the width or height of an ICON in pixels */


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
	openAppDocs -	if application is opened from doc, open those documents. Else put new
	3.30.90kwgm		document up. This is a result of double-clicking on a document in the
					desktop
------------------------------------------------------------------------------------------ */
void
openAppDocs ()
{
	Boolean		openedOne;
	
	/* GenApp has no documents */
	openedOne = false;

/* ### kwgm 5.17.90 - new argument to doNewDoc */
	if (!openedOne)
		doNewDoc (kDocPICT);
	 
} /* openAppDocs */

/* ----------------------------------------------------------------------------------------
	initMem -	initialize application state/global variables
	3.30.90kwgm
	4.24.90kwgm - 	modified for multiple window environment
	5.20.90kwgm	-	modified for window scrolling
------------------------------------------------------------------------------------------ */
static Boolean
initMem ()
{
	register short 	i;
	Size 			sz;
	short 			resW, resH, menuBarHeight;
	Boolean			resultCode;
	Rect			grayRgnBounds;
	RgnHandle		grayRgnHdl;

	MaxApplZone ();    		/* maximize available memory */

	sz = FreeMem ();		/* get the available free memory */
	
	/* check that there's enough memory for our application */
	if (sz < kMinSegSize)
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
		this default window rect is offset from the screen's edges by the
		size of an icon. The offset is so users can still select the desktop
		in Multifinder by clicking on the disk icons on the rhs of the screen
	*/
	SetRect (&gWindowRect, kIconSize, menuBarHeight + kIconSize, 
		resW - kIconSize, resH - kIconSize);

	/* now get entire gray rgn rect (the size of all screens in multiple screen env.) */
	grayRgnHdl = (RgnHandle)GetGrayRgn ();					/* known as the 'gray region' */
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

	gNumOpenDocs = 0;		/* window management globals */
	gNextWindow = 1;
	
	gDevel = true;			/* we are in development */
	
	return (true);
	
} /* initMem */

/* ---------------------------------------------------------------------------------
	initMenus -		set up the application menus.
	3.30.90kwgm		all menu templates are in the resource file.
	5.20.90kwgm		added new menus for window type, window list.
-----------------------------------------------------------------------------------*/
void
initMenus ()
{
	gDeskMenu = GetMenu (kAppleMenuID);
	AddResMenu (gDeskMenu, 'DRVR');
	InsertMenu (gDeskMenu, 0);
	
	gFileMenu = GetMenu (kFileMenuID);
	InsertMenu (gFileMenu, 0);

	gEditMenu = GetMenu (kEditMenuID);
	InsertMenu (gEditMenu, 0);
	
/* ### kwgm 5.17.90 - new window menu */
	/* hierarchical menu */
	gDocTypeMenu = GetMenu (kDocTypeMenuID);
	InsertMenu (gDocTypeMenu, hierMenu);
/* ### kwgm 5.17.90 */

	DrawMenuBar();
	
} /* initMenus */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */