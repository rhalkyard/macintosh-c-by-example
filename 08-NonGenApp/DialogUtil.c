/* *****************************************************************************
	FILE: 			DialogUtil.c
	
	DESCRIPTION: 	Dialog box utilities
	
	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.20.90 - 	July 1990 MacUser Release: No Changes
	4.24.90 - 	June 1990 MacUser Release: No Changes
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

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */