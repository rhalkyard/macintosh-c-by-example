/* *****************************************************************************
	FILE: 			DocUtil.c
	
	DESCRIPTION: 	Document Utilities 

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.20.90 -	July 1990 MacUser Release 
					- support for fixed text and PICT documents
	
	4.24.90	-	June 1990 MacUser (multi-document support)
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
#include "Version.h"

#include <Controls.h>
#include <ControlDefinitions.h>
#include <Devices.h>
#include <Resources.h>
#include <TextUtils.h>

#include "ThinkHelpers.h"

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
#include <TextEdit.h>
#endif

#include "AppGlobals.h"
#include "StrRsrcDefs.h"

#include "DisplayPr.h"
#include "FileUtilPr.h"
#include "MenuUtilPr.h"
#include "MiscUtilPr.h"
#include "WindowUtilPr.h"
#include "DocUtilPr.h"


/* ------------------------  Local Prototypes  --------------------------------- */

static DocPtr		createNewDoc		( DocParamsPtr );
static DocPtr		allocDoc			( void );
static void			disposeDocContents	( DocPtr );
static void			setDocMaxScroll		( DocPtr );

/* -----------------------------------------------------------------------------
	doNewDoc -		passed a docType token, create a document of that type
	3.30.90kwgm
	5.20.90kwgm		major modifications to accomodate PICT and TEXT windows
-------------------------------------------------------------------------------- */
Boolean
doNewDoc (docType)
	short				docType;
{
	DocParams			docParams;
	DocPtr				theDoc;
	Boolean				result;
	Handle				dataHdl;
	PicHandle			picHdl;
	TEHandle			docText;
	Rect				extent, frameRect;
	OSErr				err;
	FontInfo			fInfo;
	Str64				theString;
		
	result = false;

	/* 	
		The DocParams data structure is used to tell the creation function
		how to create the document and what file if any to associate
		with the window
	*/
	docParams.attributes = docType;
	docParams.fileParams.fileName [0] = 0;
	docParams.fileParams.openFileRefNum = 0;
	docParams.fileParams.volRefNum = 0;

	if (theDoc = createNewDoc (&docParams))
		result = true;
	
	makeFrameRect (theDoc, &frameRect);

	if (docType == kDocPICT)
	{
		/* get a picture from the resource fork */
		picHdl = (PicHandle)GetPicture (kDocPictureID);
		
		/* always check for errors after doing resource things */
		if (err = ResError())
		{
		 	memErrorStr (theString, err);
		 	pDebugStr (theString);
		 	theDoc->contentHdl = 0L;	/* no content */
		}
		else
		{
			theDoc->contentHdl = picHdl;	/* assign handle to doc */
			 
			/* set up document scroll variables (see MacUser July 1990) */
			extent = (*picHdl)->picFrame;
			theDoc->docExtent.h = extent.right;
			theDoc->docExtent.v = extent.bottom;
			theDoc->curScroll.h = theDoc->curScroll.v = 0;
			
			theDoc->scrollVal.h = 1;	/* a value of 1 gives a very smooth, slow scroll */
			theDoc->scrollVal.v = 1;	/* try substituting 5 or 10 to speed it up */
			
			setDocMaxScroll (theDoc);
		}
	}
	else
	{
		/* get a picture from the resource fork */
		dataHdl = GetResource ('TEXT', kDocTextID);
		
		/* check for error */
		if (err = ResError())
		{
		 	memErrorStr (theString, err);
		 	pDebugStr (theString);
		 	theDoc->contentHdl = 0L;	/* no content */
		}
		else
		{
			SetPort (theDoc);

			/* set text attributes */
			TextFont (1);		/* app font */
			TextSize (12);		/* 12 point */
			TextFace (0);		/* plain text */
			
			/* create TERecord */
			if (docText = TENew (&frameRect, &frameRect))
			{
				TESetJust (teJustLeft, docText);
				
				/* assign text data from resource to TERecord */
				
				/*
					Need to lock the handle to the resource while assigning
					to the TERecord. Note that I unlock the handle as soon
					as possible to avoid heap fragmentation.
				*/
				HLock (dataHdl);
				TESetText (*dataHdl, GetHandleSize (dataHdl), docText);
				HUnlock (dataHdl);
				
				theDoc->contentHdl = docText;	/* assign TEHdl to document */
							
				GetFontInfo (&fInfo);		/* get font metrics */
				
				/* setup scroll data */
				theDoc->docExtent.h = frameRect.right - frameRect.left;
				theDoc->docExtent.v = (*docText)->nLines * (*docText)->lineHeight;
				theDoc->curScroll.h = theDoc->curScroll.v = 0;
				theDoc->scrollVal.h = fInfo.widMax;
				theDoc->scrollVal.v = (*docText)->lineHeight;
				
				setDocMaxScroll (theDoc);
			}
			
			/* no longer need text resource since text is now in the TERecord */	
			ReleaseResource (dataHdl);
		}
	}
	
	return (result);

} /* doNewDoc */

/* -----------------------------------------------------------------------------
	doCloseDoc -	close the top document.
	3.30.90kwgm
	4.24.90kwgm - 	modified for multiple windows
	5.20.90kwgm	-	now disposes document contents on close
-------------------------------------------------------------------------------- */
Boolean
doCloseDoc (theDoc)
	WindowPtr		theDoc;
{
	ControlHandle		control;
	Boolean				result;
	WindowPtr			topWin;

    result = false;

	if (!theDoc)
	    return (result);
    
	if (((WindowPeek) theDoc)->windowKind  < 1)    /* desk accessory */
 		CloseDeskAcc (((WindowPeek) theDoc)->windowKind);
 	else if ((result = closeDocFile (theDoc)) != kSaveChangeCancel)
 	{
      	while (control = ((WindowPeek)theDoc)->controlList)
      		DisposeControl (control);
		
		CloseWindow ((WindowPtr) theDoc);

		gNumOpenDocs--;		/* decrement the global open window counter */
		
/* ### kwgm 5.17.90 */
		disposeDocContents (theDoc);
/* ### kwgm 5.17.90 */

		DisposPtr (theDoc);
		result = true;
	}
	else
		result = false;		/* user canceled the close */

	return (result);
	
} /* doCloseDoc */

/* -----------------------------------------------------------------------
	createNewDoc -	open a new document window
	3.30.90kwgm
	4.24.90kwgm	-	revised to support multiple documents
	5.20.90kwgm -	support for Window menu
-------------------------------------------------------------------------- */
static DocPtr 
createNewDoc (docParams)
	DocParamsPtr		docParams;
{
	register DocPtr		theDoc;
	WindowPtr			topWin;
	Rect				newWinRect, scrollBarRect;
	Str64				title;

	if (!(theDoc = allocDoc ()))		/* allocate the document structures */
		return (0L);

	if (topWin = FrontWindow ()) 		/* get the new window rect */
	{
		if (((WindowPeek)topWin)->windowKind == userKind) 
			calcNewWinRect (topWin, &newWinRect);
		else
			newWinRect = gWindowRect;	/* DA window on top, use default */
	}
	else /* no open windows, so use the default window rect */
	{
		gNextWindow = 1;
		newWinRect = gWindowRect;
	}
	
	/* create new document structure */
	if (theDoc = NewWindow (theDoc, &newWinRect, "\p", false, 
		documentProc + 8, (WindowPtr)-1L, true, 0L))
	{
		/* add scroll bars to the window */
		hScrollBarRect (theDoc, &scrollBarRect);
		NewControl (theDoc, &scrollBarRect, 0L, 
			false, 0, 0, kControlMax, scrollBarProc, kHScrollTag);

		vScrollBarRect (theDoc, &scrollBarRect);
		NewControl (theDoc, &scrollBarRect, 0L, 
			false, 0, 0, kControlMax, scrollBarProc, kVScrollTag);
	
		if (!docParams->fileParams.fileName[0])
		{
			/* create a numbered Untitled file name */
			GetIndString (title, kNameStrRsrc, kNameUntitledStr);
			PtoCstr (title);
			sprintf ((char *)title, "%s %d",title, gNextWindow++);
			CtoPstr (title);
		}
		else
			BlockMove (docParams->fileParams.fileName, title, 
				(Size)(docParams->fileParams.fileName + 1));
			
		/* initialize document data */
		SetWTitle (theDoc, title);
	
		theDoc->maxScroll.h = theDoc->maxScroll.v = kControlMax;
		
		BlockMove (title, theDoc->fileName, (Size) (title [0] + 1));
		theDoc->volRefNum = docParams->fileParams.volRefNum;
		theDoc->openFileRefNum = docParams->fileParams.openFileRefNum;
		theDoc->type |= docParams->attributes & kDocTypeMask;
			
		gNumOpenDocs++;
		
		ShowWindow (theDoc);
		SelectWindow (theDoc);	

		SetPort (theDoc);
	}
	
	return (theDoc);
	
} /* createNewDoc */

/* -----------------------------------------------------------
	allocDoc -		allocate the document's data structs
	3.30.90kwgm
	4.24.90kwgm -	modified for multiple window support
--------------------------------------------------------------  */
static DocPtr
allocDoc ()
{
	DocPtr		newDoc;
		
	newDoc = 0L;
	
	if (gNumOpenDocs < kMaxOpenDocs)
		newDoc = newClearPtr ((Size)sizeof (Doc));

	return (newDoc);
		
} /* allocDoc */

/* -----------------------------------------------------------------------------
	closeAllDocs -	close all open documents. present user with choice 
	4.24.90kwgm		to save/cancel. Return false if user cancels at any time.
-------------------------------------------------------------------------------- */
Boolean
closeAllDocs ()
{
	DocPtr				theDoc;
	register short		count;
	Boolean				result;
	
	result = true;
	while (gNumOpenDocs > 0)		/* loop on all open windows */
	{
		if (theDoc = FrontWindow ())	
		{
			if (ISDIRTY(theDoc))
				SelectWindow (theDoc);	/* bring to front and hilight */
			
			if (doCloseDoc (theDoc) == kSaveChangeCancel)
			{
				result = false;		/* user canceled */
				break;
			}
		}
	}
		
	return (result);
	
} /* closeAllDocs */

/* ----------------------------------------------------------------------
	disposeDocContents -	dispose of the content portion of the doc
	5.20.90kwgm
------------------------------------------------------------------------- */
static void
disposeDocContents (theDoc)
	DocPtr		theDoc;
{
	Handle		contentHdl;
	
	if (contentHdl = theDoc->contentHdl)
	{
		if (ISPICTDOC (theDoc))
			ReleaseResource (contentHdl);
		else
			TEDispose (contentHdl);

		theDoc->contentHdl = 0L;
	}

} /* disposeDocContents */

/* ----------------------------------------------------------------------
	resizeDocContents	-	called from growWindow, adjust doc
	5.20.90kwgm				contents for changed window size. This is only
							necessary for Generic's text documents
------------------------------------------------------------------------- */
void
resizeDocContents (theDoc)
	DocPtr		theDoc;
{
	Rect		frameRect;
	TEHandle	docText;
	
	if (ISTEXTDOC (theDoc))		/* text doc */
	{
		makeFrameRect (theDoc, &frameRect);
		docText = theDoc->contentHdl;
		
		/* adjust h extent */
		theDoc->docExtent.h = frameRect.right - frameRect.left;
		
		/* new viewRect, destRect for TERecord */
		(*docText)->viewRect = (*docText)->destRect = frameRect;

		TECalText (docText);	/* force TE to re-wrap the text */

		/* adjust v extent */
		theDoc->docExtent.v = (*docText)->nLines * (*docText)->lineHeight;
		
		/* 
			"Erase-inval" the window. Mac developers have defined this new
			verb do describe what you need to do to force an update event.
			Its as simple as...
		*/
		EraseRect (&frameRect);
		InvalRect (&frameRect);
	}
	
	setDocMaxScroll (theDoc);		/* adjust the doc's scroll parameters */
	
} /* resizeDocContents */

/* ----------------------------------------------------------------------
	setDocMaxScroll -	calculate the doc's maxScroll data
	5.20.90kwgm
------------------------------------------------------------------------- */
static void
setDocMaxScroll (theDoc)
	DocPtr		theDoc;
{
	Rect		frameRect;
	
	makeFrameRect (theDoc, &frameRect);
	
	theDoc->maxScroll.h = theDoc->docExtent.h - (frameRect.right - frameRect.left);
	theDoc->maxScroll.v = theDoc->docExtent.v - (frameRect.bottom - frameRect.top);
}

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */