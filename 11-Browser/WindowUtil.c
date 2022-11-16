/* *****************************************************************************
	FILE: 			WindowUtil.c
	
	DESCRIPTION: 	Window management utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.12.91 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#include "BrowserGlobals.h"

#include "BufMgrPr.h"
#include "DisplayPr.h"
#include "DocUtilPr.h"

#include "WindowUtilPr.h"

#define	kWindowOffset	12		/* pixel offset from top window */

/* ------------------  Local Prototypes  ---------------------------- */

void		setPortClip			( WindowPtr );
void		moveScrollBars		( WindowPtr );

pascal void	scrollWinProc		( ControlHandle, short );
void 		scrollDoc 			( DocPtr, ControlHandle, short, short );
void 		scrollTextDoc 		( DocPtr, ControlHandle, short, short );
void 		scrollBinDoc 		( DocPtr, ControlHandle, short, short );
void 		scrollByThumb		( DocPtr, ControlHandle, short );

	
/* --------------------------------------------------------------------------
	calcNewWinRect -	create a window Rect for a new document
----------------------------------------------------------------------------- */
Rect *
calcNewWinRect (Rect *newWinRectPtr)
{
	*newWinRectPtr = gWindowRect;
	OffsetRect (newWinRectPtr, kWindowOffset, GetMBarHeight() + kWindowOffset + 8);
	
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
	
	resizeTextDocContents (theWindow);		/* notify the document of the change */

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

	resizeTextDocContents (theWindow);		/* notify the document of the change */

	InvalRect (&theWindow->portRect);

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

/* ------------------------------------------------------------------------------------
	drawScrollBars -	draw the window's scroll bars
	11.20.90kwgm
--------------------------------------------------------------------------------------- */
void
drawScrollBars (DocPtr theDoc, Boolean activate)
{
	ControlHandle	theControl;
	long			ref;
	short			value;
	Rect			frameRect;
	Point			frameSize;
	
	if (!theDoc)
		return;
		
	setPortClip (theDoc);		/* clip out to port */
	
	if (ISTEXTDOC (theDoc))
	{
		DrawGrowIcon (theDoc);
		/* get frame size */
		makeFrameRect (theDoc, &frameRect);
		frameSize.h = frameRect.right - frameRect.left;
		frameSize.v = frameRect.bottom - frameRect.top;
	}

	/* get head of control list */
	theControl = ((WindowPeek)theDoc)->controlList;
	
	if ((theDoc == FrontWindow ()) && activate)
	{		
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
				if (theDoc->curScroll.v < theDoc->maxScroll.v)
				{
					if (ISBINDOC (theDoc))
						value = theDoc->curScroll.v;
					else
						value = ( (long)theDoc->curScroll.v * (long)kControlMax) / (long)theDoc->maxScroll.v;
				}
				else
					value = theDoc->maxScroll.v;

				HiliteControl (theControl, ISTEXTDOC(theDoc) ? ((theDoc->docExtent.v > frameSize.v) ? 0 : 255) :
											(theDoc->maxScroll.v >= 1 ? 0 : 255));
				SetCtlValue (theControl, value);
			}
			else if (ISTEXTDOC (theDoc))	/* text document v scroll bar */
			{
				/* get thumb value */
				if (theDoc->curScroll.h < theDoc->maxScroll.h)
					value = ( (long)theDoc->curScroll.h * (long)kControlMax) / (long)theDoc->maxScroll.h;
				else
					value = kControlMax;
					
				HiliteControl (theControl, (theDoc->docExtent.h > frameSize.h) ? 0 : 255);
				SetCtlValue (theControl, value);
			}
			else /* binary document and H scroll bar */
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

	DrawControls (theDoc);		/* Draw all controls in the window */

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
	
	if (ISTEXTDOC(theWindow))
		theRect->bottom -= (kScrollBarSize - 2);
	else
		theRect->bottom += 1;

	return (theRect);
	
} /* vScrollBarRect */

/* --------------------------------------------------------------------------
	invalScrollBars	-	invalidate the scrollbars
	4.24.90kwgm			erase the area if erase is true
----------------------------------------------------------------------------- */
void
invalScrollBars (theWindow, erase)
	WindowPtr			theWindow;
	Boolean				erase;
{
	Rect				scrollbarRect;
	
	if (ISTEXTDOC(theWindow))
	{
		hScrollBarRect (theWindow, &scrollbarRect);
		InsetRect (&scrollbarRect, -1, -1);
		scrollbarRect.right += kScrollBarSize;		/* get Grow box */
		
		if (erase)
			EraseRect (&scrollbarRect);
	
		InvalRect (&scrollbarRect);
	}
	
	vScrollBarRect (theWindow, &scrollbarRect);
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
Rect *
makeFrameRect (theWindow, frameRectPtr)
	WindowPtr	theWindow;
	Rect		*frameRectPtr;
{
	Rect		localRect;
	
	localRect = theWindow->portRect;
	
	localRect.right -= kScrollBarSize;
	if (ISTEXTDOC (theWindow))
		localRect.bottom -= kScrollBarSize;

	if (frameRectPtr)
		*frameRectPtr = localRect;

	return (&localRect);
	
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
	mBarHeight = GetMBarHeight ();

	/* get the screen size */
	scrLength = screenBits.bounds.right - screenBits.bounds.left;
	scrHeight = (screenBits.bounds.bottom - screenBits.bounds.top) - mBarHeight;

	where.v = (scrHeight - (globalRect.bottom - globalRect.top)) / 2 + mBarHeight;
	where.h = (scrLength - (globalRect.right - globalRect.left)) / 2;
	
	MoveWindow (theWindow, where.h, where.v, false);
	
} /* centerWindow */

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
	
	setPortClip (theDoc);
	
	switch (partCode) 
	{
		case inUpButton:
		case inDownButton:
			TrackControl (theControl, where, scrollWinProc);
			break;
		
		case inPageUp:
		case inPageDown:
			if (ISTEXTDOC (theDoc))
			{
				/* scroll by an amount the size of the current doc frame */
				makeFrameRect (theDoc, &frameRect);
				
				/* scale the scroll by the document's scroll value */
				if (GetCRefCon (theControl) == kHScrollTag)
					scrollValue = (frameRect.right - frameRect.left) / theDoc->scrollVal.h;
				else
					scrollValue = (frameRect.bottom - frameRect.top) / theDoc->scrollVal.v;
			}
			else
				scrollValue = 1;
	
			scrollDoc (theDoc, theControl, partCode, 1);
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
	scrollDoc -			the quintessential scrolling routine, scrollDoc is called for all
	1.20.91kwgm			document scrolling, from the scrollProc, or directly for
						the thumb and page scrolls	
----------------------------------------------------------------------------------- */
static void 
scrollDoc (theDoc, theControl, partCode, value)
	DocPtr				theDoc;
	ControlHandle		theControl;
	short				partCode, value;
{
	if (ISTEXTDOC(theDoc))
		scrollTextDoc (theDoc, theControl, partCode, value);
	else
		scrollBinDoc (theDoc, theControl, partCode, value);
}

/* --------------------------------------------------------------------------------
	scrollTextDoc -		the quintessential scrolling routine, scrollDoc is called for all
	5.20.90kwgm			document scrolling, from the scrollProc, or directly for
						the thumb and page scrolls	
----------------------------------------------------------------------------------- */
static void 
scrollTextDoc (theDoc, theControl, partCode, value)
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
		setFrameClip (theDoc, &frameRect);	/* clip to doc contents */
	
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
			
			BeginUpdate (theDoc);
			drawDocContents (theDoc);	/* note: mini update process */
			EndUpdate (theDoc);
			
			SetRectRgn (updateRgn, 0, 0, 0, 0);		/* clear out region */
		}
	
		setPortClip (theDoc);	/* widen clip to include scrollbars */
	
		/* adjust scroll bar appearance */
		SetCtlValue (theControl, hScroll ? theDoc->curScroll.h : theDoc->curScroll.v);
		SetCtlMax (theControl, hScroll ? theDoc->maxScroll.h : theDoc->maxScroll.v);

	} while (StillDown());

	if (updateRgn)
		DisposeRgn (updateRgn);

} /* scrollTextDoc */


/* --------------------------------------------------------------------------------
	scrollBinDoc -		scrollBinDoc pages the binary screen
	11.20.90kwgm
----------------------------------------------------------------------------------- */
static void 
scrollBinDoc (theDoc, theControl, partCode, value)
	DocPtr				theDoc;
	ControlHandle		theControl;
	short				partCode, value;
{
	Rect				frameRect;
	Boolean				scrolled;
	
	do
	{
		scrolled = false;
		if ((GetCRefCon (theControl)) == kVScrollTag)
		{
			switch (partCode)
			{
				case inPageUp:
				case inUpButton:
					if (theDoc->curScroll.v > 0)
					{
						prevFileBuffer (theDoc, value);
						theDoc->curScroll.v -= value;
						scrolled = true;
					}
					break;
				case inPageDown:
				case inDownButton:
					if (theDoc->curScroll.v < theDoc->maxScroll.v)
					{
						nextFileBuffer (theDoc, value);
						theDoc->curScroll.v += value;
						scrolled = true;
					}
					break;
			}
			
			if (scrolled)
			{
			
				setPortClip (theDoc);	/* widen clip to include scrollbars */
		
				SetCtlValue (theControl, theDoc->curScroll.v);
				SetCtlMax (theControl, theDoc->maxScroll.v);
				
				setFrameClip (theDoc, &frameRect);
	
				EraseRect (&frameRect);
				InvalRect (&frameRect);
				
				BeginUpdate (theDoc);
				drawDocContents (theDoc);	/* note: mini update process */
				EndUpdate (theDoc);
		
				setPortClip (theDoc);	/* widen clip to include scrollbars */
			}
		}
	} while (StillDown());

} /* scrollBinDoc */

/* ----------------------------------------------------------------------------------
	scrollByThumb -	scroll the doc deltaPage pages
	11.20.90kwgm
------------------------------------------------------------------------------------- */
static void 
scrollByThumb (DocPtr theDoc, ControlHandle theControl, short delta)
{
	short			partCode;
	
	if (delta)	/* if the thumb moved */
	{
		if (delta < 0)
		{
			partCode = inDownButton;	/* old thumb position greater than new */
			delta = -delta;				/* scroll an absolute value */
		}
		else
			partCode = inUpButton;		/* new position greater than old */
	
		if (ISTEXTDOC (theDoc))
		{
			if (GetCRefCon (theControl) == kHScrollTag)
				delta /= theDoc->scrollVal.h;
			else
				delta /= theDoc->scrollVal.v;
		}

		/* again, we call scroll doc to do the scrolling */
		scrollDoc (theDoc, theControl, partCode, delta);
	}
	
} /* scrollByThumb */

/* --------------------------------------------------------------------------------- 
	scrollWinProc -	scrollProc for scroll bars -  a very uninteresting routine that 
	5.20.90kwgm		structures the call to scrollDoc()
------------------------------------------------------------------------------------ */
static pascal void
scrollWinProc (ControlHandle theControl, short partCode)
{
	scrollDoc ((*theControl)->contrlOwner, theControl, partCode, 1);
}

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */
