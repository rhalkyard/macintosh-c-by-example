/* *****************************************************************************
	FILE: 			StrRsrcDefs.h
	
	DESCRIPTION: 	Str# Resource definitions

	AUTHOR:			Kurt W.G. Matthies
		
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
	
	Revision History:
	==========================================================
	Spring 1991 - 	Version 1.0
	==========================================================

   ***************************************************************************** */

#ifndef _StrRsrcDefs_
#define _StrRsrcDefs_

#define		kNameStrRsrc		16
#define		kNameUntitledStr	1
#define		kAboutBoxMsgStr		2


#define		kMsgStrID			 	64
#define		kMsgPromptStr		  	1
#define		kMsgSavePromptStr		2
#define		kMsgOpCancelledStr	  	3
#define		kMsgPasswdWrongStr		4
#define		kMsgPasswdWrongLen		5
#define		kMsgPasswdZeroLen		6
#define		kMsgDESTailStr			7

#define		kIOMsgStrID			104		/*  STR# 104, I/O Msg codes  */
#define		kNoErr				0
#define		kOpen				1
#define		kClose				2
#define 	kRead				3
#define 	kWrite				4
#define		kDelete				5
#define		kDirectoryFull		6
#define		kDiskFull			7
#define		kVolumeNotFound		8
#define		kDiskIOErr			9
#define		kBadFilename		10
#define		kEndOfFile			11
#define		kEarlyEOF			12
#define		kVolumeLocked		13
#define		kFileLocked			14
#define		kFileBusy			15
#define		kFileExists			16
#define		kOutOfMemory		17
#define		kBadFileFormat		18
#define		kFileNotFound		19
#define		kExternFSErr		20
#define		kIOLockErr			21
#define		kIOUnlockErr		22
#define		kIOSetVolErr		23
#define		kIONoGetTmpFileInfo	24
#define		kIONoSetTmpFileInfo	25
#define		kIONoDeleteOldErr	26
#define		kIONoMoveFileErr	27
#define		kIODataNotSaved		28
#define		kIOMacErr			29
#define		kIOInitErr			30
#define		kIOOpenPrompt		31
#define		kTooManyOpenFiles	32

#define		kMemErrStrRsrc			256
#define		kMemErrMsgStr			1
#define		kMemErrUnknownStr		2
#define		kMemErrNoErrStr			3
#define		kMemErrReadOnlyStr		4
#define		kMemErrMemFullStr		5
#define		kMemErrNilHdlStr		6
#define		kMemErrFreeBlkStr		7
#define		kMemErrLockedBlkStr		8
#define		kMemErrFileTooBig		9

#endif
/* ===============================  EOF  =======================================
	Copyright © 1990 by Kurt W.G. Matthies, All Rights Reserved.
================================================================================ */