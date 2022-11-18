/* *****************************************************************************
	FILE: 			WindowUtil.c
	
	DESCRIPTION: 	Window management utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.17.90	-	July 1990 Release: 
					- Revised to support text and PICT scrolling
	4.24.90	-	June 1990 Release: Revised for multiple window support
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#include <Controls.h>
#include <ControlDefinitions.h>
#include <Quickdraw.h>
#include <Windows.h>

#include "ThinkHelpers.h"

#include "AppGlobals.h"

/* ### kwgm 5.17.90 */
#include "DisplayPr.h"
#include "DocUtilPr.h"
/* ### kwgm 5.17.90 */

#include "WindowUtilPr.h"

#define	kWindowOffset	12		/* pixel offset from top window */

/* ------------------  Local Prototypes  ---------------------------- */

static void		moveScrollBars		( WindowPtr );
static void		setPortClip			( WindowPtr );

/* ### kwgm 5.17.90 */
static pascal void	scrollWinProc		( ControlHandle, short );
static void 		scrollDoc 			( DocPtr, ControlHandle, short, short );
static void 		scrollByThumb		( DocPtr, ControlHandle, short );
/* ### kwgm 5.17.90 */


	
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

/* ------------------------------------------------------------------------------
	doGrowWindow -	resize the window by tracking user input
	4.24.90kwgm
	5.20.90kwgm		modified for scroll bar support
--------------------------------------------------------------------------------*/
void 
doGrowWindow (theWindow, aPt)
	WindowPtr		theWindow;
	Point			aPt;
{
	long			newSize;
	Rect			limitRect;
	
	invalScrollBars (theWindow, true);	/* erase and invalidate old scroll bar area */
	
	/* limit size of window to the available screen */
	limitRect = gGrayRgnRect;
	limitRect.left = 48;	/* minimum window size */
	limitRect.top = 48;
	
	/* track user mouse and grow the window */
	newSize = GrowWindow (theWindow, aPt, &limitRect);
	SizeWindow (theWindow, LoWord (newSize), HiWord (newSize), true);
		
	moveScrollBars (theWindow);		/* relocate scroll bars to new window bounds */
	
	invalScrollBars (theWindow, true);	/* erase and invalidate new scroll bar area */
	
/* ### kwgm 5.17.90 */
	resizeDocContents ((DocPtr) theWindow);		/* notify the document of the change */
/* ### kwgm 5.17.90 */

} /* doGrowWindow */

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

	ZoomWindow (theWindow, partCode, false);

	moveScrollBars (theWindow);

	InvalRect (&theWindow->portRect);

/* ### kwgm 5.17.90 */
	resizeDocContents ((DocPtr) theWindow);		/* notify the document of the change */
/* ### kwgm 5.17.90 */

	SetPort (savePort);
	
} /* doZoomBox */

/* ----------------------------------------------------------------------
	clickZoomWindow	-	zoom or un-zoom the window
	4.24.90kwgm			called when there is a dbl-click in title bar
------------------------------------------------------------------------- */
void
clickZoomWindow (theWindow)
	WindowPtr		theWindow;
{
	long  				newSize;
	WStateDataHandle	wDataHdl;
	Rect				userState, portRect;

	/* See IM-IV for WStateData description */
	wDataHdl = (WStateDataHandle) ((WindowPeek)theWindow)->dataHandle;
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

/* ------------------------------------------------------------------------------------
	drawScrollBars -	draw the window's scroll bars
	6/1/90kwgm
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
	
	if (!theDoc)
		return;
		
	setPortClip ((WindowPtr) theDoc);		/* clip out to port */
	DrawGrowIcon ((WindowPtr) theDoc);
	
	/* get head of control list */
	theControl = (ControlHandle) ((WindowPeek)theDoc)->controlList;
	
	if ((theDoc == (DocPtr) FrontWindow ()) && activate)
	{
		/* get frame size */
		makeFrameRect ((WindowPtr) theDoc, &frameRect);
		frameSize.h = frameRect.right - frameRect.left;
		frameSize.v = frameRect.bottom - frameRect.top;
		
		/* use temp variables */
		maxScroll = theDoc->maxScroll;
		curScroll = theDoc->curScroll;
		docExtent = theDoc->docExtent;
		
		
		/*
			Controls are kept as a linked list. Run the list, calculating
			the proper thumb positions if the control is a scroll bar,
			hilighting or unhilighting the control based on the activate
			parameter
		*/ 

		while (theControl)	/* draw each scroll bar and thumb at proper value */
		{
			ref = GetCRefCon (theControl);	/* scroll bar tag kept here */
			if ( ref == kVScrollTag )
			{
				/* get thumb value */
				if (curScroll.v < maxScroll.v)
					value = ( (long)curScroll.v * (long)kControlMax) / (long)maxScroll.v;
				else
					value = kControlMax;
				HiliteControl (theControl, (docExtent.v > frameSize.v) ? 0 : 255);
				SetCtlValue (theControl, value);
			}	
			else if ( ref == kHScrollTag )
			{
				/* get thumb value */
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

	DrawControls ((WindowPtr) theDoc);		/* Draw all controls in the window */

} /* drawScrollBars */

/* -----------------------------------------------------------------------------------
	moveScrollBars -	redraw the scroll bars after a window resizes
	4.24.90kwgm
-------------------------------------------------------------------------------------- */
static void 
moveScrollBars (theWindow)
	register WindowPtr		theWindow;
{
	long					ref;
	ControlHandle			controlList;
	Rect					portRect, sbRect;
	
	setPortClip (theWindow);
	
	controlList = (ControlHandle) ((WindowPeek)theWindow)->controlList;
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

/* --------------------------------------------------------------------------
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
	
	LocalToGlobal(&(topLeft(*globalRect)));
	LocalToGlobal(&(botRight(*globalRect)));
	
	SetPort (savePort);
	
	return (globalRect);
	
} /* getWinRect */

/* ------------------------------------------------------------------------
	setPortClip	-	set the clipping rectangle to the port rect
	4.24.90kwgm
--------------------------------------------------------------------------- */
static void
setPortClip (theWin)
	WindowPtr		theWin;
{
	if (theWin)
		ClipRect (&theWin->portRect);
}

/* --------------------------------------------------------------------------------
	makeFrameRect -	create the window frame rectangle, ie, the content - scroll bar
	4.24.90kwgm		areas
----------------------------------------------------------------------------------- */
void
makeFrameRect (theWindow, frameRectPtr)
	WindowPtr	theWindow;
	Rect		*frameRectPtr;
{
	Rect		localRect;
	
	localRect = theWindow->portRect;
	
	localRect.right -= kScrollBarSize;
	localRect.bottom -= kScrollBarSize;
	
	if (frameRectPtr)
		*frameRectPtr = localRect;
	
} /* makeFrameRect */

/* --------------------------------------------------------------------------
	setFrameClip -	set the port's clip rect to the content region of the window
	4.24.90kwgm		minus the scroll bar area
----------------------------------------------------------------------------- */
void
setFrameClip (theWindow, frameRectPtr)
	WindowPtr		theWindow;
	Rect			*frameRectPtr;
{
	Rect			frameRect;
	
	makeFrameRect (theWindow, &frameRect);
	ClipRect (&frameRect);
	
	if (frameRectPtr)
		*frameRectPtr = frameRect;
	
} /* setFrameClip */

/* ----------------------------------------------------------------------------
	centerWindow -	calculate the left, top position of a centered window
	3.30.90kwgm		and move it to there
	
	5.17.90kwgm		modified to accomodate variable sized menu bar
------------------------------------------------------------------------------- */
void
centerWindow (theWindow)
	WindowPtr		theWindow;
{
	short			scrLength, scrHeight, mBarHeight;
	Rect			globalRect;
	Point			where;

	/* get the window rect in global coordinates */
	getWinRect (theWindow, &globalRect);
/* ### kwgm 5.17.90 */
	mBarHeight = GetMBarHeight();
/* ### kwgm 5.17.90 */

	/* get the screen size */
	scrLength = qd.screenBits.bounds.right - qd.screenBits.bounds.left;
/* ### kwgm 5.17.90 */
	scrHeight = (qd.screenBits.bounds.bottom - qd.screenBits.bounds.top) - mBarHeight;

	where.v = (scrHeight - (globalRect.bottom - globalRect.top)) / 2 + mBarHeight;
/* ### kwgm 5.17.90 */
	where.h = (scrLength - (globalRect.right - globalRect.left)) / 2;
	
	MoveWindow (theWindow, where.h, where.v, false);
	
} /* centerWindow */

/* ### kwgm 5.17.90 */
/* ============================  SCROLLING UTILS  =========================== */

/* ------------------------------------------------------------------------------------
	mouseInScroll -		react to mouse down in a window's scroll bars
	5.20.90kwgm
--------------------------------------------------------------------------------------*/
void
mouseInScroll (theDoc, theControl, partCode, where)
	DocPtr			theDoc;
	ControlHandle	theControl;
	short			partCode;
	Point			where;
{
	Rect			frameRect;
	short			oldThumb, newThumb, scrollValue;
	
	setPortClip ((WindowPtr) theDoc);
	switch (partCode) 
	{
		case inUpButton:
		case inDownButton:
			TrackControl (theControl, where, scrollWinProc);
			break;
		
		case inPageUp:
		case inPageDown:
			/* scroll by an amount the size of the current doc frame */
			makeFrameRect ((WindowPtr) theDoc, &frameRect);
			
			/* scale the scroll by the document's scroll value */
			if (GetCRefCon (theControl) == kHScrollTag)
				scrollValue = (frameRect.right - frameRect.left) / theDoc->scrollVal.h;
			else
				scrollValue = (frameRect.bottom - frameRect.top) / theDoc->scrollVal.v;

			scrollDoc (theDoc, theControl, partCode, scrollValue);
			break;
			
		case inThumb:
			oldThumb = GetCtlValue (theControl);		/* current thumb */
			TrackControl (theControl, where, 0L);		/* user feedback */
			newThumb = GetCtlValue (theControl);		/* new value */
			
			scrollByThumb (theDoc, theControl, oldThumb - newThumb);
			break;
	}
	
} /* mouseInScroll */

/* --------------------------------------------------------------------------------
	scrollDoc -		the quintessential scrolling routine, scrollDoc is called for all
	5.20.90kwgm		document scrolling, from the scrollProc, or directly for
					the thumb and page scrolls	
----------------------------------------------------------------------------------- */
static void 
scrollDoc (theDoc, theControl, partCode, value)
	DocPtr				theDoc;
	ControlHandle		theControl;
	short				partCode, value;
{
	register short		hScroll, vScroll;
	Rect				frameRect;
	long				ref;
	RgnHandle			updateRgn;
	
	/* we need to know what scroll bar, horiz or vert, that we're dealing with */
	ref = GetCRefCon (theControl);
	
	/* assign scroll pixel value to appropriate scroll variable */
	hScroll = (ref == kHScrollTag) ? (value * theDoc->scrollVal.h) : 0;
	vScroll = (ref == kVScrollTag) ? (value * theDoc->scrollVal.v) : 0;
	
	/* we'll need this region in ScrollRect */
	if (!(updateRgn = NewRgn()))
		return;

	/* we loop here while the mouse stays down */
	do
	{
		setFrameClip ((WindowPtr) theDoc, &frameRect);	/* clip to doc contents */
	
		switch (partCode)
		{
			case inPageUp:
			case inUpButton:
				/* adjust scroll value at the top (or left) boundary */
				if (vScroll && theDoc->curScroll.v - vScroll < 0)
					vScroll = theDoc->curScroll.v;
				else if (hScroll && theDoc->curScroll.h - hScroll < 0)
					hScroll = theDoc->curScroll.h;
	
				/* if we have a scroll value */
				if (vScroll || hScroll)
				{
					/* scroll the document */
					ScrollRect (&frameRect, hScroll, vScroll, updateRgn);
	
					/* adjust document's current scroll */
					if (hScroll)
						theDoc->curScroll.h -= hScroll;
					else if (vScroll)
						theDoc->curScroll.v -= vScroll;
				}
				break;
	
			case inPageDown:
			case inDownButton:
				/* adjust the scroll value at the bottom (or right) boundary */
				if (vScroll && (vScroll + theDoc->curScroll.v) > theDoc->maxScroll.v)
					vScroll = theDoc->maxScroll.v - theDoc->curScroll.v;
				else if (hScroll && (hScroll + theDoc->curScroll.h) > theDoc->maxScroll.h)
					hScroll = theDoc->maxScroll.h - theDoc->curScroll.h;
					
				if (vScroll || hScroll)
				{
					ScrollRect (&frameRect, -hScroll, -vScroll, updateRgn);
					if (hScroll)
						theDoc->curScroll.h += hScroll;
					else if (vScroll)
						theDoc->curScroll.v += vScroll;
				}
				break;
		}

		if (!EmptyRgn (updateRgn))	/* we scrolled */
		{
			InvalRgn (updateRgn);
			
			BeginUpdate ((WindowPtr) theDoc);
			drawDocContents (theDoc);	/* note: mini update process */
			EndUpdate ((WindowPtr) theDoc);
			
			SetRectRgn (updateRgn, 0, 0, 0, 0);		/* clear out region */
		}
	
		setPortClip ((WindowPtr) theDoc);	/* widen clip to include scrollbars */
	
		/* adjust scroll bar appearance */
		SetCtlValue (theControl, hScroll ? theDoc->curScroll.h : theDoc->curScroll.v);
		SetCtlMax (theControl, hScroll ? theDoc->maxScroll.h : theDoc->maxScroll.v);

	} while (StillDown());

	if (updateRgn)
		DisposeRgn (updateRgn);

} /* scrollDoc */

/* ----------------------------------------------------------------------------------
	scrollByThumb -	passed a delta value for the thumb in pixels, compute the
	5.20.90kwgm		pixels to scroll and do it
------------------------------------------------------------------------------------- */
static void 
scrollByThumb (theDoc, theControl, deltaPix)
	DocPtr			theDoc;
	ControlHandle	theControl;
	short			deltaPix;
{
	short			partCode;
	
	if (deltaPix)	/* if the thumb moved */
	{
		if (deltaPix < 0)
		{
			partCode = inDownButton;	/* old thumb position greater than new */
			deltaPix = -deltaPix;		/* scroll an absolute value */
		}
		else
			partCode = inUpButton;		/* new position greater than old */
			
		if (ISTEXTDOC(theDoc))		/* special handling for text doc */
		{
			if (GetCRefCon (theControl) == kHScrollTag)
				deltaPix /= theDoc->scrollVal.h;
			else
				deltaPix /= theDoc->scrollVal.v;
		}
	
		/* again, we call scroll doc to do the scrolling */
		scrollDoc (theDoc, theControl, partCode, deltaPix);
	}
	
} /* scrollByThumb */

/* --------------------------------------------------------------------------------- 
	doScrollWin -	scrollProc for scroll bars -  a very uninteresting routine that 
	5.20.90kwgm		structures the call to scrollDoc()
------------------------------------------------------------------------------------ */
static pascal void
scrollWinProc (theControl, partCode)
	ControlHandle		theControl;
	short				partCode;
{
	scrollDoc ((DocPtr) (*theControl)->contrlOwner, theControl, partCode, 1);
}

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */
