/* *****************************************************************************
	FILE: 			WindowUtil.c
	
	DESCRIPTION: 	Window management utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.28.90	-	Sept 1990 MacUser Release (Loser)
	3.30.90 -	May 1990 MacUser Release (miniGenApp)
	==========================================================

   ***************************************************************************** */

#include <Windows.h>

#include "ThinkHelpers.h"

#include "WindowUtilPr.h"

/* ----------------------------------------------------------------------------
	centerWindow -	calculate the left, top position of a centered window
	3.30.90kwgm		and move it to there
------------------------------------------------------------------------------- */
void
centerWindow (theWindow)
	WindowPtr		theWindow;
{
	short			scrLength, scrHeight;
	Rect			globalRect;
	Point			where;

	/* get the window rect in global coordinates */
	getWinRect (theWindow, &globalRect);
	
	/* get the screen size */
	scrLength = qd.screenBits.bounds.right - qd.screenBits.bounds.left;
	scrHeight = (qd.screenBits.bounds.bottom - qd.screenBits.bounds.top) - GetMBarHeight();

	where.v = (scrHeight - (globalRect.bottom - globalRect.top)) / 2;
	where.h = (scrLength - (globalRect.right - globalRect.left)) / 2;
	
	MoveWindow (theWindow, where.h, where.v, false);
	
} /* centerWindow */
	
/*-----------------------------------------------------------------------------
	getWinRect -	returns window portRect in global coordinates
	3.30.90kwgm		used for centering the window
----------------------------------------------------------------------------- */
Rect *
getWinRect (theWindow, globalRect)
	WindowPtr		theWindow;
	Rect			*globalRect;
{
	GrafPtr		savePort;
	
	GetPort (&savePort);
	SetPort (theWindow);
	
	*globalRect = theWindow->portRect;
	
	LocalToGlobal (&(topLeft(*globalRect)));	/* convert top-left */
	LocalToGlobal (&(botRight(*globalRect)));	/* convert bottom-right */
		
	SetPort (savePort);
	
	return (globalRect);
	
} /* getWinRect */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */
