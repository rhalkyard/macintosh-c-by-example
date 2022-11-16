/* *****************************************************************************
	FILE: 			DocUtil.c
	
	DESCRIPTION: 	Document Utilities 

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#include <stdio.h>
#if 0
#include "HFS.h"
#endif

#include "BrowserGlobals.h"
#include "StrRsrcDefs.h"

#include "BufMgrPr.h"
#include "DialogUtilPr.h"
#include "DisplayPr.h"
#include "FileUtilPr.h"
#include "MenuConstants.h"
#include "MenuUtilPr.h"
#include "MiscUtilPr.h"
#include "WindowTblPr.h"
#include "WindowUtilPr.h"
#include "DocUtilPr.h"

static short sBrowserMode, sRsrcMode;

/* ------------------------  Local Prototypes  --------------------------------- */
DocPtr			createNewDoc		( DocParamsPtr );
DocPtr			allocDoc			( void );
void			disposeDocContents	( DocPtr );

Boolean			initDocData			( DocPtr, DocParamsPtr );
TEHandle		initDocText			( DocPtr );
void			initScrollParams	( DocPtr, DocParamsPtr );
void			setDocMaxScroll 	( DocPtr theDoc );

OSErr				doGetFile 			( DocParamsPtr );
pascal int 			getFileDlgHook 		( short, DialogPtr );
pascal uchar		getFileFilterProc 	( FileParam * );

/* -----------------------------------------------------------------------------
	doBinaryOpen -	respond to open menu selection
	9.20.90kwgm
-------------------------------------------------------------------------------- */
void
doOpenMenu (short theItem)
{
	DocParams			docParams;
	DocPtr				theDoc;
	Handle				dataHdl;
		
	/* 	
		The DocParams data structure is used to tell the creation function
		how to create the document and what file if any to associate
		with the window
	*/
	docParams.fileParams.fileName [0] = 0;
	docParams.fileParams.openFileRefNum = 0;
	docParams.fileParams.volRefNum = 0;
	docParams.attributes = 0;
	sBrowserMode = (theItem == kBinaryOpenItem) ? kBinaryMode : kTextMode;
	
	if (doOpenFile (&docParams, &theDoc) == noErr)
	{
		if (theDoc = createNewDoc (&docParams))
		{
			if (!initDocData (theDoc, &docParams))
				doCloseDoc (theDoc);
		}		
	}

} /* doOpenMenu */

/* ----------------------------------------------------------------------
	initDocData - 	initialize the document with file data
------------------------------------------------------------------------- */
static Boolean
initDocData (theDoc, docParamsPtr)
	DocPtr			theDoc;
	DocParamsPtr	docParamsPtr;
{
	Boolean		result;
	
	result = false;
	if (initFileBuffer (theDoc, docParamsPtr))
	{	
		if (sBrowserMode == kTextMode)
			initDocText (theDoc);
		initScrollParams (theDoc, docParamsPtr);
		
		result = true;
	}
	
	return (result);
	
} /* initDocData */

/* ----------------------------------------------------------------------
	initScrollParams - 	initialize the document scroll parameters
------------------------------------------------------------------------- */
static void
initScrollParams (DocPtr theDoc, DocParamsPtr docParamsPtr)
{
	register ControlHandle	controlHdl;
	OSErr					err;
	FontInfo				fInfo;
	Rect					frameRect;
	TEHandle				docText;
	
	if (sBrowserMode == kBinaryMode)
	{
		/* setup scroll data */
		theDoc->maxScroll.v = theDoc->docExtent.v = theDoc->fileSize / 256;
		theDoc->curScroll.v = 0;
		theDoc->scrollVal.v = 1;
	}
	else
	{
		docText = theDoc->textHdl;
		
		makeFrameRect (theDoc, &frameRect);
		GetFontInfo (&fInfo);
	
		/* setup scroll data */
		theDoc->docExtent.h = frameRect.right - frameRect.left;
		theDoc->docExtent.v = (*docText)->nLines * (*docText)->lineHeight;
		theDoc->curScroll.h = theDoc->curScroll.v = 0;
		theDoc->scrollVal.h = fInfo.widMax;
		theDoc->scrollVal.v = (*docText)->lineHeight;
	}
	controlHdl = ((WindowPeek)theDoc)->controlList;
	while (controlHdl)
	{
		SetCtlMax (controlHdl, theDoc->maxScroll.v);
		controlHdl = (*controlHdl)->nextControl;
	}

} /* initScrollParams */

/* ----------------------------------------------------------------------
	initDocText -	initialize the text structures for the doc
	9.20.90kwgm
------------------------------------------------------------------------- */
TEHandle
initDocText (theDoc)
	DocPtr		theDoc;
{
	TEHandle	teHdl;
	Rect		frameRect;
	Str255		strBuf;
	
	makeFrameRect (theDoc, &frameRect);

	/* setup the port with proper defaults */
	SetPort (theDoc);
	TextFont (theDoc->textFont);
	TextFace (theDoc->textFace);
	TextSize (theDoc->textSize);

	if ((teHdl = TENew (&frameRect, &frameRect)))
	{
		HidePen ();
		/* if the handle is non-zero, then the file was read */
		if (theDoc->contentHdl)
		{
			HLock (theDoc->contentHdl);
			TEInsert (*theDoc->contentHdl, theDoc->fileSize, teHdl);
			DisposHandle (theDoc->contentHdl);
			theDoc->contentHdl = 0L;
		}
		else	/* print why file wasn't read */
		{
			GetIndString (strBuf, kMemErrStrRsrc, kMemErrFileTooBig);
			TEInsert (&strBuf[1], (Size)strBuf [0], teHdl);
		}
				
		ShowPen ();
		theDoc->textHdl = teHdl;
	}
	
	return (teHdl);

} /* initDocText */

/* ----------------------------------------------------------------------------------------
	doOpenFile -	action func from Open…
	11.20.90kwgm
------------------------------------------------------------------------------------------*/
short
doOpenFile (docParamsPtr, openDocPtr)
	DocParamsPtr	docParamsPtr;
	DocPtr			*openDocPtr;
{
	short 			result;
		
	*openDocPtr = 0L;
	
	result = -1;
	if (doGetFile (docParamsPtr))
	{		
		/* is this document already open ? */	
		if (*openDocPtr = findOpenDoc (docParamsPtr))
		{
			SelectWindow (*openDocPtr);	/* document already on desk - bring to top */
			result = -1;
		}
		else
			result = openFile (docParamsPtr);		/* openFile displays file errors */
	}

	return (result);
	
} /* doOpenFile */

/* ----------------------------------------------------------------------
	doGetFile -			returns false if cancel button 
	11.20.90kwgm		pressed, sets sRsrcMode and gets file info for
						selected file.
------------------------------------------------------------------------- */
static short
doGetFile (docParamsPtr)
	DocParamsPtr	docParamsPtr;
{
	short 			result, dialogID;
	SFReply 		reply;
	Point 			aPt;
	Str64			promptStr;
	SFTypeList		typeList;
	
	typeList [0] = 0;
	
	if (sBrowserMode == kBinaryMode)
		dialogID = kBinaryGetFileDLOG;
	else
		dialogID = kTextGetFileDLOG;
	
	aPt = dialogTopLeft (dialogID);		/* center the GetFile dialog */
		
	GetIndString (promptStr, kMsgStrID, kMsgPromptStr);
	SFPGetFile (aPt, promptStr, getFileFilterProc, -1, typeList, getFileDlgHook, &reply, dialogID, NIL); 

	result = false;  		/*  Cancel button */
	
	if (reply.good == true)		/* Open button */
	{
		BlockMove (reply.fName, docParamsPtr->fileParams.fileName, (Size)(1 + reply.fName [0]));
		docParamsPtr->fileParams.volRefNum = reply.vRefNum;
		
		if (sBrowserMode == kBinaryMode)
		{
			docParamsPtr->attributes |= sRsrcMode ? kDocRsrcFork : kDocDataFork;
			docParamsPtr->attributes |= kBinaryMode;
		}
		else
			docParamsPtr->attributes |= kDocDataFork + kTextMode;
			
		result = true;	
	}

	return (result);

} /* doGetFile */

/* ----------------------------------------------------------------------
	getFileFilterProc - 	hook proc for the get file dialog 
	11.20.90kwgm			selects files with resource or data forks
							 based on sRsrcMode.
------------------------------------------------------------------------- */
static  pascal uchar
getFileFilterProc (paramBlkPtr)
	FileParam	* paramBlkPtr;
{
	uchar		showit;

	if (sBrowserMode == kBinaryMode)	/* binary mode */
	{
		/* 
			show files with non-zero resource forks in resource mode, 
			files with non-zero length data forks in data mode.
			It's all in the FileParam structure.
		*/
		if (sRsrcMode)
			showit = (paramBlkPtr->ioFlRLgLen) ? false : true;	/* resource fork size */
		else
			showit = (paramBlkPtr->ioFlLgLen) ? false : true;	/* data fork size */
	}
	else	/* text mode */
		showit = paramBlkPtr->ioFlLgLen ? false : true;		/* no zero length data forks */

	return (showit);
	
} /* getFileFilterProc */

/* ----------------------------------------------------------------------
	getFileDlgHook - hook proc for the get file dialog
	5.28.90kwgm
------------------------------------------------------------------------- */
static  pascal int
getFileDlgHook (item, dialogPtr)
	short		item;
	DialogPtr	dialogPtr;
{
	short				itemType;
	Rect				box;
	ControlHandle		rsrcButton, dataButton, tempControlHdl;

	if (sBrowserMode == kBinaryMode)
	{
		GetDItem (dialogPtr, kBRsrcButton, &itemType, &rsrcButton, &box);
		GetDItem (dialogPtr, kBDataButton, &itemType, &dataButton, &box);
	}

	switch (item)
	{	
		case -1:	/* initialization as per Apple */
			/* install graphics items for auto-refresh */
			GetDItem (dialogPtr, kGetFileSepLine, &itemType, &tempControlHdl, &box);
			SetDItem (dialogPtr, kGetFileSepLine, itemType, sepLineProc, &box);

			GetDItem (dialogPtr, kGetFileOutline, &itemType, &tempControlHdl, &box);
			SetDItem (dialogPtr, kGetFileOutline, itemType, buttonProc, &box);
			
			if (sBrowserMode == kBinaryMode)
			{
				SetCtlValue (rsrcButton, sRsrcMode);		/* init controls */
				SetCtlValue (dataButton, !sRsrcMode);
			}
			break;
			
		case getOpen:			/* Standard GetFile Items */
		case getCancel:
		case getEject:
		case getDrive:
		case getNmList:
		case getScroll:
			return (item);
			break;
			
		/* manage radio buttons for Binary mode */
		case kBRsrcButton:
			if ((sBrowserMode == kBinaryMode) && GetCtlValue (dataButton))
			{
				SetCtlValue (rsrcButton, true);
				SetCtlValue (dataButton, false);
				
				sRsrcMode = true;
				item = 101;			/* tell SF package to re-read the directory */
			}
			break;
		
		case kBDataButton:
			if ((sBrowserMode == kBinaryMode) && GetCtlValue (rsrcButton))
			{
				SetCtlValue (rsrcButton, false);
				SetCtlValue (dataButton, true);
				
				sRsrcMode = false;
				item = 101;			/* tell SF package to re-read the directory */
			}
			break;
	}

	return (item);

} /* getFileDlgHook */

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

    result = false;

	if (!theDoc)
	    return (result);
    
	if (((WindowPeek) theDoc)->windowKind  < 1)    /* desk accessory */
 		CloseDeskAcc (((WindowPeek) theDoc)->windowKind);
 	else
 	{
      	while (control = ((WindowPeek)theDoc)->controlList)
      		DisposeControl (control);
		
		CloseWindow ((WindowPtr) theDoc);
	
		removeFromDocList (theDoc);
		
		closeDocFile (theDoc);
		disposeDocContents (theDoc);
		DisposPtr (theDoc);
	
		gNumOpenDocs--;		/* decrement the global open window counter */
		result = true;
	}

	return (result);
	
} /* doCloseDoc */

/* -----------------------------------------------------------------------
	createNewDoc -	open a new document window
-------------------------------------------------------------------------- */
static DocPtr 
createNewDoc (docParams)
	DocParamsPtr		docParams;
{
	register DocPtr		theDoc;
	Rect				newWinRect, scrollBarRect;
	Str64				title;
	short				windowProc;

	if (!(theDoc = allocDoc ()))		/* allocate the document structures */
		return (0L);

	/* initialize document data */

	theDoc->maxScroll.h = theDoc->maxScroll.v = kControlMax;
	theDoc->volRefNum = docParams->fileParams.volRefNum;
	theDoc->openFileRefNum = docParams->fileParams.openFileRefNum;
	theDoc->type |= docParams->attributes & (kDocTypeMask + kBrowserModeMask);
	
	theDoc->textFont = gTextFont;
	theDoc->textFace = gTextFace;
	theDoc->textSize = gTextSize;
			
	calcNewWinRect (&newWinRect);
	
	/* create new document structure */
	if (docParams->attributes & kTextMode)
	{
		windowProc = documentProc + 8;
	}
	else
	{
		windowProc = noGrowDocProc;
	}
	
	if (theDoc = NewWindow (theDoc, &newWinRect, "\p", false, 
		windowProc, (WindowPtr)-1L, true, 0L))
	{
		vScrollBarRect (theDoc, &scrollBarRect);
		NewControl (theDoc, &scrollBarRect, 0L, 
			false, 0, 0, kControlMax, scrollBarProc, kVScrollTag);
	
		if (docParams->attributes & kTextMode)
		{
			hScrollBarRect (theDoc, &scrollBarRect);
			NewControl (theDoc, &scrollBarRect, 0L, 
				false, 0, 0, kControlMax, scrollBarProc, kHScrollTag);
		}

		/* title the window */		
		BlockMove (docParams->fileParams.fileName, title, 
				(Size)(docParams->fileParams.fileName [0] + 1));
		BlockMove (title, theDoc->fileName, (Size) (title [0] + 1));
		SetWTitle (theDoc, title);
			
		gNumOpenDocs++;
		addToDocList (theDoc);
		
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

/* ----------------------------------------------------------------------
	resizeTextDocContents	-	called from growWindow, adjust doc
	5.20.90kwgm				contents for changed window size. This is only
							necessary for Browser's text documents
------------------------------------------------------------------------- */
void
resizeTextDocContents (theDoc)
	DocPtr		theDoc;
{
	Rect		frameRect;
	TEHandle	docText;
	
	makeFrameRect (theDoc, &frameRect);
	docText = theDoc->textHdl;
	
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
	
	setDocMaxScroll (theDoc);		/* adjust the doc's scroll parameters */
	
} /* resizeTextDocContents */

/* ----------------------------------------------------------------------
	setDocMaxScroll -	calculate the doc's maxScroll data
	5.20.90kwgm
------------------------------------------------------------------------- */
static void
setDocMaxScroll (DocPtr theDoc)
{
	Rect		frameRect;
	
	makeFrameRect (theDoc, &frameRect);
	
	theDoc->maxScroll.h = theDoc->docExtent.h - (frameRect.right - frameRect.left);
	theDoc->maxScroll.v = theDoc->docExtent.v - (frameRect.bottom - frameRect.top);
}


/* ----------------------------------------------------------------------
	disposeDocContents -	dispose of the content portion of the doc
	5.20.90kwgm
------------------------------------------------------------------------- */
static void
disposeDocContents (theDoc)
	DocPtr		theDoc;
{
	Handle		contentHdl;
	TEHandle	textHdl;
	
	if (ISBINDOC (theDoc))
	{
		if (contentHdl = theDoc->contentHdl)
		{
			DisposHandle (contentHdl);
			theDoc->contentHdl = 0L;
		}
	}
	else
	{
		if (textHdl = theDoc->textHdl)
		{
			TEDispose (textHdl);
			theDoc->textHdl = 0L;
		}
	}

} /* disposeDocContents */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */