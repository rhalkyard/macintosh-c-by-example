/* *****************************************************************************
	FILE: 			Shell.c
	
	DESCRIPTION: 	Main event loop and event handling utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#define _Main_Module_

#include "AppGlobals.h"

#ifdef V2
#include <ControlMgr.h>
#include <DialogMgr.h>
#include <EventMgr.h>
#endif

#include "AppInitPr.h"
#include "DisplayPr.h"
#include "DocUtilPr.h"
#include "MenuUtilPr.h"

#include "ShellPr.h"
	
	
/* --------------------  Local Prototypes --------------------------------- */
void					main					( void );
void					doKeyDown 				( EventRecord *e );
void					doMouseDown 			( EventRecord *e );
void					doActEvent				( EventRecord *e );
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
	short 			dItem;
	DialogPtr		dialogPtr;
	Boolean			result;
	long			waitTicks;

	initApplication ();
	
	openAppDocs ();

	FlushEvents (everyEvent, 0);	/* dump all pending events */
	
	waitTicks = 20;		/* the Multifinder share time value */
	
	while (true)	/* main event loop */
	{	
		if (gHasWNE)
			result = WaitNextEvent (everyEvent, &event, waitTicks, 0L);
		else
		{
			SystemTask ();
			result = GetNextEvent (everyEvent, &event);
		}
		
		if (result)		/* if there is an event */
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
					doActEvent (&event);
					break;
	
				case updateEvt:
					doUpdateEvent (&event);
					break;
					
				case app4Evt:
					doSuspendResume (&event);
					break;
					
				default:		/* 
									you may want to put some test code here
									to see what kind of events an application
									can receive
								*/
					break;
					
			}
		}
	}	/* main event loop */
} 

/*--------------------------------------------------------------------------
	doKeyDown - 	react to a key down event
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
	doMouseDown -  react to a mouse down event
	3.30.90kwgm
--------------------------------------------------------------------------------*/
static void 
doMouseDown (e)
	EventRecord 	*e;
{
	WindowPtr 		theWindow;
	short  			where;

	where = FindWindow (e->where, &theWindow);
	
	switch (where) 
	{	
		case inDesk:		/* not interested */
			break;
		
		case inMenuBar:
			doMenu (MenuSelect (e->where));
			break;
		
		case inSysWindow:
			SystemClick (e, theWindow);
			break;
	
		case inContent:
			if (theWindow != FrontWindow() || !((WindowPeek)theWindow)->hilited)
				SelectWindow (theWindow);
			else
				doInContent (theWindow, e);
			break;
	
		case inGoAway:
			if (TrackGoAway (theWindow, e->where))
				doCloseDoc (theWindow);
			break;
	}

} /* doMouseDown */


/*-----------------------------------------------------------------------------
	doActEvent -	react to an activate event
	3.30.90kwgm
------------------------------------------------------------------------------*/
static void 
doActEvent (e)
	EventRecord 	*e;
{
	WindowPtr 		theWindow;  		/* the active window */
	ControlHandle	controlList;
	Rect			scrollbarRect;

	theWindow = (WindowPtr) e->message;
	SetPort (theWindow);
	
	controlList =  ((WindowPeek)theWindow)->controlList;
	
	HidePen();
	if (e->modifiers & activeFlag)
	{
		/* activate the controls of the newly activated window */
		while (controlList)
		{
			ShowControl (controlList);
			controlList = (*controlList)->nextControl;
		}
	}
	else
	{
		/* deactivate the controls of the newly deactivated window */
		while (controlList)
		{
			HideControl (controlList);
			controlList = (*controlList)->nextControl;
		}
	}
	ShowPen();

} /* doActEvent */

/* ----------------------------------------------------------------------------
	doUpdateEvent -		react to the update event
	3.30.90kwgm
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
		
		drawDocContents (theWindow);
		
		EndUpdate (theWindow);
		SetPort (savePort);
	}
	
} /* doUpdateEvent */

/* ------------------------------------------------------------------------------
	doInContent -	called from doMouseDown, respond to mouse down in window
	3.30.90kwgm 
--------------------------------------------------------------------------------- */
static void 
doInContent (theWindow, eventPtr)
	WindowPtr				theWindow;
	EventRecord				*eventPtr;
{
	short					part;
	ControlHandle			theControl;
	Point					where;
	
	SetPort (theWindow);
	
	where = eventPtr->where;
	
	GlobalToLocal (&where);
		
	/* this is the start of something, but there's nothing to do here yet */
	
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
			SelectWindow (topWindow);
		else
			HiliteWindow (topWindow, false);
	}

} /* doSuspendResume */

/*------------------------------------------------------------------------------
	cleanExit - 	do the assorted things which must be done on exit
	3.30.90kwgm
-------------------------------------------------------------------------------- */
void 
cleanExit (normal)
	Boolean		normal;
{
	WindowPeek		theWindow;
	
	if (theWindow = FrontWindow ())
		if (theWindow->windowKind > 1)
			doCloseDoc (theWindow);
			
	ExitToShell ();
}
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */