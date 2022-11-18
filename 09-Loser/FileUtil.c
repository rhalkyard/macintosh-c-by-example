/* *****************************************************************************
	FILE: 			FileUtil.c
	
	DESCRIPTION: 	File I/O utilities

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.

	
	Revision History:
	==========================================================
	6.13.91 - 	Microsoft Press Release
	5.28.90	-	Sept 1990 MacUser Release (Loser)
	==========================================================

   ***************************************************************************** */
#include <Dialogs.h>
#include <Sound.h>
#include <TextUtils.h>
  
#include "AppConstants.h"
#include "StrRsrcDefs.h"

#include "DialogUtilPr.h"
#include "MiscUtilPr.h"
#include "WindowUtilPr.h"

#include "FileUtilPr.h"

/* ------------------------  Local Prototypes  --------------------------------- */

static void		getIOErrStr 		( StringPtr, short );
static short	fmErr2AppReason 	( OSErr );


/* -------------------------------------------------------------------------------
	doFileCantAlert -	put up the can't open/close/read/ advisory
	5.28.90kwgm			print other relevent information if supplied.
						Pass null pstrings for filename, infoStr
						if not used.
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

	/* get the operation string */
	GetIndString (whatStr, kIOMsgStrID, whatOp);
		
	if (theDialog = GetNewDialog (kIOErrDLOG, 0L, (WindowPtr)-1L))
	{
		SysBeep (1);
		GetDItem (theDialog, kOutlineButtonID, &itemType, &buttonHdl, &box);
		SetDItem (theDialog, kOutlineButtonID, itemType, (Handle) buttonProc, &box);
		
		getIOErrStr (errStr, reason);
		ParamText (whatStr, fileName, errStr, infoStr);
		centerWindow (theDialog);
		ShowHide (theDialog, true);
		
		ModalDialog (NIL, &theItem);
				
		DisposDialog (theDialog);
	}

	SetPort (savePort);

} /* doFileCantAlert */

/* -------------------------------------------------------------------------------------
	getIOErrStr -	build an error string from the error number
	5.28.90kwgm	
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
	5.28.90kwgm
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
			
		default:
			reason = err;
			break;
	}
	
} /* fmErr2AppReason */

/* ===========================================  EOF  ========================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
============================================================================================ */	

