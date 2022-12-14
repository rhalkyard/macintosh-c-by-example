/* *****************************************************************************
	FILE: 			AboutBox.c
	
	DESCRIPTION: 	AboutBox utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#include <stdio.h>

#include <Dialogs.h>
#include <Events.h>
#include <Sound.h>
#include <TextUtils.h>

#include "ThinkHelpers.h"

#include "BrowserConstants.h"
#include "StrRsrcDefs.h"

#include "DialogUtilPr.h"
#include "WindowUtilPr.h"

#include "AboutBoxPr.h"

/* ---------------------------  Local Prototypes  ----------------------------- */

static DialogPtr	drawAboutBox ( Boolean );

/* ----------------------------------------------------------------------------
	doAboutBox -	put up about box, wait for user to go away
	3.30.90kwgm
------------------------------------------------------------------------------- */
void 
doAboutBox ()
{
	EventRecord			theEvent;
	DialogPtr			theDialog;
	GrafPtr				savePort;
	
	GetPort (&savePort);

	if (theDialog = drawAboutBox (true))
	{
		/* wait for a key or mouse down */
		while (!GetNextEvent (keyDownMask + mDownMask, &theEvent))
			SystemTask();
		
		DisposDialog (theDialog);
	}
	
	SetPort (savePort);

} /* doAboutBox */

/* ----------------------------------------------------------------------------
	splashScreen -	put up about box, delay, go away automatically.
	3.30.90kwgm		used to introduce the program.
------------------------------------------------------------------------------- */
void 
splashScreen ()
{
	EventRecord			theEvent;
	DialogPtr			theDialog;
	GrafPtr				savePort;
	long				ticksNow;
	
	GetPort (&savePort);	/* save current port */

	if (theDialog = drawAboutBox (false))
	{
	
		Delay (120L, &ticksNow);	/* wait 2 seconds */
		
		DisposDialog (theDialog);
	}
	else
	{
		SysBeep (1);
		ExitToShell ();		/* probably can't open resource fork! */
	}
	
	SetPort (savePort);		/* restore saved port */

} /* splashScreen */

/* -------------------------------------------------------------------------
	drawAboutBox	-	do aboutbox display
	3.30.90kwgm
---------------------------------------------------------------------------- */
static DialogPtr
drawAboutBox (doMemSize)
	Boolean				doMemSize;
{
	register DialogPtr	theDialog;
	ControlHandle		cntlHdl;
	Size				sz;
	short				itemType;
	Rect				memBox;
	Str64				memStr, formatStr;

	/* get dialog ptr from resource file */
	if (!(theDialog = GetNewDialog (kAboutBoxDLOG, 0L, (WindowPtr)-1L)))
		return (0L);

	/*
		dialog window is invisible so that it can be centered
	*/

	centerWindow (theDialog);

	/* now make it visible */
	ShowHide (theDialog,true);
	DrawDialog (theDialog);

	if (doMemSize)		/* print a total memory avail message in about box */
	{
		SetPort (theDialog);	/* set this dialog as the current grafport */

		/* memBox : where to draw string */
		GetDItem (theDialog, kAboutMemBox, &itemType, (Handle *) &cntlHdl, &memBox);
		
		/* get the printf format string */
		GetIndString (formatStr, kNameStrRsrc, kAboutBoxMsgStr);
		PtoCstr (formatStr);
		
		/* create memory string */
		sz = FreeMem ();
		sprintf (memStr, formatStr, sz >> 10);
		CtoPstr (memStr);
	
		/* draw string as white on black */
		PenPat (&qd.white);
		TextFont (1);		/* 12 pt 'appfont' (usually geneva) */
		TextSize (12);
		TextMode (srcBic);	/* need this mode to draw white on blcak */
		
		MoveTo (memBox.left, memBox.bottom - 2);
		DrawString (memStr);
		
		PenNormal ();
	}
	
	return (theDialog);
	
} /* drawAboutBox */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies All Rights Reserved.
================================================================================ */

