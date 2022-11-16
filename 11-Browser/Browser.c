/* *****************************************************************************
	FILE: 			Browser.c
	
	DESCRIPTION: 	Browser entry point

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#define _Main_Module_

#include "BrowserGlobals.h"

#undef _Main_Module

#include "AppInitPr.h"
#include "DisplayPr.h"
#include "DocUtilPr.h"
#include "MenuUtilPr.h"
#include "MiscUtilPr.h"
#include "WindowTblPr.h"
#include "WindowUtilPr.h"

#include "BrowserPr.h"
	
	
/* --------------------  Local Prototypes --------------------------------- */
void					main					( void );
void					doKeyDown 				( EventRecord *e );
void					doMouseDown 			( EventRecord *e );
void					doActivateEvent			( EventRecord *e );
void					doUpdateEvent			( EventRecord *e );
void					doSuspendResume			( EventRecord *e );
void					doInContent 			( WindowPtr, EventRecord *e );

/* -------------------------------------------------------------------------
	main -	program entry point
---------------------------------------------------------------------------- */
void
main ()
{
	EventRecord  	event;
	Boolean			result;
	long			waitTicks;

	initApplication ();

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

/* ------------------------------------------------------------------------
	doKeyDown - react to a key down event
--------------------------------------------------------------------------- */
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

/*---------------------------------------------------------------------------
	doMouseDown () -  handle mouse down event
------------------------------------------------------------------------------ */
static void 
doMouseDown (e)
	EventRecord 	*e;
{
	WindowPtr 		theWindow;
	short  			where;
	long  			newSize;
	WStateData		**wDataHdl;
	Rect			userState, stdState, portRect;

	where = FindWindow (e->where, &theWindow);
	
	switch (where) {
		
		case inDesk :
			break;
		
		case inMenuBar :
			doMenu (MenuSelect (e->where));
			break;
		
		case inSysWindow :
			SystemClick (e, theWindow);
			break;
	
		case inContent:
			if (theWindow != FrontWindow() || !((WindowPeek)theWindow)->hilited)
				SelectWindow (theWindow);
			else
				doInContent (theWindow, e);
			break;
	
		case inDrag :				/* title region */
			if (ISTEXTDOC (theWindow) && getDblClick (e))
				clickZoomWindow (theWindow);
			else
			{
				SelectWindow (theWindow);
				DragWindow (theWindow, e->where, &gGrayRgnRect);
			}
			break;
			
		case inGrow :
			doGrowWindow (theWindow, e->where);
			break;
			
		case inZoomIn:
		case inZoomOut:
			if (TrackBox (theWindow, e->where, where))
				doZoomBox (theWindow, where);
			break;
	
		case inGoAway :
			if (TrackGoAway (theWindow, e->where))
			{
				if (e->modifiers & optionKey)
					closeAllDocs ();
				else
					doCloseDoc (theWindow);
			}
			break;
	}
} /* doMouseDown */

/*-----------------------------------------------------------------------------
	doActivateEvent -	react to an activate event
------------------------------------------------------------------------------*/
static void 
doActivateEvent (e)
	EventRecord 	*e;
{
	WindowPtr 		theWindow;  		/* the active window */
	ControlHandle	controlList;
	Rect			scrollbarRect;

	if (theWindow = (WindowPtr) e->message)
	{
		SetPort (theWindow);
		
		controlList =  ((WindowPeek)theWindow)->controlList;
		
		HidePen();
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
		
		/* put the scroll bars into the refresh area */
		invalScrollBars (theWindow, false);
	}

} /* doActivateEvent */

/* ----------------------------------------------------------------------------
	doUpdateEvent - react to the update event
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
		
		EraseRgn ((WindowPeek)theWindow->visRgn);

		drawScrollBars (theWindow, true);				
		drawDocContents (theWindow);
		
		EndUpdate (theWindow);
		SetPort (savePort);
	}
	
} /* doUpdateEvent */

/* ------------------------------------------------------------------------------
	doInContent -	called from doMouseDown, respond to mouse down in window
--------------------------------------------------------------------------------- */
static void 
doInContent (theWindow, eventPtr)
	WindowPtr				theWindow;
	EventRecord				*eventPtr;
{
	short					part;
	ControlHandle			theControl;
	Point					where;
	GrafPtr					savePort;
	
	GetPort (&savePort);		/* save current grafport */
	SetPort (theWindow);		/* set to this port */
	
	where = eventPtr->where;
	GlobalToLocal (&where);
		
	if (part = FindControl (where, theWindow, &theControl))		/* in control? */
		mouseInScroll (theWindow, theControl, part, where);

	SetPort (savePort);		/* restore port */

}	/* doInContent */

/* -----------------------------------------------------------------------------------
	doSuspendResume -	do necessary things on multifinder switch
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
			HiliteWindow (topWindow, true);
		}
		else
			HiliteWindow (topWindow, false);

		drawScrollBars (topWindow, activate);
	}

} /* doSuspendResume */

/* ------------------------------------------------------------------------------
	cleanExit - 	do the assorted things which must be done on exit
-------------------------------------------------------------------------------- */
void 
cleanExit (normal)
	Boolean		normal;
{	
	if (closeAllDocs ())			
		ExitToShell ();
}
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */