/* *****************************************************************************
	FILE: 			Display.c
	
	DESCRIPTION: 	Drawing functions

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.20.90	-	July 1990 MacUser Release - all new routines
	==========================================================

   ***************************************************************************** */
#include "AppGlobals.h"

#include <TextEdit.h>

#include "MiscUtilPr.h"
#include "WindowUtilPr.h"
#include "DisplayPr.h"

/* ----------------------------  Local Prototypes  -------------------------------- */

void		drawDocPICT		( DocPtr );
void		drawDocText		( DocPtr );

/*---------------------------------------------------------------------------------
	drawDocContents -	draw the contents of theDoc based on document type
	5.20.90kwgm
----------------------------------------------------------------------------------*/
void 
drawDocContents (theDoc)
	DocPtr 			theDoc;
{
	Rect			frameRect;
	
	setFrameClip (theDoc, &frameRect);
	
	if (ISPICTDOC(theDoc))		/* see AppConstants.h for macro definition of ISPICTDOC */
		drawDocPICT (theDoc);
	else
		drawDocText (theDoc);

} /* drawDocContents */

/* ----------------------------------------------------------------------
	drawDocPICT 	-	draw a picture document at the correct scroll
	5.20.90kwgm
------------------------------------------------------------------------- */
static void
drawDocPICT (theDoc)
	DocPtr		theDoc;
{
	Rect		picRect;
	
	/* get the bounding rectangle for the picture */
	picRect = (*(PicHandle)(theDoc->contentHdl))->picFrame;
	
	/* offset it by the document scroll */
	OffsetRect (&picRect, -(theDoc->curScroll.h - 1), -(theDoc->curScroll.v - 1));
	
	/* draw the PICT in the offset rectangle */
	DrawPicture (theDoc->contentHdl, &picRect);

} /* drawDocPICT */

/* ----------------------------------------------------------------------
	drawDocText 	-	draw a text document at the current scroll
	5.20.90kwgm
------------------------------------------------------------------------- */
static void
drawDocText (theDoc)
	DocPtr		theDoc;
{
	TEHandle		docTextHdl;
	Rect			viewRect, destRect;
	
	if (docTextHdl = theDoc->contentHdl)
	{
		/*
			This is the technique (one of them) for scrolling a TE document:
			
			The TERecord has two rectangles that is uses to draw the text --
				 destRect and viewRect
				 
			The viewRect is where the text will be drawn in the window. This is
			the view box that bounds and clips the text.
			
			The destRect defines where TE will start to draw the text and how
			the words will wrap.
			
			These two rectangles are identical in an unscrolled document.
			
			To draw the text in a scrolled position, you offset the viewRect by
			the curScroll and assign it to the destRect. The text is then rendered
			in the viewRect.
			
		*/
		
		/* get the viewRect */
		destRect = viewRect = (*docTextHdl)->viewRect;
		
		/* offset by vertical scroll */
		OffsetRect (&destRect, 0, -theDoc->curScroll.v);
		
		/* re-assign destRect to TERecord */
		(*docTextHdl)->destRect = destRect;
		
		TEUpdate (&viewRect, docTextHdl);	/* draw the text */
	}

} /* drawDocText */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */
