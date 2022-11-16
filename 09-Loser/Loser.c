/* *****************************************************************************
	FILE: 			Loser.c
	
	DESCRIPTION: 	Loser entry point and utils

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	2/10/90	-	Created as 1.0
	==========================================================

   ***************************************************************************** */
#define _Main_Module_

#include <StandardFile.h>
#include <TextUtils.h>

#include "AppConstants.h"
#include "AppGlobals.h"
#include "StrRsrcDefs.h"

#include "DialogUtilPr.h"
#include "FileUtilPr.h"
#include "MiscUtilPr.h"

#define	kScreenBorder	4			/* value in pixels */


/* ---- Static vars ----- */

static	SFTypeList 		sTypelist;
static	Str255			sFileName;
static	Boolean			sSFProcFirst, sLoseMode;


/* -------------------------------  Local Prototypes  ----------------------- */
int						main					( void );
static Boolean			doLoser					( void );
static OSErr			doLoserGetFile 			( DocParamsPtr );
static pascal short		loserGetFileDlgHook 	( short, DialogPtr );
static pascal pBoolean	loserGetFileFilterProc 	( FileParam * );

/* -------------------------------------------------------------------------
	main -		program entry point
	5.28.90kwgm
---------------------------------------------------------------------------- */
main ()
{
	InitGraf (&qd.thePort);    /* initialize the managers */
	InitFonts ();
	InitWindows();
	InitCursor ();	
	TEInit ();
	InitDialogs (0L);
	
	MaxApplZone ();    		/* maximize available memory */

	/*  global screen size */
	SetRect (&gScreenRect, kScreenBorder, GetMBarHeight() + kScreenBorder, 
		(qd.screenBits.bounds.right - qd.screenBits.bounds.left) - kScreenBorder, 
		(qd.screenBits.bounds.bottom - qd.screenBits.bounds.top) - kScreenBorder);

	gDevel = false;			/* we are in development */
	
	FlushEvents (everyEvent, 0);	/* dump all pending events */

	while (doLoser ());
	
	ExitToShell ();
}
	
/* ----------------------------------------------------------------------
	doLoser -		called in a loop, put up get file box and set or
	5.28.90kwgm		clear fndrInfo invisible flag. Return 0 for Cancel
------------------------------------------------------------------------- */
static Boolean
doLoser ()
{
	DocParams		docParams;
	FInfo			fndrInfo;
	OSErr			err;
	StringPtr		fileName;
	short			volRefNum;
	FileParamsPtr	fParamsPtr;
	Boolean			result;
	
	if (doLoserGetFile (&docParams))
	{
		fileName = docParams.fileParams.fileName;
		volRefNum = docParams.fileParams.volRefNum;
		
		if (err = GetFInfo (fileName, volRefNum, &fndrInfo))
			doFileCantAlert (fileName, kRead, err, "\pGetFInfo");
		else
		{
			if (sLoseMode)
				fndrInfo.fdFlags |= fInvisible;
			else
				fndrInfo.fdFlags &= ~fInvisible;
					
			/* set the fndrInfo */
			if (err = SetFInfo (fileName, volRefNum, &fndrInfo))
				doFileCantAlert (fileName, kWrite, err, "\pSetFInfo");
			
			if (gDevel)
			{
				/* did it work?? */
				if (err = GetFInfo (fileName, volRefNum, &fndrInfo))		
					doFileCantAlert (fileName, kRead, err, "\pGetFInfo");
			}

		}
		
		result = true;
	}
	else
		result = false;
		
	return (result);
	
} /* doLoser */

/* ----------------------------------------------------------------------
	doLoserGetFile -	loser interface, returns false if cancel button 
	5.28.90kwgm			pressed, sets sLoseMode and gets file info for
						selected file.
------------------------------------------------------------------------- */
static short
doLoserGetFile (docParamsPtr)
	DocParamsPtr	docParamsPtr;
{
	short 			result;
	SFReply 		reply;
	Point 			aPt;
	Str64			promptStr;

	sTypelist [0] = 0;
	
	aPt = dialogTopLeft (kLoserGetFileDLOG);		/* center the GetFile dialog */
	
	sLoseMode = sSFProcFirst = true;	/* initialize the semaphore, set lose mode */
	
	GetIndString (promptStr, kMsgStrID, kMsgPromptStr);
	SFPGetFile (aPt, promptStr, loserGetFileFilterProc, -1, sTypelist, 
		loserGetFileDlgHook, &reply, kLoserGetFileDLOG, NIL); 
	
	if (reply.good != true)
		result = false;  		/*  cancel button */
	else
	{
		BlockMove (reply.fName, docParamsPtr->fileParams.fileName, (Size)(1 + reply.fName [0]));
		docParamsPtr->fileParams.volRefNum = reply.vRefNum;
			
		result = true;
	}

	return (result);

} /* doLoserGetFile */

/* ----------------------------------------------------------------------
	loserGetFileFilterProc - hook proc for the get file dialog 
	5.28.90kwgm				selects visible or invisible files based on
							sLoseMode.
------------------------------------------------------------------------- */
static  pascal pBoolean
loserGetFileFilterProc (paramBlkPtr)
	FileParam	* paramBlkPtr;
{
	Boolean			invis; 
	pBoolean		result;

	invis = (paramBlkPtr->ioFlFndrInfo.fdFlags & fInvisible) ? true : false;

	if (sLoseMode)		/* in lose mode, show visible files */
		result = invis;
	else
		result = invis ? false : true;
		
	return (result);
	
} /* loserGetFileFilterProc */

/* ----------------------------------------------------------------------
	loserGetFileDlgHook - hook proc for the get file dialog
	5.28.90kwgm
------------------------------------------------------------------------- */
static  pascal short
loserGetFileDlgHook (item, dialogPtr)
	short		item;
	DialogPtr	dialogPtr;
{
	short				itemType;
	Rect				box;
	ControlHandle		loseButton, findButton, tempControlHdl, okButton;
	Boolean				changed;

	GetDItem (dialogPtr, kLoserLoseButton, &itemType, &loseButton, &box);
	GetDItem (dialogPtr, kLoserFindButton, &itemType, &findButton, &box);
	GetDItem (dialogPtr, getOpen, &itemType, &okButton, &box);

	if (sSFProcFirst)		/* initialize the dialog */
	{
		/* install graphics items for auto-refresh */
		GetDItem (dialogPtr, kGetFileSepLine, &itemType, &tempControlHdl, &box);
		SetDItem (dialogPtr, kGetFileSepLine, itemType, sepLineProc, &box);

		GetDItem (dialogPtr, kGetFileOutlineButton, &itemType, &tempControlHdl, &box);
		SetDItem (dialogPtr, kGetFileOutlineButton, itemType, buttonProc, &box);
		
		sSFProcFirst = false;			/* clear semphore */
		
		SetCtlValue (loseButton, true);		/* init controls */
		SetCtlValue (findButton, false);
	}

	switch (item)
	{	
		case getOpen:			/* Standard GetFile Items */
		case getCancel:
		case getEject:
		case getDrive:
		case getNmList:
		case getScroll:
			return (item);
			break;
			
		case kLoserLoseButton:				/* My items */
			if (GetCtlValue (findButton))
			{
				SetCTitle (okButton, "\pLose");
				SetCtlValue (loseButton, true);
				SetCtlValue (findButton, false);
				
				sLoseMode = true;
				item = 101;
			}
			break;
		
		case kLoserFindButton:
			if (GetCtlValue (loseButton))
			{
				SetCTitle (okButton, "\pFind");
				SetCtlValue (loseButton, false);
				SetCtlValue (findButton, true);
				
				sLoseMode = false;
				item = 101;
			}
			break;
	}

	return (item);

} /* loserGetFileDlgHook */

/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */
