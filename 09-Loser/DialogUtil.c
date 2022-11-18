/* *****************************************************************************
	FILE: 			DialogUtil.c
	
	DESCRIPTION: 	Generic dialog box utilities
	
	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	05/28/90	-	Sept 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#include <Dialogs.h>
#include <Sound.h>
#include <TextUtils.h>

#include "AppConstants.h"
#include "AppGlobals.h"
#include "StrRsrcDefs.h"

#include "WindowUtilPr.h"
#include "DialogUtilPr.h"

#define			kUserType 		128

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
	
	/* get the dialog template and read the window rectangle size */
	if (theDialog = GetNewDialog (dialogID, 0L, (WindowPtr)-1L))
	{	
		dialogRect = ((WindowPtr)theDialog)->portRect;
		
		/* adjust aPt to the screen size minus half the window */
		aPt.h = screenCenter.h - ((dialogRect.left + dialogRect.right) >> 1);
		aPt.v = screenCenter.v - ((dialogRect.top + dialogRect.bottom) >> 1);
		
		DisposDialog (theDialog);
	}
	
	SetPort (savePort);

	return (aPt);
	
} /* dialogTopLeft */

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
	
	if (type & kUserType)
	{
		PenPat (&qd.gray);
		MoveTo (box.left, box.top);
		LineTo (box.right, box.top);
		PenNormal ();
	}

} /* sepLineProc */

/* ---------------------------------------------------------------------------------
	buttonProc -	 outline a dialog button
	5.28.90kwgm
------------------------------------------------------------------------------------ */
pascal void
buttonProc (theDialog, theItem)		/* from IM */
	DialogPtr		theDialog;
	short			theItem;
{
	short			type;
	Rect			box;
	Handle			itemHdl;
	
	GetDItem (theDialog, kSetButtonID, &type, &itemHdl, &box);
	PenSize (3,3);				
	InsetRect (&box,-4,-4);
	FrameRoundRect (&box,16,16);
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
	ControlHandle	item;
	Rect			box;
	char			c;
	long			endTicks;
	Boolean			result;
	
	c = (theEvent->message & charCodeMask);
	
	if (c == 13 || c == 3)		/* return or enter */
	{
		GetDItem (theDialog, kSetButtonID, &type, (Handle *) &item, &box);
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
	else if (c == '.' && theEvent->modifiers & cmdKey)
	{
		GetDItem (theDialog, kCancelButtonID, &type, (Handle *) &item, &box);
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
			
	return (result);
	
} /* DLOGfilterProc1 */

/* -------------------------------------------------------------------------------
	doNumAlert -		print an advisory
	5.28.90kwgm
---------------------------------------------------------------------------------- */
void
doNumAlert (stringNo)
	short			stringNo;
{
	DialogPtr		theDialog;
	Str255			errorStr;
	short			theItem, itemType;
	GrafPtr			savePort;
	Handle			buttonHdl;
	Rect			box;
	
	GetPort (&savePort);

	GetIndString (errorStr, kMsgStrID, stringNo);

	if (theDialog = GetNewDialog (kMsgDLOG, 0L, (WindowPtr)-1L))
	{
		
		SysBeep (1);

		GetDItem (theDialog, kOutlineButtonID, &itemType, &buttonHdl, &box);
		SetDItem (theDialog, kOutlineButtonID, itemType, (Handle) buttonProc, &box);

		ParamText (errorStr, kNulPascalStr, kNulPascalStr, kNulPascalStr);
		centerWindow (theDialog);
		ShowHide (theDialog, true);
		
		ModalDialog (DLOGfilterProc1, &theItem);
		
		DisposDialog (theDialog);
	}
	
	SetPort (savePort);
	
} /* doNumAlert */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */