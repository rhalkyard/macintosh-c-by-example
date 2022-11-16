/* *****************************************************************************
	FILE: 			DialogUtil.c
	
	DESCRIPTION: 	Dialog box utilities
	
	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */

#include "AppConstants.h"
#include "DialogUtilPr.h"

/* --------------------------------------------------------------------------
	dialogHookProcs -	these hook procs do various things like
	3.30.90kwgm			highlight buttons, draw underlines, or handle
						keydown events in dialog boxes.
----------------------------------------------------------------------------- */
pascal void
buttonProc (theDialog, theItem)
	DialogPtr		theDialog;
	short			theItem;
{
	short			type;
	Rect			box;
	Handle			itemHdl;
	
	/* from IM-I, outline the default button */
	
	/* get the button's bounds rectangle - note we're getting the button
		outline, not the user item's rectangle */
	GetDItem (theDialog, kSetButtonID, &type, &itemHdl, &box);
	
	PenSize (3, 3);
	InsetRect (&box, -4, -4);
	FrameRoundRect (&box, 16, 16);
	PenNormal ();
	
} /* buttonProc */

/* ----------------------------------------------------------------------------------
	DLOGfilterProc1 -		uses button 1 as default, button 2 as cancel
	3.30.90kwgm				processes Return, Enter and cmd .
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
		GetDItem (theDialog, kSetButtonID, &type, &item, &box);
		if (type == (ctrlItem | btnCtrl))
		{
			HiliteControl (item, true);
			Delay (8, &endTicks);
			HiliteControl (item, false);
		}
		*theItem = kSetButtonID;
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
		result = false;
			
	/* 
		you can add more cases here, like supporting cmd X, V, and C for Cut, 
		Paste, and Copy, if you want your dialog to support the clipboard.
		(You also need to call the Dialog Manager routines DlgCut, DlgPaste, and
		DlgCopy to support this
	*/
	
	return (result);
	
} /* DLOGfilterProc1 */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */