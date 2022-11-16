/* *****************************************************************************
	FILE: 			DialogUtil.c
	
	DESCRIPTION: 	Dialog box utilities
	
	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#include "BrowserConstants.h"
#include "BrowserGlobals.h"

#include "DialogUtilPr.h"

/* --------------------------------------------------------------------------
	dialogHookProcs -	these hook procs do various things like
	3.30.90kwgm			highlight buttons, draw underlines, or handle
						keydown events in dialog boxes.
----------------------------------------------------------------------------- */
pascal void
buttonProc (theDialog, theItem)		/* outline the default button of a dialog */
	DialogPtr		theDialog;
	short			theItem;
{
	short			type;
	Rect			box;
	Handle			itemHdl;

	GetDItem (theDialog, kSetButtonID, &type, &itemHdl, &box);
	
	PenSize (3, 3);
	InsetRect (&box, -4, -4);
	FrameRoundRect (&box, 16, 16);
	PenNormal ();
	
} /* buttonProc */

/* ---------------------------------------------------------------------------------
	sepLineProc -	 draw a separation line in gray
	5.28.90kwgm
------------------------------------------------------------------------------------ */
pascal void
sepLineProc (theDialog, theItem)		/* draw gray line */
	DialogPtr		theDialog;
	short			theItem;
{
	short			type;
	Rect			box;
	Handle			itemHdl;
	
	GetDItem (theDialog, theItem, &type, &itemHdl, &box);
	
	PenPat (gray);
	MoveTo (box.left, box.top);
	LineTo (box.right, box.top);
	PenNormal ();

} /* sepLineProc */

/* ----------------------------------------------------------------------------------
	DLOGfilterProc1 -		called from inside of ModalDialog
	3.30.90kwgm				uses button 1 as default, button 2 as cancel
							processes Return, Enter and cmd .
------------------------------------------------------------------------------------- */
pascal Boolean
DLOGfilterProc1 (theDialog, theEvent, theItem)
	DialogPtr		theDialog;
	EventRecord		*theEvent;
	short			*theItem;
{
	short			type;
	Rect			box;
	char			c;
	long			endTicks;
	Boolean			result;
	Handle			item;
	
	c = (theEvent->message & charCodeMask);
	
	if (c == 13 || c == 3)		/* return or enter */
	{
		/* get the item data from the DialogMgr */
		GetDItem (theDialog, kSetButtonID, &type, &item, &box);
		if (type == (ctrlItem | btnCtrl))
		{
			HiliteControl (item, true);		/* flash the button push */
			Delay (8, &endTicks);
			HiliteControl (item, false);
		}
		*theItem = kSetButtonID;			/* simulate button push */
		theEvent->what = mouseDown;
		result = true;
	}
	else if (c == '.' && theEvent->modifiers & cmdKey)	/* cmd . */
	{
		GetDItem (theDialog, kCancelButtonID, &type, &item, &box);
		if (type == (ctrlItem | btnCtrl))
		{
			HiliteControl (item, true);
			Delay (8, &endTicks);
			HiliteControl (item, false);
		}
		*theItem = kCancelButtonID;
		theEvent->what = mouseDown;

		result = true;
	}
	else
		result = false;		/* tell ModalDialog that we did nothing */
			
	return (result);
	
} /* DLOGfilterProc1 */

/* ---------------------------------------------------------------------------------
	dialogTopLeft -		return a point which if used as the dialog's top left
	5.28.90kwgm			will center the dialog on the screen
------------------------------------------------------------------------------------ */
Point
dialogTopLeft (dialogID)
	short			dialogID;
{
	DialogPtr		theDialog;
	GrafPtr			savePort;
	Point			aPt, screenCenter;
	Rect			dialogRect;
	
	screenCenter.h = (gScreenRect.left + gScreenRect.right) >> 1;
	screenCenter.v = (gScreenRect.top + gScreenRect.bottom) >> 1;
	
	aPt.h = screenCenter.h - 100;		/* set up arbitrary pt */
	aPt.v = screenCenter.v - 80;

	GetPort (&savePort);
	
	if (theDialog = GetNewDialog (dialogID, 0L, (WindowPtr)-1L))
	{	
		dialogRect = ((WindowPtr)theDialog)->portRect;
		aPt.h = screenCenter.h - ((dialogRect.left + dialogRect.right) >> 1);
		aPt.v = screenCenter.v - ((dialogRect.top + dialogRect.bottom) >> 1);
		
		DisposDialog (theDialog);
	}
	
	SetPort (savePort);

	return (aPt);
	
} /* dialogTopLeft */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */