/* *****************************************************************************
	FILE: 			WindowUtil.c
	
	DESCRIPTION: 	Window management utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#include "ThinkHelpers.h"

#include <Windows.h>

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

	/* get the point which centers the window */
	where.v = (scrHeight - (globalRect.bottom - globalRect.top)) / 2;
	where.h = (scrLength - (globalRect.right - globalRect.left)) / 2;
	
	/* put the window there */
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
	
	/* 
		when passed a pointer to and object, as in Rect *globalRect, 
		you need to dereference the pointer to store
		the data in the object, as in the following line:
	*/
	
	*globalRect = theWindow->portRect;
	
	/* now hang on to you hats! */
	LocalToGlobal (&(topLeft(*globalRect)));	/* convert top-left */
	LocalToGlobal (&(botRight(*globalRect)));	/* convert bottom-right */
	
#if 0
/*
		these two lines of code need explaination:
		
		the macros topLeft and botRight are defined in MacTypes.h
		they return either the top-left or bottom-right points 
		of a rectangle, in a way that looks like a Point data structure.
		
		Now, lets look at one of these lines from the inside out:
		
		Remember, you need to dereference a pointer to get at it's value,
		thus the *globalRect. And LocalToGlobal takes a VAR parameter,
		so we need to pass an address, thus the &
		
		Let's look at it in another, more readable way to do it:
		
		Point		aPt;		/* need to declare an auto Point */
		
		aPt.h = globalRect->left;	/* get top-left */
		aPt.v = globalRect->top;
		LocalToGlobal (&aPt);		/* convert it */
		globalRect->left = aPt.h;
		globalRect->top = aPt.v;
		
		aPt.h = globalRect->right;	/* get bottom-right */
		aPt.v = globalRect->bottom;
		LocalToGlobal (&aPt);		/* convert it */
		globalRect->right = aPt.h;
		globalRect->bottom = aPt.v;
		
		These ten lines do what the two line above do.
		
		Can you now appreciate why sometimes, and I underline the word 'sometimes',
		writing terse code is preferable?
*/
#endif
	
	SetPort (savePort);
	
	return (globalRect);
	
} /* getWinRect */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */
