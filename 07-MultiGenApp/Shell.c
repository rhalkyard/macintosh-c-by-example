/* *****************************************************************************
	FILE: 			Shell.c
	
	DESCRIPTION: 	Main event loop and event handling utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	4.24.90 -	June 1990 MacUser Release
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#define _Main_Module_

#include "AppGlobals.h"

/* ### 4.24.90kwgm - added for multiGeneric */
#include "Version.h"
/* ### 4.24.90kwgm - added for multiGeneric */

#ifdef V2
#include <ControlMgr.h>
#include <DialogMgr.h>
#include <EventMgr.h>
#endif

#include "AppInitPr.h"
#include "DisplayPr.h"
#include "DocUtilPr.h"
#include "MenuUtilPr.h"
/* ### 4.24.90kwgm - added for multiGeneric */
#include "MiscUtilPr.h"
#include "WindowUtilPr.h"
/* ### 4.24.90kwgm - added for multiGeneric */
#include "ShellPr.h"
	
	
/* --------------------  Local Prototypes --------------------------------- */
void					main					( void );
static void				doKeyDown 				( EventRecord *e );
static void				doMouseDown 			( EventRecord *e );
static void				doActivateEvent			( EventRecord *e );
static void				doUpdateEvent			( EventRecord *e );
static void				doSuspendResume			( EventRecord *e );
static void				doInContent 			( WindowPtr, EventRecord *e );
/* -------------------------------------------------------------------------
	main -	program entry point
---------------------------------------------------------------------------- */
void
main ()
{
	EventRecord  	event;
	short 			dItem;
	DialogPtr		dialogPtr;
	Boolean			result;
	long			waitTicks;

	initApplication ();
	
	openAppDocs ();

	FlushEvents (everyEvent, 0);	/* dump all pending events */
	
	waitTicks = 20;		/* the Multifinder share time value */
	
	for (;;)	/* main event */
	{	
		if (gHasWNE)
			result = WaitNextEvent (everyEvent, &event, waitTicks, 0L);
		else
		{
			SystemTask ();
			result = GetNextEvent (everyEvent, &event);
		}
		
		if (result)
		{
			fixMenus ();			/* hilite/unhilite appropriate menu items */

			switch (event.what) 
			{
				case mouseDown:	
					doMouseDown (&event);
					break;
			
				case keyDown:
					doKeyDown (&event);
					break;
			
				case activateEvt:	
					doActivateEvent (&event);
					break;
	
				case updateEvt:
					doUpdateEvent (&event);
					break;

				case app4Evt:		/* multifinder suspend/resume event */
					doSuspendResume (&event);
					break;

				default:
					break;
					
			}
		}
	}
} /* main event loop */

/*--------------------------------------------------------------------------
	doKeyDown - react to a key down event
	3.30.90kwgm
---------------------------------------------------------------------------*/
static void 
doKeyDown (e)
	EventRecord 	*e;
{
	char 			c;
	
	c = e->message & charCodeMask;		/* get character from event record */
	
	if (e->modifiers & cmdKey)
	{
		doMenu (MenuKey (c));		/* do menu commands */
		HiliteMenu (0);
	}
}

/*------------------------------------------------------------------------------
	doMouseDown () -  react to a mouse down event
	3.30.90kwgm
	4.24.90kwgm -	modified for multiple window support
--------------------------------------------------------------------------------*/
static void 
doMouseDown (e)
	EventRecord 	*e;
{
	WindowPtr 		theWindow;
	short  			where;
/* ### 4.24.90kwgm - added for multiGeneric */
	long  			newSize;
	WStateData		**wDataHdl;
	Rect			userState, stdState, portRect;
/* ### 4.24.90kwgm - added for multiGeneric */

	where = FindWindow (e->where, &theWindow);
	
	switch (where) 			/* where did the event occur ?? */
	{
		case inDesk :
			break;
		
		case inMenuBar :
			doMenu (MenuSelect (e->where));
			break;
		
		case inSysWindow :
			SystemClick (e, theWindow);
			break;
	
		case inContent :
			if (theWindow != FrontWindow() || !((WindowPeek)theWindow)->hilited)
				SelectWindow (theWindow);
			else
				doInContent (theWindow, e);
			break;

/* ### kwgm 4.24.90 - new stuff supports window controls */
		case inDrag :					/* title region */
			if (!getDblClick(e))
			{
				SelectWindow (theWindow);
				DragWindow (theWindow, e->where, &gGrayRgnRect);
			}
			else
				clickZoomWindow (theWindow);
			break;
	
		case inGrow :
			doGrowWindow (theWindow, e->where);
			break;
			
		case inZoomIn:
		case inZoomOut:
			if (TrackBox (theWindow, e->where, where))
				doZoomBox (theWindow, where);
			break;
/* ### kwgm 4.24.90 */
	
		case inGoAway :
			if (TrackGoAway (theWindow, e->where))
			{
/* ### 4.24.90kwgm - added for multiGeneric */
				if (e->modifiers & optionKey)
					closeAllDocs ();
				else
/* ### 4.24.90kwgm - added for multiGeneric */
					doCloseDoc (theWindow);
			}
			break;
	}
} /* doMouseDown */

/*-----------------------------------------------------------------------------
	doActivateEvent -	react to an activate event
	3.30.90kwgm
	4.24.90kwgm -	modified for multiple window support
------------------------------------------------------------------------------*/
static void 
doActivateEvent (e)
	EventRecord 	*e;
{
	WindowPtr 		theWindow;  		/* the active window */
	ControlHandle	controlList;
	Rect			scrollbarRect;

	theWindow = (WindowPtr) e->message;
	SetPort (theWindow);

	HidePen();

	/* activate or deactivate all window controls */
	controlList = (ControlHandle) ((WindowPeek)theWindow)->controlList;
	if (e->modifiers & activeFlag)
	{
		while (controlList)
		{
			ShowControl (controlList);
			controlList = (*controlList)->nextControl;
		}
	}
	else
	{
		while (controlList)
		{
			HideControl (controlList);
			controlList = (*controlList)->nextControl;
		}
	}
	
	ShowPen();
	
/* ### kwgm 4.24.90 - addition to May 1990 version */
	/* since HidePen was in effect during the
		activation/deactivation of controls,
		put the scroll bars, grow Icon into the refresh area 
		so that they are drawn in the subsequent update event
	*/
	invalScrollBars (theWindow, false);
/* ### kwgm 4.24.90  */

} /* doActivateEvent */

/* ----------------------------------------------------------------------------
	doUpdateEvent - react to the update event
	3.30.90kwgm
	4.24.90kwgm -	modified for multiple window support
-------------------------------------------------------------------------------*/
static void 
doUpdateEvent (e)
	EventRecord		*e;
{
	WindowPtr		theWindow;
	GrafPtr			savePort;
	
	theWindow = (WindowPtr) e->message;

	if (((WindowPeek) theWindow)->windowKind  >= 1)		/* is my window?  */
	{
		GetPort (&savePort);
		SetPort (theWindow);
		BeginUpdate (theWindow);
		
		EraseRgn ((RgnHandle) (WindowPeek)theWindow->visRgn);

/* ### kwgm 4.24.90 - addition to May 1990 version */
		drawScrollBars ((DocPtr) theWindow, true);				
/* ### kwgm 4.24.90  */
		drawDocContents ((DocPtr) theWindow);
		
		EndUpdate (theWindow);
		SetPort (savePort);
	}
	
} /* doUpdateEvent */

/* ------------------------------------------------------------------------------
	doInContent -	called from doMouseDown, respond to mouse down in window
	3.30.90kwgm 
--------------------------------------------------------------------------------- */
static void 
doInContent ( theWindow, eventPtr)
	WindowPtr				theWindow;
	EventRecord				*eventPtr;
{
	short					part;
	ControlHandle			theControl;
	Point					where;
	
	where = eventPtr->where;
	
	GlobalToLocal (&where);
		
	/* still nothing to do here yet */

}	/* doInContent */

/* -----------------------------------------------------------------------------------
	doSuspendResume -	do necessary things on multifinder switch
	3.30.90kwgm
-------------------------------------------------------------------------------------- */
static void 
doSuspendResume (e)
	EventRecord		*e;
{
	Boolean			activate;
	WindowPtr		topWindow;
	
	/* Suspend == false, Resume == true */
	activate = (e->message & 1) ? true : false;
	
	/* if active window, activate/deactivate */
	topWindow = FrontWindow ();
	
	if ((((WindowPeek) topWindow)->windowKind == userKind)) 
	{
		if (activate)
		{
			SelectWindow (topWindow);
/* ### 4.24.90kwgm - added for multiGeneric to set window highlight */
			HiliteWindow (topWindow, true);
/* ### 4.24.90kwgm - added for multiGeneric */
		}
		else
			HiliteWindow (topWindow, false);
	}

} /* doSuspendResume */

/*------------------------------------------------------------------------------
	cleanExit - 	do the assorted things which must be done on exit
	3.30.90kwgm
	4.24.90kwgm -	modified for multiple window support
-------------------------------------------------------------------------------- */
void 
cleanExit (normal)
	Boolean		normal;
{
/* ### 4.24.90kwgm - closeAllDocs added for multiGeneric */
	if (closeAllDocs ())
/* ### 4.24.90kwgm - added for multiGeneric */
		ExitToShell ();
}

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */