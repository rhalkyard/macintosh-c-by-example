/* *****************************************************************************
	FILE: 			AboutBox.c
	
	DESCRIPTION: 	AboutBox utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press version
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#include "Version.h"

#ifdef V5
#include <stdio.h>
#endif

#ifdef V4
#include <stdio.h>
#endif

#ifdef V3
#include <Proto.h>
#endif
 
#ifdef V2
#include <Proto.h>
#include <Pascal.h>
#endif

#include "AppConstants.h"
#include "DialogUtilPr.h"
#include "WindowUtilPr.h"

#include "AboutBoxPr.h"

/* ---------------------------  Local Prototypes  ----------------------------- */

DialogPtr	drawAboutBox ( Boolean );

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
	
	GetPort (&savePort);		/* save the current port, whatever it is */

	if (theDialog = drawAboutBox (true))	/* draw the about box contents */
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
	
	GetPort (&savePort);

	if (theDialog = drawAboutBox (false))
	{
	
		Delay (60L, &ticksNow);	/* wait one second */
		
		DisposDialog (theDialog);
	}
	else
	{
		SysBeep (1);
		ExitToShell ();		/* probably can't open resource fork! */
	}
	
	SetPort (savePort);

} /* splashScreen */

/* -------------------------------------------------------------------------
	drawAboutBox	-	do aboutbox display
	3.30.90kwgm
---------------------------------------------------------------------------- */
static DialogPtr
drawAboutBox (doMemSize)
	Boolean doMemSize;
{
	register DialogPtr	theDialog;
	ControlHandle		cntlHdl;
	Size				sz;
	short				itemType;
	Rect				memBox;
	char				memStr [64], formatStr [64];

	if (!(theDialog = GetNewDialog (kAboutBoxDLOG, 0L, (WindowPtr)-1L)))
		return (0L);

	/* 
		Developer's trick:
		create your windows in ResEdit as invisible so that they can
		be centered on the screen before they're displayed
	*/

	centerWindow (theDialog);

	/* now make it visible */
	ShowHide (theDialog,true);
	DrawDialog (theDialog);

	if (doMemSize)		/* print a total memory avail message in about box */
	{
		SetPort (theDialog);	/* set this dialog as the current grafport */

		/* memBox is location of where to draw string */
		GetDItem (theDialog, kAboutMemBox, &itemType, &cntlHdl, &memBox);
		
		/* get the printf format string */
		GetIndString (formatStr, kNameStrRsrc, kAboutBoxMsgStr);
		PtoCstr (formatStr);
		
		/* create it */
		sz = FreeMem ();
		sprintf (memStr, formatStr, sz >> 10);
		CtoPstr (memStr);
	
		/* draw it in white on black */
		PenPat (white);
		TextFont (1);		/* 12 pt 'appfont (usually geneva) */
		TextSize (12);
		TextMode (srcBic);	/* need this mode to 'lift' black pixels */
		
		MoveTo (memBox.left, memBox.bottom - 2);
		DrawString (memStr);
		
		PenNormal ();
	}
	
	return (theDialog);
	
} /* drawAboutBox */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */

