/* *****************************************************************************
	FILE: 			DocUtil.c
	
	DESCRIPTION: 	Document Utilities 

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	4.24.90	-	June 1990 MacUser (multi-document support)
	3.30.90	-	May 1990 MacUser Release
	==========================================================

   ***************************************************************************** */
/* ### 4.24.90kwgm - added for multiGeneric */
#include "Version.h"

#include <Controls.h>
#include <ControlDefinitions.h>
#include <Devices.h>
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
#endif
/* ### 4.24.90kwgm - added for multiGeneric */


#include "AppGlobals.h"

/* ### 4.24.90kwgm - added for multiGeneric */
#include "StrRsrcDefs.h"
#include "MenuUtilPr.h"
/* ### 4.24.90kwgm - added for multiGeneric */

#include "FileUtilPr.h"
#include "MiscUtilPr.h"
#include "WindowUtilPr.h"
#include "DocUtilPr.h"

/* ------------------------  Local Prototypes  --------------------------------- */

static DocPtr			createNewDoc		( DocParamsPtr );
static DocPtr			allocDoc			( void );

/* -----------------------------------------------------------------------------
	doNewDoc -		open a new window
	3.30.90kwgm
-------------------------------------------------------------------------------- */
Boolean
doNewDoc ()
{
	DocParams			docParams;
	DocPtr				theDoc;
	Boolean				result;
	
	result = false;
	
	/* 	
		The DocParams data structure is used to tell the creation function
		how to create the document and what file if any to associate
		with the window
	*/
	docParams.attributes = 0;
	docParams.fileParams.fileName [0] = 0;
	docParams.fileParams.openFileRefNum = 0;
	docParams.fileParams.volRefNum = 0;

	if (theDoc = createNewDoc (&docParams))
		result = true;
	
	return (result);

} /* doNewDoc */

/* -----------------------------------------------------------------------------
	doCloseDoc -	close the top document.
	3.30.90kwgm
	4.24.90kwgm - modified for multiple windows
-------------------------------------------------------------------------------- */
Boolean
doCloseDoc (theDoc)
	WindowPtr		theDoc;
{
	ControlHandle		control;
	OSErr				result;
	WindowPtr			topWin;

    result = false;

	if (!theDoc)
	    return (result);
    
	if (((WindowPeek) theDoc)->windowKind  < 1)    /* desk accessory */
 		CloseDeskAcc (((WindowPeek) theDoc)->windowKind);
 	else if ((result = closeDocFile (theDoc)) != kSaveChangeCancel)  /* close the file,  */
 	{																 /* then dispose of  */
 																	 /* the window stuff */
      	while (control = ((WindowPeek)theDoc)->controlList)
      		DisposeControl (control);
		
		CloseWindow ((WindowPtr) theDoc);

/* ### 4.24.90kwgm - added for multiGeneric */
		gNumOpenDocs--;		/* decrement the global open window counter */
/* ### 4.24.90kwgm - added for multiGeneric */
	
		DisposPtr (theDoc);
		result = true;
	}
	else
		result = false;		/* the user canceled the close */

	return (result);
	
} /* doCloseDoc */

/*-------------------------------------------------------------------------
	createNewDoc -	open a new document window
	3.30.90kwgm
	4.24.90kwgm	-	revised to support multiple documents
--------------------------------------------------------------------------*/
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

/* ### 4.24.90kwgm - added for multiGeneric */
#if 0
	GetIndString (title, kNameStrRsrc, kWindowTitleStrID);
	
	/* create the associated window */
	if (theDoc = NewWindow (theDoc, &gWindowRect, title, false, rDocProc, -1L, true, 0L))
	{
#endif

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
			sprintf (title, "%s %d",title, gNextWindow++);
			CtoPstr (title);
		}
		else
			BlockMove (docParams->fileParams.fileName, title, 
				(Size)(docParams->fileParams.fileName + 1));
			
		/* initialize window data */
		SetWTitle (theDoc, title);
	
		theDoc->maxScroll.h = theDoc->maxScroll.v = kControlMax;
		
		BlockMove (title, theDoc->fileName, (Size) (title [0] + 1));
		theDoc->volRefNum = docParams->fileParams.volRefNum;
		theDoc->openFileRefNum = docParams->fileParams.openFileRefNum;
	
		gNumOpenDocs++;		/* bump open doc counter */
/* ### 4.24.90kwgm - added for multiGeneric */

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
		
/* ### 4.24.90kwgm - added for multiGeneric */
#if 0
	return (newDoc = newClearPtr ((Size)sizeof (Doc)));
#endif

	newDoc = 0L;
	
	if (gNumOpenDocs < kMaxOpenDocs)
		newDoc = newClearPtr ((Size)sizeof (Doc));
/* ### 4.24.90kwgm - added for multiGeneric */

	return (newDoc);
		
} /* allocDoc */

/* ### 4.24.90 kwgm - new routine for multiGeneric */
/* -----------------------------------------------------------------------------
	closeAllDocs -	close all open documents. present user with choice 
	4.24.90kwgm		to save/cancel
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
/* ### 4.24.90 kwgm - new routine for multiGeneric */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */