/* *****************************************************************************
	FILE: 			Display.c
	
	DESCRIPTION: 	Drawing functions

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#include <TextEdit.h>

#include <ThinkHelpers.h>

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "BrowserGlobals.h"

#include "MiscUtilPr.h"
#include "WindowUtilPr.h"
#include "DisplayPr.h"

/* ----------------------------  Local Prototypes  -------------------------------- */

static void		drawByteIF			( DocPtr );
static void		printBrowserHdr		( DocPtr );
static void		drawDocText 		( DocPtr );

/*---------------------------------------------------------------------------------
	drawDocContents -	draw the contents of theDoc based on document type
	5.20.90kwgm
----------------------------------------------------------------------------------*/
void 
drawDocContents (theDoc)
	DocPtr 			theDoc;
{
	Rect			frameRect;
	
	setFrameClip ((WindowPtr) theDoc, &frameRect);
	
	TextFont (theDoc->textFont);
	TextFace (theDoc->textFace);
	TextSize (theDoc->textSize);

	if (ISBINDOC (theDoc))
		drawByteIF (theDoc);
	else
		drawDocText (theDoc);

} /* drawDocContents */

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
	
	if (docTextHdl = theDoc->textHdl)
	{
		/* get the viewRect */
		destRect = viewRect = (*docTextHdl)->viewRect;
		
		/* offset by vertical scroll */
		OffsetRect (&destRect, 0, -theDoc->curScroll.v);
		
		/* re-assign destRect to TERecord */
		(*docTextHdl)->destRect = destRect;
		
		TEUpdate (&viewRect, docTextHdl);	/* draw the text */
	}

} /* drawDocText */

/* ----------------------------------------------------------------------
	drawByteIF 	-	draw a byte oriented document at the current scroll
	11.20.90kwgm
------------------------------------------------------------------------- */
static void
drawByteIF (DocPtr theDoc)
{
	register char *p;
	register short	v, line, i, c;
	short		lineHeight, hOffset, hHex, hAscii;
	Size		fileOffset, fileSize;
	char		hexbuf [64], asciibuf [64], offsetbuf [16], tmpbuf [24];
	FontInfo	fInfo;
	Handle		fileBufHdl;
		
	
	fileOffset = theDoc->fileOffset;
	fileSize = theDoc->fileSize;
	
	if (fileBufHdl = theDoc->contentHdl)
	{
		HLock (fileBufHdl);
		p = *fileBufHdl;		/* pointer to character data */	

		printBrowserHdr (theDoc);

		GetFontInfo (&fInfo);
		lineHeight = fInfo.ascent + fInfo.descent + fInfo.leading;
		
		v = lineHeight * 3;		/* leave a space at top of screen */
			
		/* print the file data a line at a time */
		for (line = 1; line <= 16 ; line++)
		{
			/* build file offset string and increment */
			sprintf (offsetbuf, "%05lX", fileOffset);
			
			/* build hex and ascii strings, character at a time */
			hexbuf [0] = 0x00;
			asciibuf [0] = 0x00;
			for (i = 0 ; i < 16 ; i++)
			{
				if (i + fileOffset < fileSize)
					c = *p++ & 0x00FF;	/* use short for signed quantities */
				else
					c = 255;
				
				sprintf (tmpbuf, "%02X ", c);	/* do hex format */				
				strcat (hexbuf, tmpbuf);	/* add to hex string */
				
				sprintf (tmpbuf, "%c", isprint (c) ? c : '.');  /* ascii format */
				strcat (asciibuf, tmpbuf);	/* add to ascii string */


			}
			
#define kLeftMargin		6		/* left screen margin */
			/* draw each part of the display */
			MoveTo (kLeftMargin + theDoc->curScroll.h, v);
			CtoPstr (offsetbuf);
			DrawString (offsetbuf);

			Move (fInfo.widMax << 1, 0);
			CtoPstr (hexbuf);
			DrawString (hexbuf);
			
			Move (fInfo.widMax << 1, 0);
			CtoPstr (asciibuf);
			DrawString (asciibuf);
			
			v += lineHeight + fInfo.leading * 2; 	/* next line */
			fileOffset += 16;
		}		
		
		HUnlock (fileBufHdl);
	}


} /* drawByteIF */

/* ----------------------------------------------------------------------
	printBrowserHdr - print the browser page header
	11.20.90kwgm
------------------------------------------------------------------------- */
static void
printBrowserHdr (DocPtr theDoc)
{
	Str255		headerBuf;
	FontInfo	fInfo;
	short		vStart;

	SetPort ((WindowPtr) theDoc);
	
	GetFontInfo (&fInfo);
	vStart = fInfo.ascent + fInfo.descent;
	
	sprintf (headerBuf, "Browser 2.0                        %s fork      %ld bytes",
		ISRSRCDOC(theDoc) ? "Resource" : "Data", theDoc->fileSize);
	
	CtoPstr (headerBuf);
	MoveTo (kLeftMargin + theDoc->curScroll.h, vStart);
	DrawString (headerBuf);

} /* printBrowserHdr */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */
