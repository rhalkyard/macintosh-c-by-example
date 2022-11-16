/* *****************************************************************************
	FILE: 			Display.c
	
	DESCRIPTION: 	Drawing functions

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#include <TextUtils.h>

#include "AppGlobals.h"

#include "DisplayPr.h"

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

/*--------------------------------------------------------------------------------
	drawDocContents -	draw the contents of theDoc. The contents are taken from
	3.30.90kwgm			the string resource. Try using ResEdit to change the string
---------------------------------------------------------------------------------- */
void 
drawDocContents (theDoc)
	DocPtr 			theDoc;
{
	register short	len, portWidth, strWidth, height, lineHeight, portHeight;
	FontInfo		fInfo;
	Str255			helloStr;
	
	GetFontInfo (&fInfo);
	GetIndString (helloStr, kNameStrRsrc, kHelloStrID);
	
	len = height = 0;
	lineHeight = fInfo.ascent + fInfo.descent + fInfo.leading;
	
	portWidth = ((GrafPtr)theDoc)->portRect.right - ((GrafPtr)theDoc)->portRect.left;
	portHeight = ((GrafPtr)theDoc)->portRect.bottom - ((GrafPtr)theDoc)->portRect.top;
	strWidth = StringWidth (helloStr);

	/* fill the window with the string */
	
	MoveTo (0, lineHeight);
	while (height < portHeight)
	{		
		while (len < portWidth)
		{
			DrawString (helloStr);		/* draw until the edge of the window */
			len += strWidth;
		}
		
		len = 0;
		height += lineHeight;	

		MoveTo (0, height);		/* move the pen to the next line */
	}

	/* 
		this algorithm starts at the top of the window, and draws the string
		using DrawString until the right edge of the window is reached.
		Then it moves the pen down a line, and repeats the process.
		This continues until the pen falls of the bottom of the window.
		
		Notice that the beginning of each new line restarts the string.
		
		Can you modify this algoritm to wrap text around the window, i.e.,
		how would change this loop so that the next line drawn would
		pick up where the end of the previous line left off?? 
		Like in Hello World? Hello World? Hello World? Hello World? Hel
		lo World? He ...

	*/
		
} /* drawDocContents */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */
