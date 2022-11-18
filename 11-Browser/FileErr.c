/* *****************************************************************************
	FILE: 			FileErr.c
	
	DESCRIPTION: 	File Manager Error reporting utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */
#include <Dialogs.h>
#include <Files.h>
#include <Sound.h>
#include <TextUtils.h>

#include "BrowserConstants.h"
#include "StrRsrcDefs.h"

#include "DialogUtilPr.h"
#include "MiscUtilPr.h"
#include "WindowUtilPr.h"

#include "FileErrPr.h"


/* ------------------------  Local Prototypes  --------------------------------- */

static void		getIOErrStr 		( StringPtr, OSErr );
static short	fmErr2AppReason 	( OSErr );

/* -------------------------------------------------------------------------------
	doFileCantAlert -	put up the can't open/close/read advisory
	6.20.90kwgm
---------------------------------------------------------------------------------- */
void
doFileCantAlert (fileName, whatOp, reason, infoStr)
	StringPtr		fileName, infoStr;
	short			whatOp, reason;
{
	DialogPtr		theDialog;
	Str255			errStr, whatStr;
	short			theItem, id, itemType;
	GrafPtr			savePort;
	Handle			buttonHdl;
	Rect			box;

	GetPort (&savePort);

	GetIndString (whatStr, kIOMsgStrID, whatOp);
		
	if (theDialog = GetNewDialog (kIOErrDLOG, 0L, (WindowPtr)-1L))
	{
		SysBeep (1);
		GetDItem (theDialog, kOutlineButton, &itemType, &buttonHdl, &box);
		SetDItem (theDialog, kOutlineButton, itemType, (Handle) buttonProc, &box);
		
		getIOErrStr (errStr, reason);
		ParamText (whatStr, fileName, errStr, infoStr);
		centerWindow (theDialog);
		ShowHide (theDialog, true);
		
		ModalDialog (0L, &theItem);
				
		DisposDialog (theDialog);
	}

	SetPort (savePort);

} /* doFileCantAlert */

/* -------------------------------------------------------------------------------------
	getIOErrStr -	return IO error string
	6.20.90kwgm	
---------------------------------------------------------------------------------------*/
static void
getIOErrStr (errStr, err)
	StringPtr	errStr;
	OSErr		err;
{
	short		reason;
	Str255		errNumStr;
	
	reason = fmErr2AppReason (err);
	
	errStr [0] = 0;
	if (reason > 0)
		GetIndString (errStr, kIOMsgStrID, reason);
	
	if (!errStr [0])	/* error not in our list of known strings */
	{
		NumToString ((long)reason, errNumStr);
		GetIndString (errStr, kIOMsgStrID, kIOMacErr);
		pStrCat (errStr, errNumStr);
	}

} /* getIOErrStr */

/* -------------------------------------------------------------------------------------
	fmErr2AppReason -	map a file manager err code to an application reason code
	4.5.89kwgm
---------------------------------------------------------------------------------------*/
static short
fmErr2AppReason (err)
	OSErr 	err;
{
	short	reason;
	
	switch (err) {
		case noErr:
			reason = kNoErr;
			break;

		case dirFulErr:
			reason = kDirectoryFull;
			break;
			
		case dskFulErr:
			reason = kDiskFull;
			break;

		case nsvErr:
		case dirNFErr:
			reason = kVolumeNotFound;
			break;
			
		case fnfErr:
			reason = kFileNotFound;
			break;
			
		case ioErr:
			reason = kDiskIOErr;
			break;
		
		case extFSErr:
			reason = kExternFSErr;
			break;
			
		case bdNamErr:
			reason = kBadFilename;
			break;
			
		case eofErr:
			reason = kEndOfFile;
			break;
			
		case wPrErr:
		case vLckdErr:
			reason = kVolumeLocked;
			break;
			
		case permErr:
		case fLckdErr:
		case wrPermErr:
			reason = kFileLocked;
			break;
		
		case opWrErr:
		case fBsyErr:
			reason = kFileBusy;
			break;
			
		case dupFNErr:
			reason = kFileExists;
			break;
			
		case tmfoErr:
			reason = kTooManyOpenFiles;
			break;
			
		default:
			reason = err;
			break;
	}
	return reason;
	
} /* fmErr2AppReason */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */	

