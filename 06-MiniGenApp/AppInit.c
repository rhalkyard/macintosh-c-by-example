/* *****************************************************************************
	FILE: 			AppInit.c
	
	DESCRIPTION: 	Application Initialization Utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
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
Boolean					initMem 		( void );
void					initMenus 		( void );

/*----------------------------------------------------------------------------------------
	initApp -	initialize the QD environment and the application state
	3.30.90kwgm
----------------------------------------------------------------------------------------- */
void
initApplication ()
{
	short 		item;

	InitGraf(&thePort);    /* initialize the Mac managers */
	InitFonts ();
	InitWindows();
	InitCursor ();	
	InitMenus  ();
	TEInit ();
	InitDialogs (0L);
	
	splashScreen ();
	
	if (!initMem())			/* initialize application stuff */
	{
		StopAlert (kNotEnufMem, 0L);
		ExitToShell ();
	}
	
	initMenus();
	
} /* initApp */

/* ----------------------------------------------------------------------------------------
	openAppDocs -	if opened from documents, open those documents. Else put new
	3.30.90kwgm		document up. This is where double-clicking on a document opens
					that document
------------------------------------------------------------------------------------------ */
void
openAppDocs ()
{
	Boolean		openedOne;
	
	/* miniGenApp has no documents - for future use */
	openedOne = false;
	
	if (!openedOne)
		doNewDoc ();
	 
} /* openAppDocs */

/* ----------------------------------------------------------------------------------------
	initMem -	initialize application state/global variables
	3.30.90kwgm
------------------------------------------------------------------------------------------ */
static Boolean
initMem ()
{
	register short 	i;
	short 			resW, resH, menuBarHeight;
	Size 			sz;
	Boolean			resultCode;
	
	MaxApplZone ();    		/* maximize available memory */

	sz = FreeMem ();		/* get the available free memory */
	
	if (sz < kMinSegSize)
		return (false);		/* not enough memory for our application */
	
	/* to avoid memory fragmentation, allocate master pointers at bottom of heap */
	for (i = 0 ; i < kMastersNeeded ; i++)
		MoreMasters();
	
	/* get screen dimensions */
	resW = screenBits.bounds.right - screenBits.bounds.left;
	resH = screenBits.bounds.bottom - screenBits.bounds.top;
	menuBarHeight = GetMBarHeight();
	
	/* two global rectangles: one for the screen, the other for the default window size */
	SetRect (&gScreenRect, kScreenBorder, menuBarHeight + kScreenBorder, resW - kScreenBorder, resH - kScreenBorder);
	SetRect (&gWindowRect, kIconSize, menuBarHeight + kIconSize, resW - kIconSize, resH - kIconSize);
	
	/* what are we running on here? (need System 4.1 or greater) */
	if (resultCode = SysEnvirons (1, &gSysEnv))
	{
		switch (resultCode) {
			case envNotPresent:
#if 0
			case envBadSel:
			case envSelTooBig:
#endif
		default:
				StopAlert (kUnknownMach, 0L);	/* unknown environment */
				ExitToShell ();		/* leave the program here */
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
	
		gHasColor = gSysEnv.hasColorQD;		/* this is a color QD machine */
	}
	
	gDevel = true;			/* we are in development, this flag can be used
								to turn on/off various debugging items 
								that wouldn't be included in a production version */
	
	return (true);
	
} /* initMem */

/* ---------------------------------------------------------------------------------
	initMenus -	set up the application menus
	3.30.90kwgm
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

	DrawMenuBar();
	
} /* initMenus */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */