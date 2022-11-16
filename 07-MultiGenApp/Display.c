/* *****************************************************************************
	FILE: 			Display.c
	
	DESCRIPTION: 	Drawing functions

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	4.26.90	-	June 1990 MacUser Release (modified for multiple windows)
	3.30.90 -	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#include "AppGlobals.h"

#include "WindowUtilPr.h"
#include "DisplayPr.h"


/* ### 4.24.90kwgm - moved to WindowUtil.c */
#if 0
/* --------------------------------------------------------------------------------
	makeFrameRect -	create the window frame rectangle, ie, the content - scroll bar
	3.30.90kwgm		areas
----------------------------------------------------------------------------------- */
Rect *
makeFrameRect (theWindow, frameRectPtr)
	WindowPtr	theWindow;
	Rect		*frameRectPtr;
{
	Rect		localRect;
	
	localRect = theWindow->portRect;	/* get port rect */
	
	localRect.right -= kScrollBarSize;	/* take out scroll bars */
	localRect.bottom -= kScrollBarSize;
	
	if (frameRectPtr)
		*frameRectPtr = localRect;

	return (&localRect);
	
} /* makeFrameRect */

/* --------------------------------------------------------------------------
	setFrameClip -	set the port's clip rect to the content region of the window
	3.30.90kwgm		minus the scroll bar area
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
#endif
/* ### 4.24.90kwgm - moved */

/* ### 4.24.90kwgm - completely redone for multiGeneric */
/*---------------------------------------------------------------------------------
	drawDocContents -	draw the contents of theDoc - you can put your own drawing 
	4.24.90kwgm			routine in here
----------------------------------------------------------------------------------*/
void 
drawDocContents (theDoc)
	DocPtr 			theDoc;
{
	register short	len, portWidth, strWidth, height, lineHeight, portHeight;
	FontInfo		fInfo;
	Rect			frameRect;
	Str255			aStr;
	
	setFrameClip (theDoc, &frameRect);		/* set clip to frame area */
	
	GetFontInfo (&fInfo);			/* get font information */
	GetWTitle (theDoc, aStr);		/* get window title */
	
	len = height = 0;
	lineHeight = fInfo.ascent + fInfo.descent + fInfo.leading;	/* from font info */
	
	/* get the size of the drawing area */
	portWidth = frameRect.right - frameRect.left;
	portHeight = frameRect.bottom - frameRect.top;
	
	strWidth = StringWidth (aStr);		/* get string width in pixels */

	MoveTo (0, lineHeight);
	while (height < portHeight)		/* fill drawing are with string */
	{		
		while (len < portWidth)
		{
			DrawString (aStr);
			len += strWidth;
		}
		
		len = 0;
		height += lineHeight;		

		MoveTo (0, height);
	}

} /* drawDocContents */
/* ### 4.24.90kwgm -  redone */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */
