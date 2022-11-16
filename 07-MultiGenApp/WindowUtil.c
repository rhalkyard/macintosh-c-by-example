/* *****************************************************************************
	FILE: 			WindowUtil.c
	
	DESCRIPTION: 	Window management utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	4.24.90	-	June 1990 Release: Revised for multiple window support
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#include <Controls.h>
#include <Quickdraw.h>
#include <Windows.h>

#include "ThinkHelpers.h"

#include "AppGlobals.h"

#include "WindowUtilPr.h"

/* -----------------------------  Local Constants  ------------------------------ */
#define	kWindowOffset	12		/* for each new window */


/* ------------------  Local Prototypes  ---------------------------- */

static void		moveScrollBars		( WindowPtr );
static void		setPortClip			( WindowPtr );

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
	
	scrLength = qd.screenBits.bounds.right - qd.screenBits.bounds.left;
	scrHeight = (qd.screenBits.bounds.bottom - qd.screenBits.bounds.top) - GetMBarHeight();

	/* get the screen size */
	where.v = (scrHeight - (globalRect.bottom - globalRect.top)) >> 1;
	where.h = (scrLength - (globalRect.right - globalRect.left)) >> 1;
	
	MoveWindow (theWindow, where.h, where.v, false);
	
} /* centerWindow */

/*---------------------------------------------------------------------------
	getWinRect -	returns window portRect in global coordinates
	3.30.90kwgm		used for centering the window
----------------------------------------------------------------------------- */
Rect *
getWinRect ( theWindow, globalRect)
	WindowPtr		theWindow;
	Rect			*globalRect;
{
	GrafPtr		savePort;
	
	GetPort(&savePort);
	SetPort(theWindow);
	
	*globalRect = theWindow->portRect;
	
	LocalToGlobal(&(topLeft(*globalRect)));
	LocalToGlobal(&(botRight(*globalRect)));
	
	SetPort(savePort);
	
	return (globalRect);
	
} /* getWinRect */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/*---------------------------------------------------------------------------
	calcNewWinRect -	create a window Rect for a new document, based on 
	4.24.90kwgm			current top window size
----------------------------------------------------------------------------- */
Rect *
calcNewWinRect (topWin, newWinRectPtr)
	WindowPtr		topWin;
	register Rect	*newWinRectPtr;
{
	GrafPtr			savePort;
	short			winHeight, winWidth, defWinHeight, defWinWidth;

	/* get top window rect */
	GetPort (&savePort);			
	*newWinRectPtr = topWin->portRect;
	
	SetPort (topWin);
	
	/* convert to desktop (global) space */
	LocalToGlobal (&(topLeft(*newWinRectPtr)));
	LocalToGlobal (&(botRight(*newWinRectPtr)));
	
	/* get window size */
	winWidth = newWinRectPtr->right - newWinRectPtr->left;
	winHeight = newWinRectPtr->bottom - newWinRectPtr->top;
	
	/* get screen size */
	defWinWidth = gWindowRect.right - gWindowRect.left;
	defWinHeight = gWindowRect.bottom - gWindowRect.top;
	
	/* if top window is an unusually large or small window, use gWindowRect */
	if (winWidth < (defWinWidth - 50) || winHeight < (defWinHeight - 50) ||
		newWinRectPtr->left < (gWindowRect.left - 20) ||
		newWinRectPtr->bottom < (gWindowRect.bottom - 30))
		*newWinRectPtr = gWindowRect;
	
	/* offset the rect by our stacking amount */
	OffsetRect (newWinRectPtr, kWindowOffset, kWindowOffset);
	
	/* keep the window within the main screen */
	newWinRectPtr->right = MIN(gScreenRect.right, newWinRectPtr->right);
	newWinRectPtr->bottom = MIN(gScreenRect.bottom, newWinRectPtr->bottom);
		
	SetPort (savePort);

	return (newWinRectPtr);
	
} /* calcNewWinRect */
/* ### 4.24.90 kwgm - new routine for multiGeneric */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* ------------------------------------------------------------------------------
	doGrowWindow -	resize the window by tracking user input
	4.24.90kwgm
--------------------------------------------------------------------------------*/
void 
doGrowWindow (theWindow, aPt)
	WindowPtr		theWindow;
	Point			aPt;
{
	long			newSize;
	Rect			limitRect;
	
	invalScrollBars (theWindow, true);	/* erase and invalidate old scroll bar area */
	
	/* maximum size of window to all of screen area (GrayRgn) */
	limitRect = gGrayRgnRect;
	limitRect.left = 48;	/* set so that minimum window's size is 48 by 48 */
	limitRect.top = 48;
	
	/* track user mouse and grow the window */
	newSize = GrowWindow (theWindow, aPt, &limitRect);
	SizeWindow (theWindow, LoWord (newSize), HiWord (newSize), true);
		
	moveScrollBars (theWindow);		/* relocate scroll bars to new window bounds */
	
	invalScrollBars (theWindow, true);	/* erase and invalidate new scroll bar area */

} /* doGrowWindow */
/* ### 4.24.90 kwgm - new routine for multiGeneric */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* ------------------------------------------------------------------------------
	doZoomBox -		zoom the window after mouse in zoom-box
	4.24.90kwgm
--------------------------------------------------------------------------------- */
void
doZoomBox (theWindow, partCode)
	WindowPtr		theWindow;
	short			partCode;
{
	GrafPtr			savePort;
	
	GetPort (&savePort);
	SetPort (theWindow);

	ZoomWindow (theWindow, partCode, false);	/* zoom the window */

	moveScrollBars (theWindow);		/* move to new window edges */

	InvalRect (&theWindow->portRect);	/* setup for redraw */

	SetPort (savePort);
	
} /* doZoomBox */
/* ### 4.24.90 kwgm - new routine for multiGeneric */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* ----------------------------------------------------------------------
	clickZoomWindow	-	zoom or un-zoom the window
	4.24.90kwgm			called when there is a dbl-click in title bar
------------------------------------------------------------------------- */
void
clickZoomWindow (theWindow)
	WindowPtr		theWindow;
{
	long  			newSize;
	WStateData		**wDataHdl;
	Rect			userState, portRect;

	/* See IM-IV for WStateData description */
	wDataHdl = ((WindowPeek)theWindow)->dataHandle;
	userState = (*wDataHdl)->userState;
	portRect = theWindow->portRect;
	
	/* convert to window manager port coordinates */
	LocalToGlobal (&(topLeft(portRect)));
	LocalToGlobal (&(botRight(portRect)));
	
	/* if zoomed, then un-zoom , else zoom */
	if (EqualRect (&userState, &portRect))
		doZoomBox (theWindow, inZoomOut);
	else
		doZoomBox (theWindow, inZoomIn);

} /* clickZoomWindow */
/* ### 4.24.90 kwgm - new routine for multiGeneric */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* ------------------------------------------------------------------------------------
	drawScrollBars -	draw the document's scroll bars
	4.24.90kwgm
--------------------------------------------------------------------------------------- */
void
drawScrollBars (theDoc, activate)
	DocPtr			theDoc;
	Boolean			activate;
{
	ControlHandle	theControl;
	long			ref;
	short			value;
	Point			curScroll, maxScroll, docExtent, frameSize;
	Rect			frameRect;
	
	setPortClip (theDoc);		/* clip out to port */
	DrawGrowIcon (theDoc);
	
	theControl = ((WindowPeek)theDoc)->controlList;
	
	if ((theDoc == FrontWindow ()) && activate)
	{
		/* get frame size */
		makeFrameRect (theDoc, &frameRect);
		frameSize.h = frameRect.right - frameRect.left;
		frameSize.v = frameRect.bottom - frameRect.top;
		
		/* use temp variables */
		maxScroll = theDoc->maxScroll;
		curScroll = theDoc->curScroll;
		docExtent = theDoc->docExtent;

		while (theControl)	/* draw each scroll bar and thumb at proper value */
		{
			ref = GetCRefCon (theControl);
			if ( ref == kVScrollTag )
			{
				if (curScroll.v < maxScroll.v)
					value = ( (long)curScroll.v * (long)kControlMax) / (long)maxScroll.v;
				else
					value = kControlMax;
				HiliteControl (theControl, (docExtent.v > frameSize.v) ? 0 : 255);
				SetCtlValue (theControl, value);
			}	
			else if ( ref == kHScrollTag )
			{
				if (curScroll.h < maxScroll.h)
					value = ( (long)curScroll.h * (long)kControlMax) / (long)maxScroll.h;
				else
					value = kControlMax;
				HiliteControl (theControl, (docExtent.h > frameSize.h) ? 0 : 255);
				SetCtlValue (theControl, value);
			}
			else
				HiliteControl (theControl, 0);
				
			ShowControl (theControl);
			theControl = (*theControl)->nextControl;
		}
	}
	else	/* draw unhilighted scroll bars */
	{
		while (theControl)
		{
			HiliteControl (theControl, 255);
			ShowControl (theControl);
			theControl = (*theControl)->nextControl;
		}
	}

	DrawControls (theDoc);

} /* drawScrollBars */
/* ### 4.24.90 kwgm - new routine for multiGeneric */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* ------------------------------------------------------------------------------------
	moveScrollBars -	redraw the scroll bars after a window resizes
	4.24.90kwgm
---------------------------------------------------------------------------------------*/
static void 
moveScrollBars (theWindow)
	register WindowPtr		theWindow;
{
	long					ref;
	ControlHandle			controlList;
	Rect					portRect, sbRect;
	
	setPortClip (theWindow);
	
	controlList = ((WindowPeek)theWindow)->controlList;
	portRect = theWindow->portRect;
	
	while (controlList)		/* move each control */
	{
		HideControl (controlList);
		ref = GetCRefCon (controlList);
		if ( ref == kVScrollTag)		/* vertical control */
		{
			vScrollBarRect (theWindow, &sbRect);
			MoveControl (controlList, portRect.right - (kScrollBarSize - 1), portRect.top - 1);
			SizeControl (controlList, kScrollBarSize, sbRect.bottom - sbRect.top);
		}
		else if (ref == kHScrollTag)	/* horizontal control */
		{
			hScrollBarRect (theWindow, &sbRect);
			MoveControl (controlList, portRect.left - 1, portRect.bottom - (kScrollBarSize - 1));
			SizeControl (controlList, sbRect.right - sbRect.left, kScrollBarSize);
		}
			
		controlList = (*controlList)->nextControl;
	}

} /* moveScrollBars */
/* ### 4.24.90 kwgm - new routine for multiGeneric */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* --------------------------------------------------------------------------
	hScrollBarRect	-	calculate the horizontal scroll bar rect
	4.24.90kwgm
----------------------------------------------------------------------------- */
Rect *
hScrollBarRect (theWindow, theRect)
	WindowPtr			theWindow;
	Rect				*theRect;
{
	*theRect = theWindow->portRect;
	
	theRect->left -= 1;
	theRect->top = theRect->bottom - (kScrollBarSize - 1);
	theRect->right -= (kScrollBarSize - 2);
	theRect->bottom += 1;
	
	return (theRect);
	
} /* hScrollBarRect */
/* ### 4.24.90 kwgm - new routine for multiGeneric */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* --------------------------------------------------------------------------
	vScrollBarRect	-	calculate the vertical scroll bar rect
	4.24.90kwgm
----------------------------------------------------------------------------- */
Rect *
vScrollBarRect (theWindow, theRect)
	WindowPtr			theWindow;
	register Rect		*theRect;
{
	*theRect = theWindow->portRect;

	theRect->left = theRect->right - (kScrollBarSize - 1);
	theRect->top -= 1;
	theRect->right += 1;
	theRect->bottom -= (kScrollBarSize - 2);

	return (theRect);
	
} /* vScrollBarRect */
/* ### 4.24.90 kwgm - new routine for multiGeneric */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* --------------------------------------------------------------------------
	invalScrollBars	-	invalidate the scrollbars and grow box area
	4.24.90kwgm			erase the area if erase is true
----------------------------------------------------------------------------- */
void
invalScrollBars (theWindow, erase)
	WindowPtr			theWindow;
	Boolean				erase;
{
	Rect				scrollbarRect;
	
	hScrollBarRect (theWindow, &scrollbarRect);
	InsetRect (&scrollbarRect, -1, -1);
	
	if (erase)
		EraseRect (&scrollbarRect);

	InvalRect (&scrollbarRect);
	
	vScrollBarRect (theWindow, &scrollbarRect);
	scrollbarRect.bottom += kScrollBarSize;
	InsetRect (&scrollbarRect, -1, -1);

	if (erase)
		EraseRect (&scrollbarRect);

	InvalRect (&scrollbarRect);
			
} /* invalScrollBars */
/* ### 4.24.90 kwgm - new routine for multiGeneric */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* ------------------------------------------------------------------------
	setPortClip	-	set the clipping rectangle to the port rect
	6/1/90kwgm
--------------------------------------------------------------------------- */
static void
setPortClip (theWin)
	WindowPtr		theWin;
{
	ClipRect (&theWin->portRect);
}
/* ### 4.24.90 kwgm - new routine for multiGeneric */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* --------------------------------------------------------------------------------
	makeFrameRect -	create the window frame rectangle, ie, the content - scroll bar
					areas
----------------------------------------------------------------------------------- */
Rect *
makeFrameRect (theWindow, frameRectPtr)
	WindowPtr	theWindow;
	Rect		*frameRectPtr;
{
	Rect		localRect;
	
	localRect = theWindow->portRect;		/* port rect */
	
	localRect.right -= kScrollBarSize;		/* minus the scroll bars */
	localRect.bottom -= kScrollBarSize;
	
	if (frameRectPtr)
		*frameRectPtr = localRect;

	return (frameRectPtr);
	
} /* makeFrameRect */
/* ### 4.24.90 kwgm - new routine for multiGeneric */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* --------------------------------------------------------------------------
	setFrameClip -	set the port's clip rect to the content region of the window
					minus the scroll bar area
----------------------------------------------------------------------------- */
void
setFrameClip (theWindow, frameRectPtr)
	WindowPtr		theWindow;
	Rect			*frameRectPtr;
{
	Rect			frameRect;
	
	ClipRect (makeFrameRect (theWindow, &frameRect));
	
	if (frameRectPtr)
		*frameRectPtr = frameRect;
	
} /* setFrameClip */
/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */
